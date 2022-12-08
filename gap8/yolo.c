#include "yolo.h"

static box_list_t *box_before, *box_after; //全局bounding box链表
static box_trans_t bounding_boxes[SS*SS*B]; //全局boudnding box
#ifdef __EMUL__
unsigned char *Input_1; //模型输入
signed char *Output_1; //量化模型输出
float *DqOutput; //解量化模型输出
#else
extern unsigned char *Input_1; //模型输入
extern signed char *Output_1; //量化模型输出
extern float *DqOutput; //解量化模型输出
extern box_trans_t result[5]; //串口输出结果
#endif

float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

void dequantization(float *dest, signed char *src)
{
    for(int i = 0; i < SS; i++)
    {
        for(int j = 0; j < SS; j++)
        {
            for(int k = 0; k < (5*B+C); k++)
            {
                dest[i*SS*(5*B+C)+j*(5*B+C)+k] = (float)src[i*SS*(5*B+C)+j*(5*B+C)+k] * SCALE_FACTOR;
            }
        }
    }
}

void box_trans(box_t *src, box_trans_t *des, int offset_x, int offset_y)
{
    //坐标放大
    float x_center = (src->box_info[0] + offset_x) * (IMG_H / SS);
    float y_center = (src->box_info[1] + offset_y) * (IMG_W / SS);
    float w = src->box_info[2] * IMG_W;
    float h = src->box_info[3] * IMG_H;

    float xmin = x_center - w / 2.0;
    float ymin = y_center - h / 2.0;
    float xmax = x_center + w / 2.0;
    float ymax = y_center + h / 2.0;

    des->box_trans_info[0] = xmin;
    des->box_trans_info[1] = ymin;
    des->box_trans_info[2] = xmax;
    des->box_trans_info[3] = ymax;

    //置信度复制
    des->box_conf = src->box_conf;
}

float iou(box_trans_t *box1, box_trans_t *box2)
{
    float s1 = (box1->box_trans_info[2] - box1->box_trans_info[0]) * (box1->box_trans_info[3] - box1->box_trans_info[1]);
    float s2 = (box2->box_trans_info[2] - box2->box_trans_info[0]) * (box2->box_trans_info[3] - box2->box_trans_info[1]);
    
    float xmin = max(box1->box_trans_info[0], box2->box_trans_info[0]);
    float ymin = max(box1->box_trans_info[1], box2->box_trans_info[1]);
    float xmax = min(box1->box_trans_info[2], box2->box_trans_info[2]);
    float ymax = min(box1->box_trans_info[3], box2->box_trans_info[3]);

    float w = max(xmax - xmin, 0);
    float h = max(ymax - ymin, 0);
    float s3 = w * h;
    return s3 / (s1 + s2 - s3 + 1e-10);
}

box_list_t *list_init(void)
{
    box_list_t *temp = NULL;
    temp = (box_list_t *)malloc(sizeof(box_list_t));
    if(temp)
    {
        // memset(temp->data, 0, sizeof(temp->data)); //不能赋0，否则变成空指针
        temp->next = NULL;
        temp->size = 0;
    }
    return temp;
}

void list_deinit(box_list_t *phead)
{
    if(phead->size > 0)
    {
        box_list_t *temp = phead->next;
        box_list_t *pre = NULL;
        while(temp->next != NULL)
        {
            pre = temp;
            pre->size = 0;
            temp = temp->next;
            #ifdef __EMUL__
            free(pre);
            #else
            free(pre, sizeof(box_list_t));
            #endif
            pre=NULL;
        } //temp->next == null
        #ifdef __EMUL__
        free(temp);
        #else
        free(temp, sizeof(box_list_t));
        #endif
        temp = NULL;
        phead->next = temp;
        phead->size = 0;
    }    
}

int list_insert(box_list_t *phead, box_trans_t *box)
{
    box_list_t *temp = phead;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    
    box_list_t *item = (box_list_t *)malloc(sizeof(box_list_t));
    if(item)
    {
        item->data = box; 
        item->next = NULL;
        temp->next = item;

        phead->size++;

        return 0;
    }
    else
    {
        return -1;
    }
}

int list_delete(box_list_t *phead, box_trans_t *box)
{
    box_list_t *temp = phead;

    while(temp->next != NULL && temp->next->data != box)
    {
        temp = temp->next;
    }

    if(temp->next == NULL) return -1;
    else //temp->next->data == box
    {
        box_list_t *pre = temp;
        box_list_t *nxt = temp->next->next;
        //free(pre->next); //浅拷贝，不能回收内存
        pre->next = nxt;
        phead->size--;
        return 0;
    }
}

void sort(box_trans_t *pBox, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len - 1 - i; j++)
        {
            //按置信度降序排序
            if(pBox[j].box_conf < pBox[j+1].box_conf)
            {
                box_trans_t temp;
                temp = pBox[j];
                pBox[j] = pBox[j+1];
                pBox[j+1] = temp;
            }
        }
    }
}


void nms(box_list_t *before, box_list_t *after)
{
    //当候选框不空
    while(before->size > 0)
    {

        if(list_insert(after, before->next->data) < 0)
        {
            printf("list insert error\n");
            return ;
        }

        if(list_delete(before, before->next->data) < 0)
        {
            printf("list delete error\n");
            return ;
        }

        //找到after的最后一个元素
        box_list_t *a = after;
        while(a->next != NULL)
        {
            a = a->next;
        }

        //遍历before
        box_list_t *b = before;
        while(b->next != NULL)
        {
            b = b->next;
            //计算before现在的每个元素和刚刚加入after的元素的IOU
            float test_iou = iou(a->data, b->data);
            //如果IOU大于阈值从before中删除
            if(test_iou >= IOU_THRESHOLD)
            {
                if(list_delete(before, b->data) < 0)
                {
                    printf("list delete error\n");
                    return ;
                }
            }
        }   
    }
}



void resolve_output(void)
{
    //解量化
    dequantization(DqOutput, Output_1);

    box_before = list_init(); //置信度过滤后的bounding box
    box_after = list_init(); //NMS过滤后的bounding box

    //构造全局bounding box数组
    int cnt = 0;
    for(int i = 0; i < SS; i++)
    {
        for(int j = 0; j < SS; j++)
        {
            box_t box1, box2;
            grid_vector_t grid;

            //构造box_t box1
            box1.box_conf = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+0];
            box1.box_info[0] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+1];
            box1.box_info[1] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+2];
            box1.box_info[2] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+3];
            box1.box_info[3] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+4];

            //构造box_t box2
            box2.box_conf = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+5];
            box2.box_info[0] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+6];
            box2.box_info[1] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+7];
            box2.box_info[2] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+8];
            box2.box_info[3] = DqOutput[i*SS*(5*B+C)+j*(5*B+C)+9];

            //构造grid_vector_t 
            grid.box1 = box1;
            grid.box2 = box2;

            float max_prob = 0.0;
            uint8_t max_id = 0;
            for(int k = 0; k < C; k++)
            {
                grid.prob[k] = DqOutput[i*(SS*(5*B+C))+j*(5*B+C)+10+k];
                if(grid.prob[k] > max_prob)
                {
                    max_prob = grid.prob[k];
                    max_id = k;
                }
            }


            //check box 
            if(grid.box1.box_conf >= CON_THRESHOLD)
            {
                box_trans(&box1, &bounding_boxes[cnt], i, j);
                bounding_boxes[cnt].box_id = max_id;
                bounding_boxes[cnt].box_prob = max_prob;
                cnt++;
            }

            if(grid.box2.box_conf >= CON_THRESHOLD)
            {
                box_trans(&box2, &bounding_boxes[cnt], i, j);
                bounding_boxes[cnt].box_id = max_id;
                bounding_boxes[cnt].box_prob = max_prob;
                cnt++;
            }
        }
    }

    sort(bounding_boxes, cnt);
    for(int i = 0; i < cnt; i++)
    {
        if(list_insert(box_before, &bounding_boxes[i]) < 0)
        {
            printf("list insert error\n");
            return ;
        }
    }
    nms(box_before, box_after);
    cnt = 0;
    //print
    box_list_t *p = box_after;
    while(p->next != NULL)
    {
        p = p->next;
        // printf("con: %f id: %d prob: %f [ %d, %d, %d, %d ] \n", p->data->box_conf, p->data->box_id, p->data->box_prob, \
        // (int)(p->data->box_trans_info[0]), (int)(p->data->box_trans_info[1]), (int)(p->data->box_trans_info[2]), (int)(p->data->box_trans_info[3]));
        
        //copy value to uart buffer
        result[cnt].box_conf = p->data->box_conf;
        result[cnt].box_id = p->data->box_id;
        result[cnt].box_prob = p->data->box_prob;
        result[cnt].box_trans_info[0] = p->data->box_trans_info[0];
        result[cnt].box_trans_info[1] = p->data->box_trans_info[1];
        result[cnt].box_trans_info[2] = p->data->box_trans_info[2];
        result[cnt].box_trans_info[3] = p->data->box_trans_info[3];
        cnt++;
        
    }

    printf("free memory!\n");
    list_deinit(box_before);
    list_deinit(box_after);
    

}

#ifdef __EMUL__
int main(void)
{
    //test list_init()
    printf("list init:\n");
    box_list_t *box_before = NULL;
    box_list_t *box_after = NULL;

    box_before = list_init();
    if(box_before ==NULL)
    {
        printf("malloc memory for box_before error\n");
        return -1;
    }
    else
    {
        printf("%p size=%d\n", box_before, box_before->size);   
    }

    box_after = list_init();
    if(box_after ==NULL)
    {
        printf("malloc memory for box_after error\n");
        return -1;
    }
    else
    {
        printf("%p size=%d\n", box_after, box_after->size);
    }


    box_trans_t boxes[10];
    for(int i = 0; i < 10; i++)
    {
        boxes[i].box_conf = 0.1 * i;
        boxes[i].box_trans_info[0] = 100*i;
        boxes[i].box_trans_info[1] = 200*i;
        boxes[i].box_trans_info[2] = 300*i;
        boxes[i].box_trans_info[3] = 400*i;     
    }

    // test sort()
    sort(boxes, 10);
    printf("\n 排序后：\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%f ", boxes[i].box_conf);

        //test list_insert()
        if(list_insert(box_before, &boxes[i]) < 0)
        {
            printf("list insert error\n");
            return -1;
        }
    }
    printf("\n");

    //print
    box_list_t *p = box_before;
    printf("size: %d\n", box_before->size);

    while(p->next != NULL)
    {
        p = p->next;
        printf("%.2f ", p->data->box_conf);
        for(int i = 0; i < 4; i++)
        {
            printf("%.2f ", p->data->box_trans_info[i]);
        }  
        printf("\n");
    }


    // //test list_delete()
    // printf("\n 测试删除：\n");
    // for(int i = 0; i < 9; i++)
    // {
    //     printf("size: %d\n", box_before->size);
    //     if(list_delete(box_before, &boxes[i]) < 0)
    //     {
    //         printf("target no found\n");
    //         return -1;
    //     }
    // }

    // p = box_before; //头指针重置
    // while(p->next != NULL)
    // {
    //     p = p->next;
    //     printf("%.2f ", p->data->box_conf);
    //     for(int i = 0; i < 4; i++)
    //     {
    //         printf("%.2f ", p->data->box_trans_info[i]);
    //     }  
    //     printf("\n");
    // }

    //test dequantization()
    signed char *output;
    float *dqoutput;

    output = (signed char *)malloc((SS*SS*(5*B+C))*sizeof(signed char));
    
    for(int i = 0; i < SS; i++)
    {
        for(int j = 0; j < SS; j++)
        {
            for(int k = 0; k < (5*B+C); k++)
            {
                output[i*SS*(5*B+C)+j*(5*B+C)+k] = (i+1)*(j+1);
            }    
        }
    }
    printf("\n 量化：\n");

    //print
    for(int i = 0; i < SS; i++)
    {
        for(int j = 0; j < SS; j++)
        {
            for(int k = 0; k < (5*B+C); k++)
            {
                printf("%d ", output[i*SS*(5*B+C)+j*(5*B+C)+k]);           
            }
            printf("\n");
        }
        printf("\n");
    }

    
    dqoutput = (float *)malloc((SS*SS*(5*B+C))*sizeof(float));
    dequantization(dqoutput, output);
    printf("\n 解量化：\n");

    //print
    for(int i = 0; i < SS; i++)
    {
        for(int j = 0; j < SS; j++)
        {
            for(int k = 0; k < (5*B+C); k++)
            {
                printf("%.2f ", dqoutput[i*SS*(5*B+C)+j*(5*B+C)+k]);           
            }
            printf("\n");
        }
        printf("\n");
    }

    //test box_trans()
    box_t box1 = {
        .box_conf = 0.9,
        .box_info[0] = 0.5,
        .box_info[1] = 0.5,
        .box_info[2] = 0.1,
        .box_info[3] = 0.1,
    }; //(x, y, w, h) = (16, 16, 22.4, 22.4)

    box_t box2 = {
        .box_conf = 0.8,
        .box_info[0] = 1.0,
        .box_info[1] = 1.0,
        .box_info[2] = 0.1,
        .box_info[3] = 0.1,
    }; //(x, y, w, h) = (32, 32, 22.4, 22.4)

    printf("c1: %.2f, x1: %.2f, y1: %.2f, w: %.2f, h: %.2f\n", \
    box1.box_conf, box1.box_info[0], box1.box_info[1], box1.box_info[2], box1.box_info[3]);

    printf("c2: %.2f, x2: %.2f, y2: %.2f, w: %.2f, h: %.2f\n", \
    box2.box_conf, box2.box_info[0], box2.box_info[1], box2.box_info[2], box2.box_info[3]);

    box_trans_t bt1, bt2;
    //(xmin, ymin, xmax, ymax) = (4.8, 4.8, 27.2, 27.2)
    //(xmin, ymin, xmax, ymax) = (20.8, 20.8, 43.2, 43.2)
    box_trans(&box1, &bt1, 0, 0);
    box_trans(&box2, &bt2, 0, 0);

    printf("xmin: %.2f, ymin: %.2f, xmax: %.2f, ymax: %.2f\n", \
    bt1.box_trans_info[0], bt1.box_trans_info[1], bt1.box_trans_info[2], bt1.box_trans_info[3]);
    
    
    printf("xmin: %.2f, ymin: %.2f, xmax: %.2f, ymax: %.2f\n", \
    bt2.box_trans_info[0], bt2.box_trans_info[1], bt2.box_trans_info[2], bt2.box_trans_info[3]);

    //test iou()
    bt1.box_trans_info[0] = 0;
    bt1.box_trans_info[1] = 0;
    bt1.box_trans_info[2] = 100;
    bt1.box_trans_info[3] = 100;

    bt2.box_trans_info[0] = 50;
    bt2.box_trans_info[1] = 50;
    bt2.box_trans_info[2] = 150;
    bt2.box_trans_info[3] = 150;

    float iou_score = iou(&bt1, &bt2);
    printf("\n iou_score: %f\n", iou_score);

    //verify box_before
    p = box_before;

    while(p->next != NULL)
    {

        p = p->next;
        iou_score = iou(box_before->next->data, p->data);
        printf("iou with %f is %f\n", p->data->box_conf, iou_score);
    }


    //test nms()
    nms(box_before, box_after);
    printf("\n after nms:\n");
    //print
    p = box_after;
    while(p->next != NULL)
    {
        p = p->next;
        printf("%.2f, %.2f, %.2f, %.2f, %.2f\n", \
        p->data->box_conf, p->data->box_trans_info[0], p->data->box_trans_info[1], p->data->box_trans_info[2], p->data->box_trans_info[3]);
    }

    //verify box_after
    p = box_after;

    while(p->next != NULL)
    {
        p = p->next;
        iou_score = iou(box_after->next->data, p->data);
        printf("iou with %f is %f\n", p->data->box_conf, iou_score);
    }
    

    //test list_deinit
    printf("\n list deinit:\n");
    list_deinit(box_before);
    printf("box_before size: %d\n", box_before->size);
    p = box_before;
    while(p->next != NULL)
    {
        p = p->next;
        printf("%.2f, %.2f, %.2f, %.2f, %.2f\n", \
        p->data->box_conf, p->data->box_trans_info[0], p->data->box_trans_info[1], p->data->box_trans_info[2], p->data->box_trans_info[3]);
    }

    list_deinit(box_after);
    printf("box_after size: %d\n", box_after->size);
    p = box_after;
    while(p->next != NULL)
    {
        p = p->next;
        printf("%.2f, %.2f, %.2f, %.2f, %.2f\n", \
        p->data->box_conf, p->data->box_trans_info[0], p->data->box_trans_info[1], p->data->box_trans_info[2], p->data->box_trans_info[3]);
    }

    return 0;
}
#endif