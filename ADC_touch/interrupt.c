#include"s3c24xx.h"


void (*isr_handle_isr[32])(void);

void interrupt_init(void)
{
	INTMOD=0x0;
	INTMSK=0xffffffff;
}
 

void adc_interrupt(void)
{
	unsigned long　offset=INTOFFSET;
	
	SRCPND=1<<offset;	
	INTPND=INTPND;	
	isr_handle_isr[oft]();
}













































