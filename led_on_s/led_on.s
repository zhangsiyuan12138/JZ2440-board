
.text
.global _start
_start:
	    LDR R0,=0x56000050
		MOV R1,#0x00000100
		STR R1,[R0]
		
		LDR R0,=0x56000054
		MOV R1,#0x00000000
		STR R1,[R0]
main_loop:
           B  main_loop