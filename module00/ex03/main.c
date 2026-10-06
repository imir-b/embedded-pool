#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << PB0); // Set PB0 as output

    DDRD &= ~(1 << PD2); // Set PD2 as input

    while (1)
    {
        _delay_ms(20); // Wait for 20ms
        if (PIND & (1 << PD2)) // Check if PD2 is high
        {
            PORTB ^= (1 << PB0); // Toggle PB0

            while (PIND & (1 << PD2)) // Wait until PD2 goes low
            {
                // Do nothing
            }

            _delay_ms(20); // Wait for 20ms to ensure button release
        }
    }

    return 0;
}