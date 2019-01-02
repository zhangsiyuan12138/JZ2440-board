#include"s3c2440.h"
/*
 * LED1,LED2,LED4对应GPF4、GPF5、GPF6
 */
#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))

#define	GPF4_msk	(3<<(4*2))
#define	GPF5_msk	(3<<(5*2))
#define	GPF6_msk	(3<<(6*2))

/*
 * S2,S3,S4对应GPF0、GPF2、GPG3
 */
#define GPF0_eint     (0x2<<(0*2))
#define GPF2_eint     (0x2<<(2*2))
#define GPG3_eint     (0x2<<(3*2))

#define GPF0_msk    (3<<(0*2))
#define GPF2_msk    (3<<(2*2))
#define GPG3_msk    (3<<(3*2)) 


void disable_watch_dog(void)
{
	WTCON = 0;
}

void led_init(void)
{
	 // LED1,LED2,LED4对应的3根引脚设为输出
    GPFCON &= ~(GPF4_msk | GPF5_msk | GPF6_msk);
    GPFCON |= GPF4_out | GPF5_out | GPF6_out;
}

void interrupt_init(void)
{
	   // S2,S3对应的2根引脚设为中断引脚 EINT0,ENT2
    GPFCON &= ~(GPF0_msk | GPF2_msk);
    GPFCON |= GPF0_eint | GPF2_eint;

    // S4对应的引脚设为中断引脚EINT11
    GPGCON &= ~GPG3_msk;
    GPGCON |= GPG3_eint;

	EINTMASK &= (~(1<<11）);
	INTMSK &= (~(1<<0))&(~(1<<2))&(~(1<<5));
	PRIORITY = (PRIORITY&((~0x01) | (0x3 << 7))) | (0x0 << 7);
}

































