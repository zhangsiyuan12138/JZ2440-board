sdram.bin:start.s sdram.c
	arm-linux-gcc -o start.o -c start.s
	arm-linux-gcc -o sdram.o -c sdram.c
	arm-linux-ld -Ttext 0x3000000 -o sdram_elf start.o sdram.o
	arm-linux-objcopy  -O binary -S sdram_elf sdram.bin
	arm-linux-objdump -D -m arm sdram_elf > sdram.dis
clean:
	rm *.o *.dis *.bin sdram_elf 
