#include"uart.h"

int main(void)
{
	uart0_init();
	while(1)
    putc(getc()+1);	
	return 0;
}


