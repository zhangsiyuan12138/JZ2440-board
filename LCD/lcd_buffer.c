#include"lcd_buffer.h"

extern unsigned long lcd_base_addr;
extern int bpp;
extern int x_size;
extern int y_size;


void draw_pixel(unsigned long x,unsigned long y,unsigned long color)
{
	unsigned long red,blue,green,*final_addr;
	
	final_addr=(unsigned long *)lcd_base_addr+(y*x_size+x);
	red=(color>>19)&0x1f;
	green=(color>>10)&0x3f;
	blue=(color>>3)&0x1f;
	color=(red<<11)|(green<<5)|(blue);
    *final_addr=color;	
}


void draw_circul(void)
{
	 unsigned long x,y;
     unsigned long color;
     unsigned long red,green,blue,alpha;

    for (y = 0; y < y_size; y++)
        for (x = 0; x < x_size; x++)
		{
            color = ((x-x_size/2)*(x-x_size/2) + (y-y_size/2)*(y-y_size/2))/64;
            red   = (color/8) % 256;
            green = (color/4) % 256;
            blue  = (color/2) % 256;
            alpha = (color*2) % 256;

            color |= (alpha << 24);
            color |= (red   << 16);
            color |= (green << 8 );
            color |= (blue       );

            draw_pixel(x,y,color);
        }
}




