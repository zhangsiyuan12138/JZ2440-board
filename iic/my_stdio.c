#include"uart.h"
#include"my_stdio.h"


typedef char* va_list;

#define int_sizeof(type)             ((sizeof(int)+sizeof(type)-1)&~(sizeof(int)-1))

#define va_start(para_p,first_para)  (para_p=(va_list)&first_para+int_sizeof(first_para)) 
#define va_arg(para_p,type)          (*(type *)((para_p+=int_sizeof(type))-int_sizeof(type)))  
#define va_end(para_p)               (para_p=(va_list)0)  


void my_printf(const char *format, ...)
{
	va_list temp ;
	char *string = format;     
	va_start(temp, format);    

	while (*string)
	{
		if (*string == '%')
		{
			switch (*++string)
			{
			   case 'c': 	{  my_putchar(va_arg(temp,char)); break; }
			   case 's':
			   {
				   char* p = va_arg(temp,char*);
				   while (*p != 0) my_putchar(*p++);
				   break;
			   }

			   case 'p':
			   {			   
				   unsigned int addr = (unsigned int)&va_arg(temp, unsigned int), sheft = 0xf0000000;
				   unsigned char temp = 0,count=0;
				   my_putchar('0');
				   my_putchar('x');
				   while (count<32)
				   {
					   temp = (unsigned char)(((sheft >> count)&addr) >> (32 - count - 4)) ; 
					   if (temp < 10) my_putchar(temp + 48);
					   if (temp >= 10) my_putchar(temp+65-10);
					   count += 4;
				   }
				   break;
			   }

			   case 'd':
			   {
				   int value = va_arg(temp, int),num=100000000;
				   if (value == 0) my_putchar(48);
				   if (value & 0x80000000)    //负数
				   {
					   my_putchar('-');
					   num = -10000000;
				   }
				   else                       //正数.;			
				   while (!(value / num))
						   { 
							   num /= 10; 
							   if (num == 0)
							   {
								   my_putchar(0);
								   return;
							   }
						    }
						  while (num != 0)
							   {
								   my_putchar(value / num+48);
								   value %= num;
								   num /= 10;
							   }
						  break;
			   }

			   case 'f':
			   {
				   char *str = "Sorry: function is not available";
				   while (*str != 0) my_putchar(*str++);
			   }

			default: break;
			}
		}
		string++;
	}
	va_end(temp);
}                    


























