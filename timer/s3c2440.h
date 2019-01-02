#ifndef _S3C2440_H_
#define _S3C2440_H_

//看门狗
#define WTCON       (*(unsigned long *)0x53000000)

//时钟
#define LOCKTIME    (*(unsigned long *)0x4c000000)
#define MPLLCON     (*(unsigned long *)0x4c000004)
#define UPLLCON     (*(unsigned long *)0x4c000008)
#define CLKCON      (*(unsigned long *)0x4c00000c)
#define CLKSLOW     (*(unsigned long *)0x4c000010)
#define CLKDIVN     (*(unsigned long *)0x4c000014)
#define CAMDIVN     (*(unsigned long *)0x4c000018)

//sdram
#define BWSCON      (*(unsigned long *)0x48000000)
#define BANKCON0    (*(unsigned long *)0x48000004)
#define BANKCON1    (*(unsigned long *)0x48000008)
#define BANKCON2    (*(unsigned long *)0x4800000C)
#define BANKCON3    (*(unsigned long *)0x48000010)
#define BANKCON4    (*(unsigned long *)0x48000014)
#define BANKCON5    (*(unsigned long *)0x48000018)
#define BANKCON6    (*(unsigned long *)0x4800001C)
#define BANKCON7    (*(unsigned long *)0x48000020)
#define REFRESH     (*(unsigned long *)0x48000024)
#define BANKSIZE    (*(unsigned long *)0x48000028)
#define MRSRB6      (*(unsigned long *)0x4800002C)
#define MRSRB7      (*(unsigned long *)0x48000030)

//GPIO
#define GPFCON      (*(unsigned long *)0x56000050)
#define GPFDAT      (*(unsigned long *)0x56000054)

//TIMER0
#define TCFG0       (*(unsigned long *)0x51000000)
#define TCFG1       (*(unsigned long *)0x51000004)
#define TCON        (*(unsigned long *)0x51000008)
#define TCNTB0      (*(unsigned long *)0x5100000c)
#define TCMPB0     (*(unsigned long *)0x51000010)
#define TCNTO0      (*(unsigned long *)0x51000014)

//INTERRUPT
#define INTMASK     (*(unsigned long *)0x4a000008)
#define SRCPND      (*(unsigned long *)0x4a000000)
#define INTPND      (*(unsigned long *)0x4a000010)
#define INTOFFSET   (*(unsigned long *)0x4a000014)

#endif
