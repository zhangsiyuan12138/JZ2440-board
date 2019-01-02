#define INTMSK     (*(volatile unsigned long *)0x4a000008)
#define INTMOD     (*(volatile unsigned long *)0x4a000004)
#define INTOFFSET  (*(volatile unsigned long *)0x4a000014)
#define SRCPND     (*(volatile unsigned long *)0x4A000000)
#define INTPND     (*(volatile unsigned long *)0x4A000010)

#include"iic.h"

void interrupt_init(void)
{
	INTMSK=0xffffffff;
	INTMOD = 0x0;	  
}


void  iic_interrupt(void)
{
	unsigned long oft=INTOFFSET;
	
	if(oft == 4 )
		EINTPEND=1<<7;
	  SRCPND = 1<<oft;	
	  INTPND = INTPND;	 
        
	iic_interrupt_svr();
}









