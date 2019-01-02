typedef struct 
{
	int  NFCONF;
	int  NFCONT;
	int  NFCMMD;
	int  NFADDR;
	int  NFDATA;
	int  NFMECCD0;
	int  NFMECCD1;
	int  NFSECCD;
	int  NFSTAT;
	int  NFSTAT0;
	int  NFSTAT1;
    int  NFMECC0;
    int  NFMECC1;
    int  NFSECC;
	int  NFSBLK;
	int  NFEBLK;
}nand_p;
nand_p *nand_register=(nand_p *)0x4e000000;

/*static fun*/
static void nand_enable_chip(void)
{
	int i=0;
	nand_register->NFCONT&=~(1<<1);
	 for(i=0; i<10; i++);
}

static void nand_unable_chip(void)
{
	nand_register->NFCONT|=(1<<1);
}

static void nand_busy(void)
{
	int i=0;
	unsigned char *p=(unsigned char *)& nand_register->NFSTAT;
   while(!(*p&1))
	    for(i=0; i<10; i++);
}

static void nand_cmd(unsigned char cmd)
{
	unsigned char *p=(unsigned char *)&nand_register->NFCMMD;
    *p=cmd;
}

static void nand_addr(unsigned int addr)
{
    int i;
    volatile unsigned char *p = (volatile unsigned char *)&nand_register->NFADDR;
    
    *p = addr & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 9) & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 17) & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 25) & 0xff;
    for(i=0; i<10; i++);
	
}

void nand_reset(void)
{
	nand_enable_chip();
	nand_cmd(0xff);
	nand_busy();
	nand_unable_chip();
}

static char nand_data_read(void)
{
 unsigned char *p = ( unsigned char *)&nand_register->NFDATA;
    return *p;
}


/*extern fun*/
void nand_init(void)
{	
	nand_register->NFCONF=(0<<12)|(3<<8)|(0<<4);
	nand_register->NFCONT=(1<<4)|(1<<1)|(1<<0);
	nand_reset();
}

void nand_read(unsigned char* dest_addr,unsigned long star_addr,unsigned int size)
{
	int i=0,j=0;
	if((star_addr&2047)||(size&2047)) return ;
	nand_enable_chip();
	for(i=star_addr;i<(star_addr+size);)
	{	
		nand_cmd(0x00);
		nand_addr(i);
		nand_cmd(0x30);
		nand_busy();
		for(j=0;j<2048;j++,i++)
		{
			*dest_addr=nand_data_read();
			dest_addr++;
		}		
	}
	nand_unable_chip();
	return ;
}































