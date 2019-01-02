led_on_c.bin: start.s led_on.c
	arm-linux-gcc -o start.o -c start.s
	arm-linux-gcc -o led_on.o -c led_on.c
	arm-linux-ld -Ttext 0x00000000 -o led_on_c_elf start.o led_on.o
	arm-linux-objcopy -O binary -S led_on_c_elf led_on_c.bin
	arm-linux-objdump -D -m arm led_on_c_elf > led_on_c.dis
clean:
	rm -f led_on_c.dis led_on_c.bin led_on_c_elf *.o
