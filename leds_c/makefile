leds.bin:start.s leds.c
	gcc -o start.o -c start.s
	gcc -o leds.o -c leds.c
	ld -Ttext 0x00000000 start.o leds.o -o leds_elf
	objcopy -O binary -S leds_elf leds.bin
	objump -D -m arm leds_elf > leds.dis
clean:
	rm -f leds.dis leds.bin leds_elf *.o