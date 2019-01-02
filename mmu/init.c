
void disable_watch_dog(void)
{
	(*(unsigned long *)0x53000000)=0;
}


void enable_sdram(void)
{
	unsigned long sdram_conf[]={0x22011110,0x00000700,0x00000700,0x00000700,0x00000700,0x00000700,0x00000700,0x00018005,0x00018005,0x008c07a3,0x000000b1,0x00000030,0x00000030};
    unsigned long* sdram_register=(unsigned long *)0x48000000;
	int i=0;
	for(i=0;i<13;i++)  sdram_register[i]=sdram_conf[i];
}



void copy_2th_to_sdram(void)
{
	unsigned int *sour=(unsigned int *)2048;
	unsigned int *dest=(unsigned int *)0x30004000;
	while(sour<(unsigned int *)4096)
	{
		
		*dest=*sour;
		sour++;
		dest++;
	}	
}



void creat_page_table(void)
{
	#define SET_AP       (3<<10)
	#define SET_DOMINE   (0<<5)
	#define SET_4	     (1<<4)
	#define SET_C        (1<<3)
	#define SET_B        (1<<2)
	#define SET_0        (2)
	
	#define mmu_cache  (SET_AP|SET_DOMINE|SET_4|SET_C|SET_B|SET_0)
	#define mmu        (SET_AP|SET_DOMINE|SET_4|SET_0)
	
	unsigned long vir_ad=0,phy_ad=0;
	unsigned long *mmu_base_ad=(unsigned long *)0x30000000;
	
	/*steppingstone*/
	vir_ad=0;
	phy_ad=0;
	*(mmu_base_ad+(vir_ad>>20))=(phy_ad & 0xfff00000)|mmu_cache;

	/*gpio*/
	vir_ad=0xa0000000;
	phy_ad=0x56000000;
	*(mmu_base_ad +( vir_ad>>20))=(phy_ad & 0xfff00000)|mmu;

	/*sdram*/
     vir_ad=0xb0000000;
     phy_ad=0x30000000;
	 while(vir_ad<0xb4000000)
	 {
		 *(mmu_base_ad +(vir_ad>>20))=(phy_ad&0xfff00000)|mmu_cache;
		 vir_ad+=0x100000;
		 phy_ad+=0x100000;
	 }
}


void enable_mmu(void)
{
	unsigned long ttb=0x30000000;
  	__asm__
	(
	  "mov r0,#0\n"                        /**/
	  "mcr p15,0,r0,c7,c7,0\n"             /*使无效icache dcache*/
	  "mcr p15,0,r0,c7,c10,4\n"            /*清空*/
	  "mcr p15,0,r0,c8,c7,0\n"             /*使无效itlb dtlb*/  
	  "mov r4,%0\n"                        /*页表基地址*/
	  "mcr p15,0,r4,c2,c0,0\n"             /**/
	  "mvn r0,#0\n"                        /**/
	  "mcr p15,0,r0,c3,c0,0\n"             /*域访问控制器为可读写*/
	  "mrc p15,0,r0,c1,c0,0\n"             /*读控制器的值*/         
	  "bic r0,r0,#0x3000\n"                /*先清除 再是能*/         
	  "bic r0,r0,#0x0300\n"                /**/          
	  "bic r0,r0,#0x0087\n"                /**/      
	  "orr r0,r0,#0x0002\n"                /*使能对齐检查*/    
	  "orr r0,r0,#0x0004\n"                /*是能cache_buff*/        
	  "orr r0,r0,#0x1000\n"                /*使能icache*/               
	  "orr r0,r0,#0x0001\n"                /*使能mmu*/      
          "mcr p15,0,r0,c1,c0,0\n"            
          :                                /**/
	  :"r"(ttb)                            /**/
	);
}












