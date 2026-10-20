
#include <avr/io.h>
#include <util/delay.h>

void set_led_green(void)
{
    /* Green on, red and blue off */
    PORTD = (PORTD | (1 << PD6))
          & ~((1 << PD3) | (1 << PD5));
}

void set_led_red(void)
{
    /* Red on, green and blue off */
    PORTD = (PORTD | (1 << PD5))
          & ~((1 << PD3) | (1 << PD6));
}

void set_led_blue(void)
{
    /* Blue on, green and red off */
    PORTD = (PORTD | (1 << PD3))
          & ~((1 << PD5) | (1 << PD6));
}

int main(void)
{
    /* Configure PD3, PD5 and PD6 as outputs */
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    while (1)
    {
        set_led_red();
        _delay_ms(1000);
        set_led_green();
        _delay_ms(1000);
        set_led_blue();
        _delay_ms(1000);
    }
}
