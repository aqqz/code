#ifndef __YOLO_H__
#define __YOLO_H__
#include <stdint.h>


#define  SS     7
#define  B      2
#define  C      20
#define IMG_W   28
#define IMG_H   28
#define IMG_C   1
#define IOU_THRESHOLD 0.5
#define CON_THRESHOLD 0.5
#define SCALE_FACTOR  0.007874015748031496


typedef struct {
    float box_conf; //置信度
    float box_info[4]; //x, y, w, h
} box_t;

typedef struct {  
    box_t box1;  //box1[c, x, y, w, h]
    box_t box2;  //box2[c, x, y, w, h]   
    float prob[C];//class prob    
} grid_vector_t;

typedef struct {
    float box_conf; //置信度
    int   box_id;   //目标类别
    float box_prob; //目标概率
    float box_trans_info[4]; //xmin, ymin, xmax, ymax
} box_trans_t;


typedef struct box_list {
    box_trans_t *data; //数据域
    struct box_list *next; //指针域
    int size; //表长
} box_list_t;


void dequantization(float *dest, signed char *src);
void box_trans(box_t *src, box_trans_t *des, int offset_x, int offset_y);
float iou(box_trans_t *box1, box_trans_t *box2);

box_list_t* list_init();
int list_insert(box_list_t *phead, box_trans_t *box);
int list_delete(box_list_t *phead, box_trans_t *box);

void nms(box_list_t *before, box_list_t *after);
extern void resolve_output(void);

float max(float a, float b);
float min(float a, float b);
void sort(box_trans_t *pBox, int len);

#endif
