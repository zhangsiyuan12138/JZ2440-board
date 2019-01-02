
objs:= start.o init.o uart.o nand.o main.o my_stdio.o  lcd_drv.o lcd_buffer.o lcd_lib.o  lib/libc.a 

CC            =arm-linux-gcc 
LD            =arm-linux-ld 
AR            =arm-linux-ar 
OBJCOPY       =arm-linux-objcopy 
OBJDUMP       =arm-linux-objdump

INCLUDEDIR    :=$(shell pwd)/include 
CFLAGS        :=-Wall -O2
CPPFLAGS      :=-nostdinc -I$(INCLUDEDIR)

export 	CC LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

uart.bin:$(objs)
	arm-linux-ld -Tuart.lds -o uart_elf $^ libgcc.a
	arm-linux-objcopy -O binary -S uart_elf $@
	arm-linux-objdump -D -m arm uart_elf > uart.dis

.PHONY:lib/libc.a
lib/libc.a:
	cd lib;make;cd ..


%.o:%.s
	$(CC) $(CPPFLAGS) $(FLAGS)-o $@ -c $<

%.o:%.c
	$(CC) $(CPPFLAGS) $(FLAGS) -o $@ -c $<

clean:
	make  clean -C lib
	rm -f *.o *.bin *.dis uart_elf
	
	
	
	
	
	
