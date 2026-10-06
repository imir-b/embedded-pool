#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << PB1); // Set PB1 as output

    ICR1 = 15624; // Top value for 10% duty cycle (15624 ~= 1 second)
    OCR1A = 1562; // Compare match value for 10% duty cycle (10% of 15624)

    TCCR1A = (1 << COM1A1) | (1 << WGM11); // Set Timer1 Control Register A for non-inverting mode and mode 14 (Fast PWM)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // Set Timer1 Control Register B for mode 14 (Fast PWM) and prescaler of 1024

    while (1)
    {
        // Do nothing, just loop indefinitely
    }
}