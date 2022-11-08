#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "pmsis.h"
#include "bsp/camera.h"
#include "bsp/camera/himax.h"

#define IMG_ORIENTATION         0x0101

#ifdef SLICE_MODE
#define X                   50 
#define Y                   0 
#define CAMERA_WIDTH        224
#define CAMERA_HEIGHT       224
#else
#define CAMERA_WIDTH        324
#ifdef QVGA_IMG
#define CAMERA_HEIGHT       224
#else // max resolution of Himax camera
#define CAMERA_HEIGHT       324
#endif /* QVGA */
#endif

extern struct pi_device cam;

void camera_init(int *err);
void camera_start(void);
void camera_stop(void);
void camera_capture(struct pi_device *device, void *buffer, uint32_t size);
void camera_close(void);


#endif