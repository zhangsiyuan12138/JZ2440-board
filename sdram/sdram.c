#define GPFCON (*(unsigned long *)0x56000050) 
#define GPFDAT (*(unsigned long *)0x56000054)
#define LED1_ON   (1<<8)
#define LED2_ON   (1<<10)
#define LED3_ON   (1<<12)

void delay(unsigned long num)
{
	while(--num);
}

int main(void)
{
	GPFCON=LED1_ON|LED2_ON|LED3_ON;
	while(1)
	{
		GPFDAT=(1<<4);
		delay(100000);
		GPFDAT=(1<<5);
		delay(100000);
		GPFDAT=(1<<6);
		delay(100000);
	}
	
	return 0;
}
