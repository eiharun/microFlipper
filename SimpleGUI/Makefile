name := main
include_dir := ./oled-display
source_files := $(wildcard $(include_dir)/*.c)
object_files := $(filter-out ./oled-display/main.o, $(patsubst %.c,%.o,$(source_files)))

default: build

build: $(object_files) $(name).o
	avr-gcc -mmcu=atmega328p $(object_files) $(name).o -o $(name)

# $(name).o: $(name).c
# 	avr-gcc -mmcu=atmega328p -I$(include_dir) -c $< -o $@ -DF_CPU=16000000UL

%.o: %.c
	avr-gcc -mmcu=atmega328p -I$(include_dir) -c $< -o $@ -DF_CPU=16000000UL

burn: build
	avr-objcopy -O ihex -R .eeprom $(name) $(name).hex
	avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:$(name).hex

clean:
	rm -f $(name) $(name).hex $(object_files) $(name).o
