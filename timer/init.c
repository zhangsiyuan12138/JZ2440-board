#include"s3c2440.h"

void watchdog_init(void)
{
	WTCON=0;
}

void clock_init(void)
{
	LOCKTIME=0x00ffffff;
	MPLLCON=((0x5c<<12)|(0x01<<4)|(0x02));     //fclk 200MHZ   hclk  100MHZ    pclk  50MHZ
 	CLKDIVN=0x03;
	
	__asm__
	(
	  "mrc p15,0,r0,c1,c0,0\n"
	  "orr r0,r0,#0xc0000000\n"
	  "mcr p15,0,r0.c1,c0,0\n"
	);
}

void sdram_init(void)
{
	unsigned long *p=(unsigned long *)0x8000000;
    p[0]=0x22011110;
    p[1]=0x00000700;
	p[2]=0x00000700;
	p[3]=0x00000700;
	p[4]=0x00000700;
	p[5]=0x00000700;
	p[6]=0x00000700;
	p[7]=0x00018005;
	p[8]=0x00018005;
	p[9]=0x008c04f4;
	p[10]=0x0000000b1;
	p[11]=0x000000030;
	p[12]=0x000000030;
}


void copy_steppingstone_to_sdram(void)
{
	unsigned int  *sour=(unsigned int *)0x00000000;
	unsigned int  *dest=(unsigned int *)0x30000000;
	
	while(sour<(unsigned int *)4096)
	{
		*dest=*sour;
		dest++;
		sour++;
	}
}

void led_init(void)
{
	GPFCON=(1<<8)|(1<<10)|(1<<12);
}


void timer0_init(void)
{
	TCFG0=99;
	TCFG1=0x03;
	TCON=11;
	TCNTB0=31250;
	TCMPB0=0;
}

void interrupt_init(void)
{
	INTMASK&=(~(1<<10));
}


























