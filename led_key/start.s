.text
.global _start
_start:
        ldr r0,=0x53000000
		ldr r1,=0x00000000
		str r1,[r0]
		
		ldr sp,=1024*4
		
		bl main
lopp1:
        b loop1