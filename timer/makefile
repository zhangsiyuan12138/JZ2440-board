objs:=start.o init.o main.o interrupt.o

timer.bin:$(objs)
	arm-linux-ld -Ttimer.lds -o timer_elf $^
	arm-linux-objcopy -O binary -S timer_elf $@
	arm-linux-objdump -D -m arm timer_elf > timer.dis
	
%.o:%.c
	arm-linux-gcc  -o $@ -c $<
%.o:%.s 
	arm-linux-gcc -o $@ -c $<
	
clean:
	rm -f *.o *.bin *.dis timer_elf