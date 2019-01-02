#include"s3c2440.h"


void timer0_interrupt(void)
{
	if(INTOFFSET==10)  GPFDAT=~(GPFDAT&(0x7<<4));	
	SRCPND=1<<INTOFFSET;
	INTPND=INTPND;
	
}