#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "yolo.h"
#include "pmsis.h"
#include "const.h"
#include "modelKernels.h"
int cluster_init(void);
void cluster_run(void);
void cluster_close(void);
void cluster_fun(void *arg);
#endif