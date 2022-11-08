#ifndef __USART_H__
#define __USART_H__

#include "pmsis.h"
extern struct pi_device uart;
extern char sendbuf[128];

void uart_init(int *err);
void uart_send(struct pi_device *device, void *buffer, uint32_t size);
void uart_close(void);

#endif