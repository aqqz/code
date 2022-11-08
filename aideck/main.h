#ifndef __MAIN_H__
#define __MAIN_H__

#include "Gap.h"

#define __XSTR(__s) __STR(__s)
#define __STR(__s) #__s
#define __PREFIX(x)     model ## x
#define malloc          pi_l2_malloc
#define free            pi_l2_free

extern signed char *Output_1; //量化模型输出
extern float *DqOutput; //解量化模型输出
extern AT_HYPERFLASH_FS_EXT_ADDR_TYPE __PREFIX(_L3_Flash);

#endif