#include"lcd_drv.h"

//gpio
#define  GPBCON    (*(unsigned long *)0x56000010)
#define  GPBDAT    (*(unsigned long *)0x56000014)
#define  GPBUP     (*(unsigned long *)0x56000018)

#define  GPCCON    (*(unsigned long *)0x56000020)
#define  GPCDAT    (*(unsigned long *)0x56000024)
#define  GPCUP     (*(unsigned long *)0x56000028)

#define  GPDCON    (*(unsigned long *)0x56000030)
#define  GPDDAT    (*(unsigned long *)0x56000034)
#define  GPDUP     (*(unsigned long *)0x56000038)

#define  GPGCON    (*(unsigned long *)0x56000060)    
#define  GPGDAT    (*(unsigned long *)0x56000064)
#define  GPGUP     (*(unsigned long *)0x56000068)

//lcd_register
#define  LCDCON1   (*(unsigned long *)0x4d000000)
#define  LCDCON2   (*(unsigned long *)0x4d000004)
#define  LCDCON3   (*(unsigned long *)0x4d000008)
#define  LCDCON4   (*(unsigned long *)0x4d00000c)
#define  LCDCON5   (*(unsigned long *)0x4d000010)
#define  LCDSADDR1 (*(unsigned long *)0x4d000014)
#define  LCDSADDR2 (*(unsigned long *)0x4d000018)
#define  LCDSADDR3 (*(unsigned long *)0x4d00001c)
#define  TPAL      (*(unsigned long *)0x4d000050)


unsigned long lcd_base_addr=0x30400000;
int bpp=16;
int x_size=640;
int y_size=480;


void lcd_port_init(void)
{
	GPCCON=0xffffffff;
	GPCDAT=0xaaaaaaaa;
	GPDCON=0xffffffff;
	GPDDAT=0xaaaaaaaa;
	
	GPBCON &= ~(3<<(0*2));  
    GPBCON |= (1<<(0*2));
    GPBDAT &= ~(1<<0);			
	

}


void tft_lcd_init(void)
{
	LCDCON1=(1<<8)|(3<<5)|(0xc<<1)|(0);
	LCDCON2=((32-1)<<24)|((480-1)<<14)|((10-1)<<6)|(2-1);
	LCDCON3=((48-1)<<19)|((640-1)<<8)|(16-1);
    LCDCON4=(96-1);	
	LCDCON5=(1<<11)|(1<<9)|(1<<8)|(1<<1);
	
	LCDSADDR1=((0x30400000>>22)<<21)|(0x1fffff&(0x30400000>>1));
	LCDSADDR2=((0x30400000+(480+1)*(640+1)*2)>>1)&0x1fffff;
	LCDSADDR3=(0<<1)|(640*2/2);
	
	TPAL=0;
	lcd_base_addr=0x30400000;
	bpp=16;
	x_size=640;
	y_size=480;
}

void lcd_poweron(void)
{
	 GPGCON = (GPGCON & (~(3<<8))) | (3<<8);  
     GPGUP  = (GPGUP & (~(1<<4))) | (1<<4); 
	
	    LCDCON5 = (LCDCON5 & (~(1<<5))) | (0<<5);  
        LCDCON5 = (LCDCON5 & (~(1<<3))) | (1<<3);  
}



void lcd_envidon(void)
{
        LCDCON1 |= 1;         
		GPBDAT |= (1<<0);			
}




























































