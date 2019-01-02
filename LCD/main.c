#include"uart.h"
#include"my_stdio.h"
#include"stdio.h"
#include"lcd_lib.h"

void raise(int sig_nr){;}


int main(void)
{
	uart0_init();	
    tft_lcd_16bpp_640_480();
	return 0;
}


