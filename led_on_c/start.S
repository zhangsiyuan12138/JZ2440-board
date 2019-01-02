
.text
.global _start
_start:
        LDR R0,=0x53000000
		MOV R1,#0x0
		STR R1,[R0]
		LDR SP,=1024*4
        BL main
loop1:
        B loop1
		