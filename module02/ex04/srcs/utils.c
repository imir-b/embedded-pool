
#include "wopr.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* Fake loader */
void loader(void)
{
    int i;
    int j;
    int percent;

    uart_printstr("\r\nAuthenticating...\r\n");

    for (i = 0; i <= 20; i++)
    {
        percent = i * 5;

        uart_printstr("\r[");

        for (j = 0; j < 20; j++)
        {
            if (j < i)
                uart_tx('#');
            else
                uart_tx('-');
        }

        uart_printstr("] ");

        if (percent < 100)
            uart_tx(' ');

        if (percent < 10)
            uart_tx(' ');

        uart_tx('0' + percent / 100);
        uart_tx('0' + (percent / 10) % 10);
        uart_tx('0' + percent % 10);
        uart_tx('%');

        _delay_ms(100);
    }

    uart_printstr("\r\nVerification complete.\r\n");
}

void wait_for_input(char *str, unsigned char size, int is_hidden)
{
    unsigned char i = 0;
    char c;

    while (i < size - 1)
    {
        c = uart_rx();

        if (c == '\r' || c == '\n')
            break;

        if (c == 8 || c == 127)
        {
            if (i > 0)
            {
                i--;
                str[i] = '\0';
                uart_printstr("\b \b");
            }
        }
        else
        {
            str[i++] = c;

            if (is_hidden)
                uart_tx('*');
            else
                uart_tx(c);
        }
    }

    str[i] = '\0';
    uart_printstr("\r\n");
}
