.extern main
.text
.global _start
_start:

@ 异常向量表

@ 0x00  复位
b Reset

@ 0x04  指令未定义
Undefine_instruct:
b Undefine_instruct

@ 0x08  软件中断
Software_interrupt:
b Software_interrupt

@ 0x0c  预取指中断
Prefetch_abort:
b Prefetch_abort

@ 0x10  数据访问中断
Data_abort:
b Data_abort

@ 0x14 保留

@ 0x18 外部访问中断
b Handle_irq

@ 0x1c  快速中断
Fiq:
b Fiq

Reset:
    ldr sp,=4096        @ 复位自动进入超级用户模式
	bl disable_watch_dog

	msr cpsr_c,#0xd2    @ 进入中断模式
	ldr sp,=3072

	msr cpsr_c,#0xd3    @ 进入超级用户模式
	ldr sp,=4096
	bl led_init         
	bl interrupt_init

	msr cpsr_c,#0x5f   @ 开中断，并进入系统模式
	ldr lr,=loop_main
	ldr pc,=main
loop_main:
         b loop_main

Handle_irq:
    sub lr,lr,#4
	stmdb sp!,{r0-r12,lr}

	ldr lr,=eint_return
	ldr pc,=eint_interrupt
eint_return:
    ldmia sp!,{r0-r12,pc}^































































