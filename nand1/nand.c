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

/* ���ⲿ���õĺ��� */
void nand_init(void);
void nand_read(unsigned char *buf, unsigned long start_addr, int size);

/* S3C2440��NAND Flash������ */
static void nand_reset(void);
static void wait_idle(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void write_cmd(int cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);


/* ��λ */
static void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);  // ��λ����
    wait_idle();
    nand_deselect_chip();
}

/* �ȴ�NAND Flash���� */
static void wait_idle(void)
{
    int i;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;
    while(!(*p & BUSY))
        for(i=0; i<10; i++);
}

/* ����Ƭѡ�ź� */
static void nand_select_chip(void)
{
    int i;
    s3c2440nand->NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);    
}

/* ȡ��Ƭѡ�ź� */
static void nand_deselect_chip(void)
{
    s3c2440nand->NFCONT |= (1<<1);
}

/* �������� */
static void write_cmd(int cmd)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
    *p = cmd;
}

/* ������ַ */
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

/* ��ȡ���� */
static unsigned char read_data(void)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;
    return *p;
}


/* ��ʼ��NAND Flash */
void nand_init(void)
{
		#define TACLS   0
		#define TWRPH0  3
		#define TWRPH1  0   

		
		/* ����ʱ�� */
        s3c2440nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
        /* ʹ��NAND Flash������, ��ʼ��ECC, ��ֹƬѡ */
        s3c2440nand->NFCONT = (1<<4)|(1<<1)|(1<<0); 
		/* ��λNAND Flash */
		nand_reset();
}


/* ������ */
void nand_read(unsigned char *buf, unsigned long start_addr, int size)
{
    int i, j;
    if ((start_addr & NAND_BLOCK_MASK_LP) || (size & NAND_BLOCK_MASK_LP))
	{
        return ;    /* ��ַ�򳤶Ȳ����� */
    }
    /* ѡ��оƬ */
    nand_select_chip();
    for(i=start_addr; i < (start_addr + size);) 
	{
      /* ����READ0���� */
      write_cmd(0);
      /* Write Address */
      write_addr(i);
      write_cmd(0x30);		
      wait_idle();
      for(j=0; j < NAND_SECTOR_SIZE_LP; j++, i++) //һҳ2k
	  {
         *buf = read_data();
          buf++;
      }
    }
    /* ȡ��Ƭѡ�ź� */
    nand_deselect_chip();
    return ;
}

