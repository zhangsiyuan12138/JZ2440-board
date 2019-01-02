
.text
.global _start
_start:
        ldr r0,=0x53000000
		mov r1,#0x0
		str r1,[r0]
		
		ldr sp,=1024*4
		
		bl main
loop1:
         b loop1 