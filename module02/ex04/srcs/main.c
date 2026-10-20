
#include "wopr.h"

const char *password = "admin";
const char *username = "admin";

int check_credentials(const char *test_login, const char *test_password)
{
    if (!ft_strcmp(test_login, username) && !ft_strcmp(test_password, password))
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    init_leds();
    uart_init(UBRR_VALUE);
    char input_login[32];
    char input_password[32];

    while (1)
    {
        set_led_off();
        uart_printstr("Enter your login:\n");
        wait_for_input(input_login, sizeof(input_login), 0);

        uart_printstr("Enter your password:\n");
        wait_for_input(input_password, sizeof(input_password), 1);

        loader();

        if (check_credentials(input_login, input_password))
        {
            uart_printstr("Access granted!\r\n");
            uart_printstr("Welcome ");
            uart_printstr(username);
            uart_printstr("! Good to see you ;)\r\n");
            while (1)
            {
                set_led_green();
                _delay_ms(1000);
                set_led_off();
                _delay_ms(1000);
            }
        }
        else
        {
            uart_printstr("Access denied!\r\n");
            set_led_red();
            _delay_ms(2000);
        }
    }
}