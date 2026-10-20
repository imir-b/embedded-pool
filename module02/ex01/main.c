
#define F_CPU 16000000UL
#define PRESCALER 1024UL
#define FREQUENCY 1UL
#define UART_BAUDRATE 115200UL
#define UBRR_VALUE ((F_CPU / (8UL * UART_BAUDRATE)) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(unsigned int ubrr)
{
    /* Double speed mode */
    UCSR0A = (1 << U2X0);

    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable transmitter */
    UCSR0B = (1 << TXEN0);

    /* 8 data bits, no parity, 1 stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = c;
}

void uart_printstr(const char *str)
{
    while (*str)
    {
        uart_tx(*str);
        str++;
    }
}

void timer1_init(void)
{
    /* Timer1 in CTC mode */
    TCCR1A = 0;
    TCCR1B = (1 << WGM12);

    /* Set compare value */
    OCR1A = F_CPU / PRESCALER * FREQUENCY - 1;

    /* Enable Timer1 Compare Match A interrupt */
    TIMSK1 = (1 << OCIE1A);

    /* Prescaler = 1024, start Timer1 */
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

ISR(TIMER1_COMPA_vect)
{
    uart_printstr("Hello World!\r\n");
}

int main(void)
{
    uart_init(UBRR_VALUE);
    timer1_init();

    sei(); // Enable global interrupts

    while (1)
    {
        // Do nothing
    }
}
