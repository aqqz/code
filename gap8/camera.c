#include "camera.h"

static struct pi_device cam;
static struct pi_himax_conf cam_conf;

int camera_init(void)
{
    pi_himax_conf_init(&cam_conf);

#ifdef SLICE_MODE
    cam_conf.roi.slice_en = 1;
    cam_conf.roi.x = X;
    cam_conf.roi.y = Y;
    cam_conf.roi.w = CAMERA_WIDTH;
    cam_conf.roi.h = CAMERA_HEIGHT;
#endif

    pi_open_from_conf(&cam, &cam_conf);
    if(pi_camera_open(&cam))
    {
        printf("Camera open failed ! \n");
        return -1;
    }

    //rotation camera
    pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
    uint8_t set_value = 3;
    uint8_t reg_value;
    
    pi_camera_reg_set(&cam, IMG_ORIENTATION, &set_value);
    pi_time_wait_us(1000000);
    pi_camera_reg_get(&cam, IMG_ORIENTATION, &reg_value);

    if(reg_value != set_value)
    {
        printf("rotation failed ! \n");
        return -2;
    }

    pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);

    /* Let the camera AEG work for 100ms */
    pi_camera_control(&cam, PI_CAMERA_CMD_AEG_INIT, 0);
    
    pi_time_wait_us(1000000);
    
    return 0;
}

void camera_start(void)
{
    pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
}

void camera_stop(void)
{
    pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);
}

void camera_capture(void *buffer, uint32_t size)
{
    pi_camera_capture(&cam, buffer, size);
}

void camera_close(void)
{
    pi_camera_close(&cam);
}
