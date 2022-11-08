#include "uart.h"

struct pi_device uart;
struct pi_uart_conf uart_conf;
char sendbuf[128];

void uart_init(int *err)
{
    pi_uart_conf_init(&uart_conf);
    uart_conf.enable_tx = 1;
    uart_conf.enable_rx = 0;
    uart_conf.baudrate_bps = 9600;

    pi_open_from_conf(&uart, &uart_conf);
    if(pi_uart_open(&uart))
    {
        printf("Uart open failed ! \n");
        *err = -4;
        return ;
    }
}

void uart_send(struct pi_device *device, void *buffer, uint32_t size)
{
    pi_uart_write(device, buffer, size);
}

void uart_close(void)
{
    pi_uart_close(&uart);
}