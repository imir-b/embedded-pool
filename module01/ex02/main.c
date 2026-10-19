#include <avr/io.h>

#define F_CPU 16000000UL // Define CPU frequency as 16 MHz
#define PRESCALER 1024 // Define prescaler value
#define FREQUENCY 1 // Define desired frequency in Hz

int main(void)
{
    DDRB |= (1 << DDB1); // Set DDB1 as output

    ICR1 = (F_CPU / (PRESCALER * FREQUENCY)) - 1; // Set Input Capture Register for 1Hz frequency
    OCR1A = ICR1 / 10; // Set Output Compare Register A for 10% duty cycle

    TCCR1A = (1 << COM1A1) | (1 << WGM11); // Set Timer1 Control Register A for non-inverting mode and mode 14 (Fast PWM)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // Set Timer1 Control Register B for mode 14 (Fast PWM) and prescaler of 1024

    while (1)
    {
        // Do nothing
    }
}