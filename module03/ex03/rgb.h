#ifndef RGB_H
#define RGB_H

#include <avr/io.h>

// uart functions
void uart_init(unsigned int ubrr);
char uart_rx(void);
void uart_tx(char c);

#endif