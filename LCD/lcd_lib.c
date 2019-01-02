#include"lcd_lib.h"
#include"lcd_drv.h"
#include"lcd_buffer.h"

void tft_lcd_16bpp_640_480(void)
{
	 lcd_port_init();
	 tft_lcd_init();
	 lcd_poweron();
	 lcd_envidon();
	 draw_circul();
}


