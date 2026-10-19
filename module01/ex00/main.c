#include <avr/io.h>

#define F_CPU 16000000UL // Define CPU frequency as 16 MHz

int main(void)
{
    DDRB |= (1 << DDB1); // Set DDB1 (D1) as output

    uint32_t cycles = 36; // Number of cycles for ~0.5 seconds delay
    uint32_t delay_count = (F_CPU / cycles) / 2; // Calculate delay count for ~0.5 seconds
    while (1)
    {
        PORTB ^= (1 << PB1); // Toggle PB1 (D1)

        for (volatile uint32_t i = 0; i < delay_count; i++)
        {
            // Do nothing
        }
    }
}