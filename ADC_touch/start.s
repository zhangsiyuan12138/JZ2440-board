.extern main interrupt_init   adc_interrupt
.text
.global _start
_start:

    b   Reset

HandleUndef:
    b   HandleUndef 
 
HandleSWI:
    b   HandleSWI

HandlePrefetchAbort:
    b   HandlePrefetchAbort

HandleDataAbort:
    b   HandleDataAbort

HandleNotUsed:
    b   HandleNotUsed

    b   HandleIRQ

HandleFIQ:
    b   HandleFIQ

Reset:
      ldr sp,=4096
	  bl  watchdog_init
	  bl  clock_init
	  bl  nand_init
	  bl  sdram_init 
	  
	  ldr r0,=0x30000000
	  mov r1,#4096
	  mov r2,#(1024*16)
	  bl  nand_read
	  
	  msr cpsr_c,#0xd2
	  ldr sp,=0x31000000
	  
	  msr cpsr_c,#0xdf
	  ldr sp,=0x34000000
	  
	  ldr lr,=interrupt_return 
	  ldr pc,=interrupt_init
interrupt_return:
      msr cpsr_c,#0x5f

	  ldr lr,=main_return
	  ldr pc,=main
main_return:
      b main_return
	  
HandleIRQ:
      sub lr,lr,#4
      stmdb sp!,{r0-r12,lr}

      ldr lr,=adc_return 
      ldr pc,=adc_interrupt
adc_return:
      ldmia sp!,{r0-r12,pc}^	  
	  
	  
	  
	  
	  
	  
