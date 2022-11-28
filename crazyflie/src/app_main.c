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
#define BUFFER_SIZE 128

char recvbuf[BUFFER_SIZE];
static int takeoff = 0;
static int count = 0;

void appMain() {
  DEBUG_PRINT("Waiting for activation ...\n");

  //test for uart
  //uart1Init(9600);

  // while(1) 
  // {
  //   memset(recvbuf, 0, BUFFER_SIZE);

  //   int cnt = 0;
  //   while(cnt < BUFFER_SIZE)
  //   {
  //     char c;
  //     uart1GetDataWithTimeout(&c, portMAX_DELAY);
  //     recvbuf[cnt++] = c;
  //     if(c=='\0') break;
  //   }
  //   if(strcmp(recvbuf, "")!=0)
  //     DEBUG_PRINT("%s\n", recvbuf);
  // }

  //wait 3 second start
  vTaskDelay(pdMS_TO_TICKS(3000));

  while(1)
  {
    count++;
    if(takeoff == 0)
    {
      crtpCommanderHighLevelTakeoff(1.0f, 1.0f);
      takeoff = 1;
    }
    else if(count==1000)
    {
      crtpCommanderHighLevelGoTo(0.5f, 0, 0, 0, 1.0f, 1);
    }
    else if(count==2000)
    {
      crtpCommanderHighLevelGoTo(0.5f, 0, 0, 0, 1.0f, 1);
    }
    else if(count==3000)
    {
      crtpCommanderHighLevelLand(0.0f, 1.0f);
      takeoff = 0;
      count = 0;
      return ;
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}