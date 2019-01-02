objs:=head.o init.o main.o interrupt.o

interrupt.bin:$(objs)
	arm-linux-ld -Ttext 0x00000000 -o interrupt_elf  $^
	arm-linux-objcopy -O binary -S interrupt_elf $@
	arm-linux-objdump -D -m arm interrupt_elf > interrupt.dis

%.o:%.c
	arm-linux-gcc -o $@ -c $<

%.o:%.s
	arm-linux-gcc -o $@ -c $<

clean:
	rm -f *.o *.dis *.bin interrupt_elf