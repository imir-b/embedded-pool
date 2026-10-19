#include <avr/io.h>

#define F_CPU 16000000UL // Define CPU frequency as 16 MHz
#define PRESCALER 1024 // Define prescaler value
#define FREQUENCY 2 // Define desired frequency in Hz

int main(void)
{
    DDRB |= (1 << DDB1); // Set DDB1 as output

    TCCR1A = (1 << COM1A0); // Toggle OC1A every compare
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // WGM12 toggle CTC mode ; CS12 and CS10 for prescaler 1024

    OCR1A = F_CPU / (PRESCALER * FREQUENCY) - 1; // Set Output Compare Register A for 1Hz frequency

    while (1)
    {
        // Do nothing
    }
}