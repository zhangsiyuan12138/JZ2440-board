.extern main  interrup_init  iic_interrupt
.text
.global _start
_start:

b Reset

Undefine_Instrution:
b  Undefine_Instrution

Software_Interrupt:
b Software_Interrupt

Prefect_Abort:
b  Prefect_Abort

Data_Abort:
b  Data_Abort

b  IRQ

FIQ:
b: FIQ

Reset:
      ldr sp,=4096            @超级用户模式
	  bl  watchdog_init
	  bl  clock_init
	  bl  nand_init
	  bl  sdram_init 
	  
	  ldr r0,=0x30000000
	  mov r1,#4096
	  mov r2,#(1024*16)
	  bl  nand_read         
	  
	  msr cpsr_c #0xd2      @中断模式
	  ldr sp,=0x31000000
	  
	  msr cpsr_c,#0xdf      @系统模式
	  ldr sp,=0x34000000

	  ldr lr,=interrupt_return  
	  ldr pc,=interrup_init
interrupt_return:
      msr cpsr_c,#0x5f     @开中断   系统模式
	  
	  ldr lr,=main_return 
	  ldr pc,=main
main_return:
      b main_return
	  
	  
IRQ:
      sub lr,lr,#4
	  stmdb sp!,{r0-r12,lr}
	  
	  ldr lr,=IRQ_return 
	  ldr pc,=iic_interrupt
IRQ_return:
      ldmia sp!,{r0-r12,pc}^
	  
	  
	  
	  
	  
	  
	  
	  
