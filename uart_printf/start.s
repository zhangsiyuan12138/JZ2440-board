.extern main
.text
.global _start
_start:
      ldr sp,=4096
	  bl  watchdog_init
	  bl  clock_init
	  bl  nand_init
	  bl  sdram_init 
	  
	  ldr r0,=0x30000000
	  mov r1,#4096
	  mov r2,#(1024*16)
	  bl  nand_read

      ldr sp,=0x34000000
	  ldr lr,=main_return
	  ldr pc,=main
main_return:
      b main_return
	  
	  
	  
	  
	  
	  
	  
	  
