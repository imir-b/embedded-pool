#ifndef WOPR_H
#define WOPR_H

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200UL
#define UBRR_VALUE ((F_CPU / (8UL * UART_BAUDRATE)) - 1)

#define GREEN 0
#define RED 1

#include <avr/io.h>
#include <util/delay.h>

// io functions
void uart_init(unsigned int ubrr);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char *str);

// leds functions
void init_leds(void);
void set_led_green(void);
void set_led_red(void);
void set_led_off(void);

// utils functions
int ft_strcmp(const char *s1, const char *s2);
void loader(void);
void wait_for_input(char *str, unsigned char size, int is_hidden);

#endif