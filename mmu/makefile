objs:=start.o init.o leds.o

mmu.bin:$(objs)
	arm-linux-ld -Tmmu.lds -o mmu_elf $^
	arm-linux-objcopy -O binary -S mmu_elf $@
	arm-linux-objdump -D -m arm mmu_elf > mmu.dis
	
%.o:%.c
	arm-linux-gcc -Wall -O2 -o $@ -c $<
	
%.o:%.s
	arm-linux-gcc -Wall -O2 -o $@ -c $<
	
	
clean:
	rm -f *.bin *.o *.dis mmu_elf
