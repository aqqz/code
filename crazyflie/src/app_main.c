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

TaskHandle_t uartTaskHandle = NULL;
TaskHandle_t flyTaskHandle = NULL;

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

void uartTask(void *pvParameters)
{
  while(1)
  {
    DEBUG_PRINT("uartTask\n");
  }
}

void flyTask(void *pvParameters)
{
  while(1)
  {
    DEBUG_PRINT("flyTask\n");
  }
}

void appMain() 
{
  vTaskDelay(pdMS_TO_TICKS(3000));

  xTaskCreate(uartTask, "UARTTASK", 128, NULL, 1, &uartTaskHandle);
  xTaskCreate(flyTask, "FLYTASK", 128, NULL, 1, &flyTaskHandle);

  while(1);
}