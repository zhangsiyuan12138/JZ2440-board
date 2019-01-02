.extern main timer0_interrupt
.text
.global _start
_start:

@ 异常向量表
@0x00 reset
b Reset

@0x04 未定义指令异常
Handle_Undef:
b Handle_Undef
  
@0x08 软件中断异常
Handle_SWI:
b Handle_SWI

@0x0c 预取指令异常
Handle_PrefectchAbort:
b  Handle_PrefectchAbort

@0x10 数据访问异常
Handle_DateAbort:
b Handle_DateAbort

@0x14  保留异常
Handle_NotUsed:
b Handle_NotUsed

@0x18  外部中断请求异常
b  Handle_IRQ

@0x1c  快速中断请求异常
Handle_FIQ:
b   Handle_FIQ

Reset:                   @复位进入超级用户模式
      ldr sp,=4096
      bl watchdog_init
	  bl clock_init
	  bl sdram_init
	  bl copy_steppingstone_to_sdram
	  ldr pc,=on_sdram
on_sdram:  
	  msr cpsr_c,#0xd2   @进入中断模式
      ldr sp,=4096	

	  msr cpsr_c, #0xdf    @ 进入系统模式
      ldr sp, =0x34000000
	  
	  bl led_init
	  bl timer0_init
	  bl interrupt_init  
      msr cpsr_c,#0x5f  @进入系统模式
	  
      ldr lr,=main_loop
	  ldr pc,=main 
main_loop:
       b   main_loop 

Handle_IRQ:
      sub lr,lr,#4
      stmdb sp!,{r0-r12,lr}	   
	  	      
	  ldr lr,=IRQ_return
	  ldr pc,=timer0_interrupt
IRQ_return:
      ldmia sp!,{r0-r12,pc}^
	         
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  




