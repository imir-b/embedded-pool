#include <avr/io.h>

void delay(void)
{
    volatile unsigned long i;

    for (i = 0; i < 300000; i++)
        ;
}

int main(void)
{
    DDRB |= (1 << PB1);

    while (1)
    {
        PORTB ^= (1 << PB1); // Toggle PB1

        delay(); // Call the delay function (~1Hz)
    }
}