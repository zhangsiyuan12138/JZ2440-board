#define GPFCON      (*(volatile unsigned long *)0x56000050)
#define GPFDAT      (*(volatile unsigned long *)0x56000054)
#define GPGCON      (*(volatile unsigned long *)0x56000060)
#define GPGDAT      (*(volatile unsigned long *)0x56000064)


#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))
#define	GPF4_msk	(3<<(4*2))
#define	GPF5_msk	(3<<(5*2))
#define	GPF6_msk	(3<<(6*2))


#define GPF0_in     (0<<(0*2))
#define GPF2_in     (0<<(2*2))
#define GPG3_in     (0<<(3*2))
#define GPF0_msk    (3<<(0*2))
#define GPF2_msk    (3<<(2*2))
#define GPG3_msk    (3<<(3*2))

int main()
{
        unsigned long dwDat;
      
        GPFCON &= ~(GPF4_msk | GPF5_msk | GPF6_msk);
        GPFCON |= GPF4_out | GPF5_out | GPF6_out;
        GPFCON &= ~(GPF0_msk | GPF2_msk);
        GPFCON |= GPF0_in | GPF2_in;
        GPGCON &= ~GPG3_msk;
        GPGCON |= GPG3_in;

        while(1)
		{
            dwDat = GPFDAT;              
            if (dwDat & (1<<0))      
                GPFDAT |= (1<<4);     
            else    
                GPFDAT &= ~(1<<4);                  
            if (dwDat & (1<<2))         
                GPFDAT |= (1<<5);     
            else    
                GPFDAT &= ~(1<<5);    
  
            dwDat = GPGDAT;                
            if (dwDat & (1<<3))         
                GPFDAT |= (1<<6);    
            else    
                GPFDAT &= ~(1<<6);     
        }
    return 0;
}
