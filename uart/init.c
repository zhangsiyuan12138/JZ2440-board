//watchdog
#define WTCON      (*(volatile unsigned long *)0x53000000)

//clock 
#define LOCKTIME   (*(volatile unsigned long *)0x4c000000)
#define MPLLCON    (*(volatile unsigned long *)0x4c000004)
#define CLKDIVN    (*(volatile unsigned long *)0x4c000014)

//sdram 
#define BWSCON     (*(volatile unsigned long *)0x48000000)
#define BANKCON0   (*(volatile unsigned long *)0x48000004)
#define BANKCON1   (*(volatile unsigned long *)0x48000008)
#define BANKCON2   (*(volatile unsigned long *)0x4800000c)
#define BANKCON3   (*(volatile unsigned long *)0x48000010)
#define BANKCON4   (*(volatile unsigned long *)0x48000014)
#define BANKCON5   (*(volatile unsigned long *)0x48000018)
#define BANKCON6   (*(volatile unsigned long *)0x4800001c)
#define BANKCON7   (*(volatile unsigned long *)0x48000020)
#define REFRESH    (*(volatile unsigned long *)0x48000024)
#define BANKSIZE   (*(volatile unsigned long *)0x48000028)
#define MRSRB6     (*(volatile unsigned long *)0x4800002c)
#define MRSRB7     (*(volatile unsigned long *)0x48000030)

void watchdog_init(void)
{
	WTCON=0;
}


void clock_init(void)
{
	CLKDIVN=0x03;	
	__asm__
	(
	"mrc p15,0,r1,c1,c0,0\n"
	"orr r1,r1,#0xc0000000\n"
	"mcr p15,0,r1,c1,c0,0\n"
	);
       MPLLCON=((0x5c<<12)|(0x01<<4)|(0x02));
}

void sdram_init(void)
{
	volatile unsigned long *sdram_base=(volatile unsigned long *)0x48000000;
	sdram_base[0]  = 0x22011110;     
    sdram_base[1]  = 0x00000700;    
    sdram_base[2]  = 0x00000700;    
    sdram_base[3]  = 0x00000700;   
    sdram_base[4]  = 0x00000700;    
    sdram_base[5]  = 0x00000700;    
    sdram_base[6]  = 0x00000700;    
    sdram_base[7]  = 0x00018005;    
    sdram_base[8]  = 0x00018005;    
    sdram_base[9]  = 0x008C04F4;
    sdram_base[10] = 0x000000B1;    
    sdram_base[11] = 0x00000030;    
    sdram_base[12] = 0x00000030;     
	
}

void copy_steppingstone_to_sdram(void)
{
	unsigned int *sour=(unsigned int *)0x00000000;
	unsigned int *dest=(unsigned int *)0x30000000;
	
	while(sour<=(unsigned int *)4096)
	{
		*dest++=*sour++;		
	}
}
















































































