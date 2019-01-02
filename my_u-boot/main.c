extern void nand_read(unsigned long sour, unsigned char * dest, int copy_size);
extern void puts(char * str);
void putc(unsigned char date);
void puthex(unsigned int val);

#include"tag.h"





int main(void)
{
    void (*thekernel)(int zero,int arch,unsigned int params);


	puts("bootloader start.....\n\r");


    //copy kernel
    puts("1. copy kernal to sdram\n\r");
    nand_read(0x60000+64,(unsigned char *)0x30008000,0x200000);    

	
	//set params
    set_start_tag();
	set_memory_tag();
	set_cmdline_tag("noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0");
	set_end_tag();
	puts("2. set kernel parameters\n\r");

	//jump to kernel
	puts("3. jump to kernel\n\r");
    thekernel=(void (*)(int,int ,unsigned int))0x30008000;
    thekernel(0,362,0x30000100); 
	

    //error
    puts("something wrong\n\r");
    return 0;
}





























