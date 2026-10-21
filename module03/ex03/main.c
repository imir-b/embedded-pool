
#include "rgb.h"

void set_rgb_off(void)
{
    OCR0B = 0;  // Rouge
    OCR0A = 0;  // Vert
    OCR2B = 0;  // Bleu
}

void init_rgb(void)
{
    /* Set led D5 as output */
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    set_rgb_off();
}

void init_timer(void)
{
    /* Timer 0: Fast PWM, non-inverting on OC0A and OC0B */
    TCCR0A = (1 << COM0A1) | (1 << COM0B1)
           | (1 << WGM01) | (1 << WGM00);

    /* Timer 0 prescaler = 8 */
    TCCR0B = (1 << CS01);

    /* Timer 2: Fast PWM, non-inverting on OC2B */
    TCCR2A = (1 << COM2B1)
           | (1 << WGM21) | (1 << WGM20);

    /* Timer 2 prescaler = 8 */
    TCCR2B = (1 << CS21);
}



void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
}

void read_hex_rgb(char *value)
{
    uint8_t i = 0;
    char c;

    while (1)
    {
        c = uart_rx();

        /* Enter to valid */
        if (c == '\r' || c == '\n')
            break;

        /* Backspace to delete */
        if (c == 8 || c == 127)
        {
            if (i > 0)
            {
                i--;
                value[i] = '\0';
                uart_printstr("\b \b");
            }
        }
        else if (i < 7)
        {
            value[i++] = c;
            value[i] = '\0';
            uart_tx(c);
        }
    }

    value[i] = '\0';
    uart_printstr("\r\n");
}

/*
 * Check the format #RRGGBB.
 * Returns 1 if valid, 0 otherwise.
 */
uint8_t check_hex_rgb(const char *value)
{
    uint8_t i;

    if (value == NULL || strlen(value) != 7)
        return 0;

    if (value[0] != '#')
        return 0;

    for (i = 1; i < 7; i++)
    {
        uint8_t c = value[i];

        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'F') ||
              (c >= 'a' && c <= 'f')))
        {
            return 0;
        }
    }

    return 1;
}

/*
 * Convert #RRGGBB to three 8-bit RGB values.
 * Returns 1 on success, 0 for invalid input.
 */
uint8_t convert_hex(const char *value, uint8_t rgb[3])
{
    char component[3] = {0};

    if (rgb == NULL || !check_hex_rgb(value))
        return 0;

    /* Red: characters 1 and 2 */
    component[0] = value[1];
    component[1] = value[2];
    rgb[0] = (uint8_t)strtoul(component, NULL, 16);

    /* Green: characters 3 and 4 */
    component[0] = value[3];
    component[1] = value[4];
    rgb[1] = (uint8_t)strtoul(component, NULL, 16);

    /* Blue: characters 5 and 6 */
    component[0] = value[5];
    component[1] = value[6];
    rgb[2] = (uint8_t)strtoul(component, NULL, 16);

    return 1;
}

int main(void)
{
    char hex_rgb[8]; // #RRGGBB in hex format
    uint8_t rgb[3]; // rgb values
    init_rgb();
    init_timer();
    uart_init(UBRR_VALUE);

    while (1)
    {
        uart_printstr("Enter color (#RRGGBB): \r\n");
        read_hex_rgb(hex_rgb);

        if (!check_hex_rgb(hex_rgb))
        {
            uart_printstr("Invalid format. Example : #RRGGBB \r\n");
            continue;
        }

        if (convert_hex(hex_rgb, rgb))
            set_rgb(rgb[0], rgb[1], rgb[2]);
    }
}