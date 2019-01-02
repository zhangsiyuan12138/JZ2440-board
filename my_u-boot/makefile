OBJS := start.o init.o tag.o  main.o
CFLAGS := -O2 -Wall
CPPFLAGS := -nostdinc -fno-builtin

CC = arm-linux-gcc 
LD = arm-linux-ld  
OBJCOPY = arm-linux-objcopy  
OBJDUMP = arm-linux-objdump  

uboot.bin: ${OBJS}
	${LD} -Tuboot.lds -o uboot.elf $^
	${OBJCOPY} -O binary -S uboot.elf $@  
	${OBJDUMP} -D -m arm uboot.elf > uboot.dis

%.o:%.c 
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<

%.o:%.s 
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<


clean:
	rm -f *.o *.bin *.elf *.dis


















