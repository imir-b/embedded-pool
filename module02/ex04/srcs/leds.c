
#include "wopr.h"

void set_led_off(void)
{
    /* Set red, green and blue off */
    PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));
}

void init_leds(void)
{
    /* Configure PD3, PD5 and PD6 as outputs */
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    set_led_off();
}

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
