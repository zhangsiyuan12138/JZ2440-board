#include"uart.h"
#include"my_stdio.h"
#include"stdio.h"


void raise(int sig_nr){;}


int main(void)
{
	uart0_init();
	
    printf("%s","   wds_standard   ");	
	my_printf("%s","  zsy_standard   ");
	
	while(1)
    my_putchar(my_getchar()+1);	
    
	return 0;
}


