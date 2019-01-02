.extern main
.text
.global _start
_start:
      ldr sp,=4096
	  bl  watchdog_init
	  bl  clock_init
	  bl  sdram_init 
	  bl  copy_steppingstone_to_sdram
	  ldr pc,=sdram
sdram:
      ldr sp,=0x34000000
	  ldr lr,=main_return
	  ldr pc,=main    
main_return:
      b main_return
	  
	  
	  
	  
	  
	  
	  
	  
