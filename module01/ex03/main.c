#define F_CPU 16000000UL // Define CPU frequency as 16 MHz
#define PRESCALER 1024 // Define prescaler value
#define FREQUENCY 1 // Define desired frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
    unsigned char duty_cycle = 10; // Initial duty cycle of 10%

    // Set DDB1 as output for LED D2
    DDRB |= (1 << DDB1);

    // Set DDD2 and DDD4 as inputs for the switches
    DDRD &= ~(1 << DDD2 | (1 << DDD4));
    // Enable pull-up resistors for the switches
    PORTD |= (1 << PORTD2 | (1 << PORTD4));

    // Set Timer1 for Fast PWM mode with ICR1 as top value
    TCCR1A = (1 << COM1A1) | (1 << WGM11);

    // Set Timer1 Control Register B for mode 14 (Fast PWM) and prescaler of 1024
    TCCR1B = (1 << WGM13)
           | (1 << WGM12)
           | (1 << CS12)
           | (1 << CS10);

    // Top value for the timer (15624 ~= 1 sec)
    ICR1 = (F_CPU / (PRESCALER * FREQUENCY)) - 1;

    // Compare match value for the initial duty cycle
    OCR1A = ((uint32_t)(ICR1 + 1) * duty_cycle) / 100;

    while (1)
    {
        if (!(PIND & (1 << DDD2)))
        {
            _delay_ms(20);
            if (duty_cycle < 100)
                duty_cycle += 10;

            while (!(PIND & (1 << PIND2)))
                ;
            _delay_ms(20);
        }
        else if (!(PIND & (1 << DDD4)))
        {
            _delay_ms(20);
            if (duty_cycle > 10)
                duty_cycle -= 10;

            while (!(PIND & (1 << PIND4)))
                ;
            _delay_ms(20);
        }

        if (duty_cycle == 100)
        {
            // Disconnect OC1A from the output pin
            TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));

            // Set D1 to high state
            PORTB |= (1 << PORTB1);
        }
        else
        {
            OCR1A = ((uint32_t)(ICR1 + 1) * duty_cycle) / 100;

            // Reconnect OC1A to the output pin
            TCCR1A = (TCCR1A & ~((1 << COM1A1) | (1 << COM1A0)))
                | (1 << COM1A1);
        }
    }
}
