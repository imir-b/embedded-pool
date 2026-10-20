
#include <avr/io.h>
#include <util/delay.h>

void set_led_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));

    if (red > 0)
        PORTD |= (1 << PD5);

    if (green > 0)
        PORTD |= (1 << PD6);

    if (blue > 0)
        PORTD |= (1 << PD3);
}

int main(void)
{
    /* Configure PD3, PD5 and PD6 as outputs */
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    while (1)
    {
        // red
        set_led_rgb(255, 0, 0);
        _delay_ms(1000);

        // green
        set_led_rgb(0, 255, 0);
        _delay_ms(1000);

        // blue
        set_led_rgb(0, 0, 255);
        _delay_ms(1000);

        // yellow
        set_led_rgb(255, 255, 0);
        _delay_ms(1000);

        // cyan
        set_led_rgb(0, 255, 255);
        _delay_ms(1000);

        // magenta
        set_led_rgb(255, 0, 255);
        _delay_ms(1000);

        // white
        set_led_rgb(255, 255, 255);
        _delay_ms(1000);
    }
}
