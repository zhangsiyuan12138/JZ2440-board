.equ MENRI_BASE, 0x48000000
.equ SDRAM_BASE, 0x30000000

.text
.global _start
_start:
        bl close_watchdog
		bl sdram_set
		bl copy_sram_to_sdram
		ldr pc,=on_sdram
on_sdram:
		ldr sp,=0x34000000
		bl main
loop1:
       b loop1
		
close_watchdog:
        ldr r0,=0x53000000
        mov r1,#0x0		
        str r1,[r0]
        mov pc,lr

copy_sram_to_sdram:
        ldr r0,=SDRAM_BASE
        mov r1,#0x0
        mov r3,#4*1024
l:    
        ldr r4,[r1], #4
        str r4,[r0],#4	
		cmp r1, r3  
		bne l
		 
		 mov pc,lr 
		 
sdram_set:
        mov r1,#MENRI_BASE
		adrl r2,mem_reg_set
		add r3,r1,#52
m:
        ldr r4,[r2],#4
		str r4,[r1],#4
		cmp r1,r3
		bne m
		
		mov pc,lr

.align 4
mem_reg_set:
.long  0x22011110
.long  0x00000700
.long  0x00000700
.long  0x00000700 
.long  0x00000700 			  
.long  0x00000700 			  
.long  0x00000700 
.long  0x00018005
.long  0x00018005
.long  0x008c07a3
.long  0x000000b1
.long  0x00000030
.long  0x00000030

