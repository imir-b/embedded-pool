#define F_CPU 16000000UL
#define UART_BAUDRATE 115200UL
#define UBRR_VALUE ((F_CPU / (8UL * UART_BAUDRATE)) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(unsigned int ubrr)
{
    /* Enable double speed mode */
    UCSR0A = (1 << U2X0);

    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable Transmitter, Receiver and RX complete interrupt */
    UCSR0B |= (1 << RXCIE0) | (1 << TXEN0) | (1 << RXEN0);

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

    /* Toggle case if character is alphabetic */
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        c ^= 0x20;
}

ISR(USART_RX_vect)
{
    char received_char = UDR0; // Read the received character
    uart_tx(received_char);   // Transmit the character back
}

int main(void)
{
    uart_init(UBRR_VALUE);

    /* Enable global interrupts */
    sei();

    while (1)
    {
        // Do nothing, waiting for interrupts to handle UART transmission
    }
}
