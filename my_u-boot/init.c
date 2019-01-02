//watchdog
#define WTCON   (*(volatile unsigned long *)0x53000000)

//clock
#define CLOCKTIME    (*(volatile unsigned long *)0x4c000000)
#define MPLLCON      (*(volatile unsigned long *)0x4c000004)
#define CLKDIVN      (*(volatile unsigned long *)0x4c000014)
#define CAMDIVN      (*(volatile unsigned long *)0x4c000018)


//sdram
#define BWSCON       (*(volatile unsigned long *)0x48000000)
#define BANKCON0     (*(volatile unsigned long *)0x48000004)
#define BANKCON1     (*(volatile unsigned long *)0x48000008)
#define BANKCON2     (*(volatile unsigned long *)0x4800000c)
#define BANKCON3     (*(volatile unsigned long *)0x48000010)
#define BANKCON4     (*(volatile unsigned long *)0x48000014)
#define BANKCON5     (*(volatile unsigned long *)0x48000018)
#define BANKCON6     (*(volatile unsigned long *)0x4800001c)
#define BANKCON7     (*(volatile unsigned long *)0x48000020)
#define REFRESH      (*(volatile unsigned long *)0x48000024)
#define BANKSIZE     (*(volatile unsigned long *)0x48000028)
#define MRSRB6       (*(volatile unsigned long *)0x4800002c)
#define MRSRB7       (*(volatile unsigned long *)0x48000030)



//nand
#define NFCONF   (*(volatile unsigned long *)0x4e000000)
#define NFCONT   (*(volatile unsigned long *)0x4e000004)
#define NFCMMD   (*(volatile unsigned char *)0x4e000008)
#define NFADDR   (*(volatile unsigned char *)0x4e00000C)
#define NFDATA   (*(volatile unsigned char *)0x4e000010)
#define NFSTAT   (*(volatile unsigned char *)0x4e000020)



//uart 
#define  ULCON0      (*(volatile unsigned long *)0x50000000)
#define  UCON0       (*(volatile unsigned long *)0x50000004)
#define  UFCON0       (*(volatile unsigned long *)0x50000008)
#define  UMCON0       (*(volatile unsigned long *)0x5000000c)
#define  UTRSTAT0    (*(volatile unsigned long *)0x50000010)
#define  UERSTAT0    (*(volatile unsigned long *)0x50000014)
#define  UTXH0       (*(volatile unsigned char *)0x50000020)
#define  URXH0       (*(volatile unsigned char *)0x50000024)
#define  UBRDIV0     (*(volatile unsigned long *)0x50000028)

//GPH
#define  GPHCON      (*(volatile unsigned long *)0x56000070)
#define  GPHDAT      (*(volatile unsigned long *)0x56000074)
#define  GPHUP       (*(volatile unsigned long *)0x56000078)



/****************************************    watchdog_init   ********************************************/
void disable_watchdog(void)
{
    WTCON=0;
}

/******************************************    colck_init   ********************************************/
void clock_init(void)
{
   MPLLCON = ((0x5c<<12)|(0x01<<4)|(0x02));
   CLKDIVN = ((1<<1)|(1<<0));      //200 MHZ
 //  CAMDIVN = ((1<<1)|(1<<0));         //1:2:4         200M:100M:50M 


__asm__
 (
     " mrc p15,0,r1,c1,c0,0  \n"
     " orr r1, r1,#0xc0000000 \n"
     " mcr p15,0,r1,c1,c0,0  \n"
 );
   
}

void open_icache(void)
{
  __asm__
  	(
     " mrc p15, 0, r0, c1, c0, 0  \n"
	 " orr r0, r0, #(1<<12)       \n"
	 " mcr	p15, 0, r0, c1, c0, 0 \n"
    );
}

/******************************************    sdram_init   *******************************************/

void sdram_init(void)
{
      BWSCON =  0x22011110	;      //BWSCON
      BANKCON0 =  0x00000700;      //BANKCON0
      BANKCON1 =0x00000700;	       //BANKCON1
      BANKCON2 =  0x00000700;	   //BANKCON2
      BANKCON3 =  0x00000700;	   //BANKCON3
      BANKCON4 =  0x00000700;	   //BANKCON4
      BANKCON5 =0x00000700;	       //BANKCON5
      BANKCON6 =0x00018005;	       //BANKCON6
      BANKCON7 = 0x00018005;	   //BANKCON7
      REFRESH  =0x008C04F4	;      // REFRESH
	  BANKSIZE = 0x000000B1;	   //BANKSIZE
	  MRSRB6 = 0x00000030;	       //MRSRB6
	  MRSRB7 =  0x00000030	;      //MRSRB7
}


/******************************************    nand_flash_init   ********************************************/

void select_chip(void)
{
	NFCONT &= ~(1<<1);
}

void disselect_chip(void)
{
	NFCONT |= (1<<1);
}

void write_command(unsigned char cmd)
{
	NFCMMD=cmd;
   volatile int i;
	for (i = 0; i < 10; i++);

}

unsigned char   read_data(void)
{
    return NFDATA;
}

void write_addr(unsigned int addr)
{
    unsigned int row,col;
	int i=0;
	row=addr/2048;
	col=addr%2048;

	NFADDR=  0xff & col;
	for (i = 0; i < 10; i++);
	NFADDR=(col>>8)& 0xff;
	for (i = 0; i < 10; i++);
	
	NFADDR=row& 0xff;
	for (i = 0; i < 10; i++);
	NFADDR=(row>>8)& 0xff;
	for (i = 0; i < 10; i++);
	NFADDR=(row>>16)& 0xff;
	for (i = 0; i < 10; i++);
}

int nand_ready(void)
{
    return (NFSTAT & 1);  
}


void nand_init(void)
{
   NFCONF = (0<<12|1<<8|0<<4);
   NFCONT = (1<<4|1<<1|1<<0); 
}

void nand_read(unsigned int sour,unsigned char* dest,int copy_size)
{
   int col=sour % 2048;
   int i=0;
  
   
    
         select_chip();
	while(i<copy_size)    
		{
			
	          write_command(0x00);
	      
	          write_addr(sour);
	     
	          write_command(0x30);
			
			  while(!nand_ready());
	       
             for(;  (col<2048)&&(i<copy_size);col++)  //page read
             	{
                     dest[i]=read_data();
                     sour++;  i++;        
			    }
			 col=0;
		} 
  
	disselect_chip();
}




/******************************************    copy_uboot_to_sdram   ********************************************/
int nand_boot(void)
{
    volatile unsigned long* top = (volatile unsigned long *)0x00000000;
    int value=*top;
	*top=1234;
	if(*top==1234)     //ÅÐ¶ÏÊÇ nor_flash »¹ÊÇ nand_flash
		{
		  *top=value;
	      return 1;
		}
	else return 0;	
}


void copy_uboot_to_sdram(unsigned char* sour1,unsigned char *dest,int copy_size)
{
      int i=0;
	  unsigned char *sour = sour1;
      if(nand_boot())  // nand_boot
      {
          while(i<copy_size)
          	{
               dest[i]=sour[i];i++;
		    }
	  }
	  else              //nor_boot
	  	{
            nand_read((unsigned long)sour,dest,copy_size);
	    }
}


/*********************************************clean_bss*************************************************/
void clean_bss(void)
{
    extern long __bss_end,  __bss_start;
    int* p = &__bss_start;
    for(;p < &__bss_end ;p++) *p=0;
}


/********************************************uart_init*****************************************************/


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


void puts(char *str)
{
  while(*str) putc(*str++);

}




void puthex(unsigned int val)
{
	/* 0x1234abcd */
	int i;
	int j;
	
	puts("0x");

	for (i = 0; i < 8; i++)
	{
		j = (val >> ((7-i)*4)) & 0xf;
		if ((j >= 0) && (j <= 9))
			putc('0' + j);
		else
			putc('A' + j - 0xa);
		
	}
	
}

