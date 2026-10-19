#include <avr/io.h>
#include <util/delay.h>

void display_value(unsigned char value)
{
    // Clear the bits for PB0(D1), PB1(D2), PB2(D3), and PB4(D4)
    PORTB &= ~((1 << PB0) |
                (1 << PB1) |
                (1 << PB2) |
                (1 << PB4));
    
    // Set the bits for PB0(D1), PB1(D2) and PB2(D3) based on the third bit of the value
    PORTB |= value & 0x07;

    // Set the bit for PB4(D4) based on the fourth bit of the value
    PORTB |= (value & 0x08) << 1; 
}

unsigned char read_switches(unsigned char *old_sw1, unsigned char *old_sw2, unsigned char value)
{
    unsigned char sw1 = !(PIND & (1 << PD2)); // Read SW1 state
    unsigned char sw2 = !(PIND & (1 << PD4)); // Read SW2 state

    if (sw1 && !*old_sw1) // Check if SW1 is pressed
    {
        if (value < 15)
            value = (value + 1) & 0x0F; // Increment value
        _delay_ms(20);
    }
    else if (sw2 && !*old_sw2) // Check if SW2 is pressed
    {
        if (value > 0)
            value = (value - 1) & 0x0F; // Decrement value
        _delay_ms(20);
    }

    *old_sw1 = sw1; // Update old SW1 state
    *old_sw2 = sw2; // Update old SW2 state

    return value;
}

int main(void)
{
    // Setup LEDs D1 D2 D3 D4 as output
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);

    // Setup Switches SW1 and SW2 as input
    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD4);

    unsigned char value = 0, old_sw1 = 0, old_sw2 = 0;

    while (1)
    {
        // 1- Check if SW1 or SW2 is pressed to increment or decrement the value 
        value = read_switches(&old_sw1, &old_sw2, value);

        // 2- Display the value on the LEDs
        display_value(value);
    }
}
