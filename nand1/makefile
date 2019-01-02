objs:=start.o sdram.o nand.o leds.o

nand.bin:$(objs)
	arm-linux-ld -Tnand.lds -o nand_elf $^
	arm-linux-objcopy -O binary -S nand_elf $@
	arm-linux-objdump -D -m arm nand_elf > nand.dis
%.o:%.c
	arm-linux-gcc -o $@ -c $<
%.o:%.S
	arm-linux-gcc -o $@ -c $<

clean:
	rm *.o *.bin *.dis nand_elf
