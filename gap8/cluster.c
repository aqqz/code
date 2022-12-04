#include "cluster.h"


static struct pi_device cluster_dev;
static struct pi_cluster_conf cl_conf;
static struct pi_cluster_task cl_task;
extern unsigned char *Input_1; //模型输入
extern signed char *Output_1; //量化模型输出

int cluster_init(void)
{
    cl_conf.id = 0; //set fc as main core
    pi_open_from_conf(&cluster_dev, &cl_conf);
    if(pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open error\n");
        return -1;
    }

    //cluster task configuration
    pi_cluster_task(&cl_task, cluster_fun, NULL);
    cl_task.stack_size = STACK_SIZE;
    cl_task.slave_stack_size = SLAVE_STACK_SIZE;
    return 0;
}

void cluster_fun(void *arg)
{
    //run nngraph
    __PREFIX(CNN)(Input_1, Output_1);
    printf("Model Run completed\n");
    resolve_output();
}

void cluster_run(void)
{
    pi_cluster_send_task(&cluster_dev, &cl_task);
}

void cluster_close(void)
{
    pi_cluster_close(&cluster_dev);
}