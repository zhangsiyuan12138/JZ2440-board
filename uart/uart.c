//uart 
#define  ULCON0      (*(volatile unsigned long *)0x50000000)
#define  UCON0       (*(volatile unsigned long *)0x50000004)
#define UFCON0       (*(volatile unsigned long *)0x50000008)
#define UMCON0       (*(volatile unsigned long *)0x5000000c)
#define  UTRSTAT0    (*(volatile unsigned long *)0x50000010)
#define  UERSTAT0    (*(volatile unsigned long *)0x50000014)
#define  UTXH0       (*(volatile unsigned char *)0x50000020)
#define  URXH0       (*(volatile unsigned char *)0x50000024)
#define  UBRDIV0     (*(volatile unsigned long *)0x50000028)

//GPH
#define  GPHCON      (*(volatile unsigned long *)0x56000070)
#define  GPHDAT      (*(volatile unsigned long *)0x56000074)
#define  GPHUP       (*(volatile unsigned long *)0x56000078)


void uart0_init(void)
{
	GPHCON|=0xa0;
	GPHUP=0x0c;
	
	ULCON0=0x03;	
	UCON0=0x05;
	UFCON0=0x00;     
    UMCON0=0x00;     
	UBRDIV0=((50000000/(115200*16))-1);	
}

unsigned char getc(void)
{
	while(!(UTRSTAT0 & 0x01));
	return URXH0;
}


void putc(unsigned char date)
{
	while(!(UTRSTAT0 & 0x02));
	UTXH0=date;
}



