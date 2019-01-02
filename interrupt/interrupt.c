#include"s3c2440.h"

void eint_interrupt(void)
{
	unsigned long offset = INTOFFSET;

	switch (offset)
	{
		case 0:
		{
			 GPFDAT |= (0x7<<4);
			GPFDAT &= ~(1<<4);
			break;
		}

		case 2:
		{
			 GPFDAT |= (0x7<<4);
			GPFDAT &= ~(1<<5);
			break;
		}

		case 5:
		{
			 GPFDAT |= (0x7<<4);
			GPFDAT &= ~(1 << 6);
		    break;
		}
		defult:break;
	}

	if (offset == 5) EINTPEND = (1 << 11);
	SRCPND = 1 << offset;
	INTPND = 1 << offset;
}


























