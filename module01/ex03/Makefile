NAME = ex03

MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CCFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

SRCS = main.c
HEX = $(NAME).hex

all: flash

$(NAME).bin: $(SRCS)
	$(CC) $(CCFLAGS) -o $@ $(SRCS)

$(HEX): $(NAME).bin
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(HEX)
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(HEX):i

asm:
	$(CC) $(CCFLAGS) -S $(SRCS) -o $(NAME).s

clean:
	rm -f $(NAME).bin $(NAME).hex $(NAME).s

.PHONY: all flash asm clean
