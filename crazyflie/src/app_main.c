#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "app.h"

#include "FreeRTOS.h"
#include "task.h"

#define DEBUG_MODULE "AIDECK"
#include "debug.h"
#include "uart1.h"
#define BUFFER_SIZE 128
char recvbuf[BUFFER_SIZE];

void appMain() {
  DEBUG_PRINT("Waiting for activation ...\n");
  
  uart1Init(9600);

  while(1) 
  {
    memset(recvbuf, 0, BUFFER_SIZE);

    int cnt = 0;
    while(cnt < BUFFER_SIZE)
    {
      char c;
      uart1GetDataWithTimeout(&c, portMAX_DELAY);
      recvbuf[cnt++] = c;
      if(c=='\0') break;
    }
    if(strcmp(recvbuf, "")!=0)
      DEBUG_PRINT("%s\n", recvbuf);
  }
}