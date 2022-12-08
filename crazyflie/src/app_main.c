#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "debug.h"
#include "uart1.h"
#include "crtp_commander_high_level.h"

#define DEBUG_MODULE "AIDECK"
#define BUFFER_SIZE 28

typedef struct {
  float box_conf; //置信度
  uint8_t box_id; //目标类别
  float box_prob; //目标概率
  float box_trans_info[4]; //xmin, ymin, xmax, ymax
} box_trans_t;

uint8_t recvbuf[BUFFER_SIZE];
box_trans_t recv[5];

int takeoff = 0;
int count = 0;
int area = 0;
box_trans_t* uart1GetStruct()
{
  memset(recvbuf, 0, sizeof(recvbuf));
  int cnt = 0;
  while(cnt < BUFFER_SIZE)
  {
    uint8_t c;
    uart1GetDataWithTimeout(&c, portMAX_DELAY);
    recvbuf[cnt++] = c;
  }
  return (box_trans_t *)recvbuf;
}

void appMain() {
  DEBUG_PRINT("Waiting for activation ...\n");
  uart1Init(115200);
  //wait 3 second
  vTaskDelay(pdMS_TO_TICKS(3000));

  while(1) 
  {
    box_trans_t *temp = uart1GetStruct();
    
    DEBUG_PRINT("con: %f id: %d prob: %f [ %d, %d, %d, %d ] \n", (double)(temp->box_conf), temp->box_id, (double)(temp->box_prob), (int)(temp->box_trans_info[0]), (int)(temp->box_trans_info[1]), (int)(temp->box_trans_info[2]), (int)(temp->box_trans_info[3]));
    // count++;
    // //takeoff
    // if(takeoff == 0)
    // {
    //   crtpCommanderHighLevelTakeoff(1.0f, 1.0f);
    //   takeoff = 1;
    // }
    // //land
    // if(count==300)
    // {
    //   crtpCommanderHighLevelLand(0.0f, 1.0f);
    //   takeoff = 0;
    //   count = 0;
    //   return ;
    // }
    
    // if(temp->box_id == 2)
    // {
    //   area = (temp->box_trans_info[2] - temp->box_trans_info[0]) * (temp->box_trans_info[3] - temp->box_trans_info[1]);
    
    //   if(area < 224*224 / 4)
    //   {
    //     crtpCommanderHighLevelGoTo(0.1f, 0, 0, 0, 1.0f, 1);
    //   }
    //   else
    //   {
    //     crtpCommanderHighLevelGoTo(-0.1f, 0, 0, 0, 1.0f, 1);
    //   }
    // }
    // vTaskDelay(pdMS_TO_TICKS(10));
  }
}