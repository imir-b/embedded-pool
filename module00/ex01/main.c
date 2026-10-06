#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << PB0); // Set PB0 as output
    PORTB |= (1 << PB0); // Set PB0 high

    return 0;
}
