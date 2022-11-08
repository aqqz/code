#include "cluster.h"
#include "yolo.h"

struct pi_device cluster_dev;
struct pi_cluster_conf cl_conf;
struct pi_cluster_task cl_task;

void cluster_init(int *err)
{
    cl_conf.id = 0; //set fc as main core
    pi_open_from_conf(&cluster_dev, &cl_conf);
    if(pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open error\n");
        *err = -3;
        return ;
    }

    //cluster task configuration
    pi_cluster_task(&cl_task, cluster_fun, NULL);
    cl_task.stack_size = STACK_SIZE;
    cl_task.slave_stack_size = SLAVE_STACK_SIZE;
}

void cluster_fun(void *arg)
{
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