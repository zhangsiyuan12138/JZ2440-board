#define BUSY          1

#define NAND_SECTOR_SIZE_LP    2048
#define NAND_BLOCK_MASK_LP     (NAND_SECTOR_SIZE_LP - 1)

typedef struct 
{
    int   NFCONF;
    int   NFCONT;
    int   NFCMD;
    int   NFADDR;
    int   NFDATA;
    int   NFMECCD0;
    int   NFMECCD1;
    int   NFSECCD;
    int   NFSTAT;
    int   NFESTAT0;
    int   NFESTAT1;
    int   NFMECC0;
    int   NFMECC1;
    int   NFSECC;
    int   NFSBLK;
    int   NFEBLK;
} S3C2440_NAND;

static S3C2440_NAND *s3c2440nand = (S3C2440_NAND *)0x4e000000;

/* 供外部调用的函数 */
void nand_init(void);
void nand_read(unsigned char *buf, unsigned long start_addr, int size);

/* S3C2440的NAND Flash处理函数 */
static void nand_reset(void);
static void wait_idle(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void write_cmd(int cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);


/* 复位 */
static void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);  // 复位命令
    wait_idle();
    nand_deselect_chip();
}

/* 等待NAND Flash就绪 */
static void wait_idle(void)
{
    int i;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;
    while(!(*p & BUSY))
        for(i=0; i<10; i++);
}

/* 发出片选信号 */
static void nand_select_chip(void)
{
    int i;
    s3c2440nand->NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);    
}

/* 取消片选信号 */
static void nand_deselect_chip(void)
{
    s3c2440nand->NFCONT |= (1<<1);
}

/* 发出命令 */
static void write_cmd(int cmd)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
    *p = cmd;
}

/* 发出地址 */
static void write_addr(unsigned int addr)
{
	int i;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;
	int col, page;

	col = addr & NAND_BLOCK_MASK_LP;
	page = addr / NAND_SECTOR_SIZE_LP;
	
	*p = col & 0xff;			/* Column Address A0~A7 */
	for(i=0; i<10; i++);		
	*p = (col >> 8) & 0x0f; 	/* Column Address A8~A11 */
	for(i=0; i<10; i++);
	*p = page & 0xff;			/* Row Address A12~A19 */
	for(i=0; i<10; i++);
	*p = (page >> 8) & 0xff;	/* Row Address A20~A27 */
	for(i=0; i<10; i++);
	*p = (page >> 16) & 0x03;	/* Row Address A28~A29 */
	for(i=0; i<10; i++);
}

/* 读取数据 */
static unsigned char read_data(void)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;
    return *p;
}


/* 初始化NAND Flash */
void nand_init(void)
{
		#define TACLS   0
		#define TWRPH0  3
		#define TWRPH1  0   

		
		/* 设置时序 */
        s3c2440nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
        /* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
        s3c2440nand->NFCONT = (1<<4)|(1<<1)|(1<<0); 
		/* 复位NAND Flash */
		nand_reset();
}


/* 读函数 */
void nand_read(unsigned char *buf, unsigned long start_addr, int size)
{
    int i, j;
    if ((start_addr & NAND_BLOCK_MASK_LP) || (size & NAND_BLOCK_MASK_LP))
	{
        return ;    /* 地址或长度不对齐 */
    }
    /* 选中芯片 */
    nand_select_chip();
    for(i=start_addr; i < (start_addr + size);) 
	{
      /* 发出READ0命令 */
      write_cmd(0);
      /* Write Address */
      write_addr(i);
      write_cmd(0x30);		
      wait_idle();
      for(j=0; j < NAND_SECTOR_SIZE_LP; j++, i++) //一页2k
	  {
         *buf = read_data();
          buf++;
      }
    }
    /* 取消片选信号 */
    nand_deselect_chip();
    return ;
}

