#include "main.h"

//#define USE_IMAGE
#define USE_CAMERA
#define SAVE_IMG
#define USE_UART

unsigned char *Input_1; //模型输入
signed char *Output_1; //量化模型输出
float *DqOutput; //解量化模型输出
char sendbuf[128];

AT_HYPERFLASH_FS_EXT_ADDR_TYPE __PREFIX(_L3_Flash) = 0;

int appstart()
{

    //set freq
    pi_freq_set(PI_FREQ_DOMAIN_FC, 250000000);

    printf("Enter main controller\n");
    //allocate memory
    Input_1 = (unsigned char *)malloc(IMG_SIZE * sizeof(unsigned char));
    if(Input_1 == NULL)
    {
        printf("allocate memory for input error\n");
        pmsis_exit(-1);
    }

    Output_1 = (signed char *)malloc(YOLO_SIZE * sizeof(signed char));
    if(Output_1==NULL)
    {
        printf("allocate memory for model Output error\n");
        pmsis_exit(-1);
    }

    DqOutput = (float *)malloc(YOLO_SIZE *sizeof(float));
    if(DqOutput==NULL)
    {
        printf("allocate memory for dequantization error\n");
        pmsis_exit(-1);
    }

    //read image
    #ifdef USE_IMAGE
    printf("Reading Image\n");
    char *ImgName = __XSTR(AT_IMAGE);
    if(ReadImageFromFile(ImgName, IMG_W, IMG_H, IMG_C, Input_1, IMG_SIZE, IMGIO_OUTPUT_CHAR, 0))
    {
        printf("load image from file error\n");
        pmsis_exit(-1);
    }
    #endif
    

    //camera init
    #ifdef USE_CAMERA
    if(camera_init() < 0)
    {
        printf("camera init error\n");
        pmsis_exit(-1);
    }
    printf("Open Himax camera\n");
    #endif

    //uart init
    #ifdef USE_UART
    if(uart_init(115200) < 0)
    {
        printf("uart init error\n");
        pmsis_exit(-1);
    }
    #endif

    //cluster init
    if(cluster_init() < 0)
    {
        printf("cluster init error\n");
        pmsis_exit(-1);
    }

    //construct model graph
    printf("Constructor\n");
    if(__PREFIX(CNN_Construct)())
    {
        printf("model graph construct error\n");
        pmsis_exit(-1);
    }

    while(1)
    {   
        //camera capture
        #ifdef USE_CAMERA
        printf("Capture...\n");
        camera_start();
        camera_capture(Input_1, IMG_SIZE);
        camera_stop();
        printf("Capture done.\n");
        #endif

        //save img
        #ifdef SAVE_IMG
        int idx = 0;
        char ImgName[50];
        sprintf(ImgName, "../../../img_OUT_%ld.ppm", idx);
        printf("Dump Image %s\n", ImgName);
        WriteImageToFile(ImgName, IMG_W, IMG_H, sizeof(u_int8_t), Input_1, GRAY_SCALE_IO);
        #endif
        
        //cluster run
        printf("Call cluster\n");
        cluster_run();

        //uart send
        #ifdef USE_UART
        strcpy(sendbuf, "helloworld");
        uart_send(sendbuf, sizeof(sendbuf));
        pi_time_wait_us(500000); //500ms
        #endif   
        
    }
    //destruct model graph
    __PREFIX(CNN_Destruct)();

    //free memory
    free(DqOutput, YOLO_SIZE * sizeof(float));
    free(Output_1, YOLO_SIZE * sizeof(signed char));
    free(Input_1, IMG_SIZE * sizeof(unsigned char));

    //close dev
    camera_close();
    uart_close();
    cluster_close();

    printf("End\n");
    pmsis_exit(0);
    return 0;
}

int main()
{
    printf("\n\n\t *** Detection on GAP8 Example *** \n\n");
    return pmsis_kickoff((void *)appstart);
}