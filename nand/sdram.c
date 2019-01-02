void disable_watch_dog(void)
{
	(*(unsigned long *)0x53000000)=0;
}

void sdram_init(void)
{
	unsigned long p[]={	0x22011110,
						0x00000700,
						0x00000700,
						0x00000700,
						0x00000700,
						0x00000700,
						0x00000700,
						0x00018005,
						0x00018005,
						0x008c07a3,
						0x000000b1,
						0x00000030,
						0x00000030 };
	unsigned long *sdram_base=(unsigned long *)0x48000000;
	int i=0;
	for(;i<13;i++) sdram_base[i]=p[i];
}