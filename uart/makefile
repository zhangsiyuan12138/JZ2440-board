objs:= start.o init.o uart.o main.o 

uart.bin:$(objs)
	arm-linux-ld -Tuart.lds -o uart_elf $^
	arm-linux-objcopy -O binary -S uart_elf $@
	arm-linux-objdump -D -m arm uart_elf > uart.dis
	
%.o:%.s
	arm-linux-gcc  -o $@ -c $<

%.o:%.c
	arm-linux-gcc  -o $@ -c $<

clean:
	rm -f *.o *.bin *.dis uart_elf
	
	
	
	
	
	
