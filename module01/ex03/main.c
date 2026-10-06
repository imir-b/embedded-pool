#include <avr/io.h>

int main(void)
{
    unsigned char duty_cycle;

    // PB1 / OC1A en sortie pour la LED D2.
    DDRB |= (1 << PB1);

    // PD2 et PD4 en entrée pour les boutons.
    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD4);

    duty_cycle = 10;

    // Fast PWM mode 14, sortie OC1A non inversée.
    TCCR1A = (1 << COM1A1) | (1 << WGM11);

    // Mode 14 + prescaler 1024.
    TCCR1B = (1 << WGM13)
           | (1 << WGM12)
           | (1 << CS12)
           | (1 << CS10);

    // Top value pour un cycle de 1 seconde (15624 ~= 1 seconde).
    ICR1 = 15624;

    // Duty cycle initial de 10% (1562 ~= 10% de 15624).
    OCR1A = (15625UL * duty_cycle) / 100;

    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {
            if (duty_cycle < 100)
                duty_cycle += 10;

            while (!(PIND & (1 << PD2)))
                ;
        }
        else if (!(PIND & (1 << PD4)))
        {
            if (duty_cycle > 0)
                duty_cycle -= 10;

            while (!(PIND & (1 << PD4)))
                ;
        }

        OCR1A = (15625UL * duty_cycle) / 100;
    }
}