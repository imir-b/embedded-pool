#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << PB1); // Set PB1 as output

    TCCR1A = (1 << COM1A0); // Set Timer1 Control Register A for toggle PB1 on compare match
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Set Timer1 Control Register B for prescaler and mode
    OCR1A = 7812; // Set Output Compare Register A for 1Hz frequency

    while (1)
    {
        // Do nothing, just loop indefinitely
    }
}