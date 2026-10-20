#include <avr/io.h>
#include <util/delay.h>

void init_rgb(void)
{
    /* Set led D5 as output */
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    /* Set R, G and B leds to value 0 */
    PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
}

void wheel(uint8_t pos)
{
    pos = 255 - pos;

    if (pos < 85) {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170) {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

void init_timer(void)
{
    /* Configure Timer 0 in PWM mode */
    TCCR0A = (1 << COM0A1) | (1 << COM0B1)
           | (1 << WGM01) | (1 << WGM00);

    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64

    /* Configure Timer 1 in PWM mode */
    TCCR2A = (1 << COM2B1)
           | (1 << WGM21) | (1 << WGM20);

    TCCR2B = (1 << CS22); // prescaler 64
}


int main(void)
{
    uint8_t pos = 0;

    init_rgb();
    init_timer();

    while (1)
    {
        wheel(pos);
        pos++;

        _delay_ms(20);
    }
}