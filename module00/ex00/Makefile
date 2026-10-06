NAME = ex00

MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CCFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

SRCS = main.c

all: hex flash

hex:
	$(CC) $(CCFLAGS) -o $(NAME).bin $(SRCS)
	$(OBJCOPY) -O ihex -R .eeprom $(NAME).bin $(NAME).hex

flash:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(NAME).hex:i

clean:
	rm -f $(NAME).bin $(NAME).hex

.PHONY: all hex flash clean