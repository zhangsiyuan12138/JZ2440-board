#ifndef _S3C2440_H_
#define _S3C2440_H_


//ø¥√≈π∑
#define WTCON    (*(unsigned long *)0x53000000)

//GPIO
#define GPFCON   (*(unsigned long *)0x56000050)
#define GPFDAT   (*(unsigned long *)0x56000054)
#define GPFUP    (*(unsigned long *)0x56000058)
#define GPGCON   (*(unsigned long *)0x56000060)
#define GPGDAT   (*(unsigned long *)0x56000064)
#define GPGUP    (*(unsigned long *)0x56000068)

//interrupt
#define INTMSK   (*(unsigned long *)0x4a000008)
#define PRIORITY (*(unsigned long *)0x4a00000c)
#define SRCPND   (*(unsigned long *)0x4a000000)
#define INTPND   (*(unsigned long *)0x4a000010)
#define INTOFFSET (*(unsigned long *)0x4a000014)

#define EINTMASK (*(unsigned long *)0x560000a4)
#define EINTPEND (*(unsigned long *)0x560000a8)



#endif

