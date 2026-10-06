#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << PB0); // Set PB0 as output
    DDRD &= ~(1 << PD2); // Set PD2 as input

    while (1)
    {
        if (PIND & (1 << PD2)) // Check if PD2 is high
        {
            PORTB &= ~(1 << PB0); // Set PB0 low
        }
        else
        {
            PORTB |= (1 << PB0); // Set PB0 high
        }
    }

    return 0;
}
