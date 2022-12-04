#ifndef __CONST_H__
#define __CONST_H__

#define __XSTR(__s) __STR(__s)
#define __STR(__s) #__s
#define __PREFIX(x)     model ## x
#define malloc          pi_l2_malloc
#define free            pi_l2_free
#define IMG_SIZE        IMG_W*IMG_H*IMG_C
#define YOLO_SIZE       SS*SS*(5*B+C)

#endif