#ifndef __UART_H__
#define __UART_H__

#include "pmsis.h"

int uart_init(int baudrate);
void uart_send(void *buffer, uint32_t size);
void uart_close(void);

#endif