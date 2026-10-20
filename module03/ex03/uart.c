#include "rgb.h"

char uart_rx(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))
        ;

    /* Get and return received data from buffer */
    return UDR0;
}

void uart_init(unsigned int ubrr)
{
    /* Enable double speed mode */
    UCSR0A = (1 << U2X0);

    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable transmitter and receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    /* 8N1 */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char c)
{
    // Transmit character via UART

    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    /* Put data into buffer, sends the data */
    UDR0 = c;
}
