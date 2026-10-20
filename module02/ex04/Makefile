NAME = ex03

MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT ?= /dev/ttyUSB0

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CCFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I.

SRCS = srcs/main.c srcs/leds.c srcs/uart.c srcs/utils.c

all: hex flash

hex:
	$(CC) $(CCFLAGS) -o $(NAME).bin $(SRCS)
	$(OBJCOPY) -O ihex -R .eeprom $(NAME).bin $(NAME).hex

asm:
	$(CC) $(CCFLAGS) -S main.c -o main.s 
	$(CC) $(CCFLAGS) -S leds.c -o leds.s 
	$(CC) $(CCFLAGS) -S uart.c -o uart.s

flash:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(NAME).hex:i

clean:
	rm -f $(NAME).bin $(NAME).hex $(NAME).s

.PHONY: all hex asm flash clean