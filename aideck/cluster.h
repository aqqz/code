#ifndef __CLUSTER_H__
#define __CLUSTER_H__
#include "pmsis.h"

void cluster_init(int *err);
void cluster_fun(void *arg);
void cluster_run(void);
void cluster_close(void);
#endif