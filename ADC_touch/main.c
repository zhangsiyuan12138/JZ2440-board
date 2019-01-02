#include"uart.h"
#include"my_stdio.h"
#include"screen_touch.h"


void raise(int sig_nr){;}


int main(void)
{
	 uart0_init();
　　 while(1)
     screen_touch();
     return 0;
}


