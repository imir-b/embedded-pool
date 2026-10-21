#ifndef RGB_H
#define RGB_H

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200UL
#define UBRR_VALUE ((F_CPU / (8UL * UART_BAUDRATE)) - 1)

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

// uart functions
void uart_init(unsigned int ubrr);
char uart_rx(void);
void uart_tx(char c);
void uart_printstr(const char *s);

#endif