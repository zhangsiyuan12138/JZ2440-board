.text
.global _start
_start:
        ldr sp,=4096
		bl  disable_watch_dog
		bl  sdram_init
		bl  nand_init
		ldr r0,=0x30000000
		mov r1,#4096
		mov r2,#2048
		bl  nand_read
		ldr sp,=0x34000000
		ldr lr,=loop1
		ldr pc,=0x30000000
loop1: 
      b loop1