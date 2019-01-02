.extern main
.text
.global _start
_start:

@ �쳣������

@ 0x00  ��λ
b Reset

@ 0x04  ָ��δ����
Undefine_instruct:
b Undefine_instruct

@ 0x08  ����ж�
Software_interrupt:
b Software_interrupt

@ 0x0c  Ԥȡָ�ж�
Prefetch_abort:
b Prefetch_abort

@ 0x10  ���ݷ����ж�
Data_abort:
b Data_abort

@ 0x14 ����

@ 0x18 �ⲿ�����ж�
b Handle_irq

@ 0x1c  �����ж�
Fiq:
b Fiq

Reset:
    ldr sp,=4096        @ ��λ�Զ����볬���û�ģʽ
	bl disable_watch_dog

	msr cpsr_c,#0xd2    @ �����ж�ģʽ
	ldr sp,=3072

	msr cpsr_c,#0xd3    @ ���볬���û�ģʽ
	ldr sp,=4096
	bl led_init         
	bl interrupt_init

	msr cpsr_c,#0x5f   @ ���жϣ�������ϵͳģʽ
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































































