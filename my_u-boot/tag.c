
/*****************************************string_lib***********************************************/
int strlen(char *str)
{
      int i=0;
     while(str[i] != 0) i++;
	 return i;
}

void strcopy(char *dest,char *sour)
{
   while((*dest++ = *sour++)!= 0);
}


/*****************************************tag_init************************************************/
#define tag_next(type)  (struct tag *) ((unsigned long *)(type) + (type)->hdr.size) 
#define tag_size(size)  ((sizeof(struct tag_header)+sizeof(struct size))>>2)

struct tag_header
{
	unsigned long   size;
	unsigned long   tag_type;
};



struct tag_core
{
   unsigned long   flags;
   unsigned long   pagesize;
   unsigned long   rootdevf;
};


struct tag_mem32
{
    unsigned long  size;
   	unsigned long  start;
};

struct tag_cmdline
{
  char cmdline[1]; 
};


struct tag 
{
    struct tag_header hdr;
	union
		{
           struct tag_core       core;
           struct tag_mem32      mem32;
           struct tag_cmdline    cmdline;
	    }u;
};

static  struct tag *params=(struct tag *)0x30000100;  // 传递参数起始地址

void set_start_tag(void)
{
   params->hdr.size=tag_size(tag_core);
   params->hdr.tag_type=0x54410001;
   
   params->u.core.flags= 0;
   params->u.core.pagesize= 0;
   params->u.core.rootdevf= 0;

   params=tag_next(params);
}


void set_memory_tag(void)
{
   params->hdr.size= tag_size(tag_mem32);
   params->hdr.tag_type = 0x54410002;

   params->u.mem32.size =64*1024*1024;   //内存大小
   params->u.mem32.start =0x30000000;   //内存起始地址

   params=tag_next(params);

}


void set_cmdline_tag(char *cmdline)
{
   int len=strlen(cmdline)+1;
    params->hdr.size = (sizeof(struct tag_header)+len+3)>>2;
	params->hdr.tag_type = 0x54410009;
    strcopy(params->u.cmdline.cmdline ,cmdline);
	
    params=tag_next(params);
}


void set_end_tag(void)
{
   params->hdr.size = 0;
   params->hdr.tag_type = 0;
}


