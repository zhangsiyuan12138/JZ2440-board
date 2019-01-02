key_led.bin:start.s key_led.c
	arm-linux-gcc -o start.o -c start.start
	arm-linux-gcc -o key_led.o -c key_led.c
	arm-linux-ld -Ttext 0x00000000 -o key_led_elf key_led.o start.o
	arm-linux-objcopy -O binary -S  key_led_elf key_led.bin
	arm-linux-objdump -D -m arm key_led_elf > key_led.dis
clean:
	rm -f key_led_elf key_led.bin key_led.dis *.o