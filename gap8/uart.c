#include "uart.h"

static struct pi_device uart;
static struct pi_uart_conf uart_conf;

int uart_init(int baudrate)
{
    pi_uart_conf_init(&uart_conf);
    uart_conf.enable_tx = 1;
    uart_conf.enable_rx = 0;
    uart_conf.baudrate_bps = baudrate;

    pi_open_from_conf(&uart, &uart_conf);
    if(pi_uart_open(&uart))
    {
        printf("Uart open failed ! \n");
        return -1;
    }
    return 0;
}

void uart_send(void *buffer, uint32_t size)
{
    pi_uart_write(&uart, buffer, size);
}

void uart_close(void)
{
    pi_uart_close(&uart);
}