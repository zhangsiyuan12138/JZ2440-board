#ifndef _IIC_H_
#define _IIC_H_


void iic_init(void);
void iic_write(unsigned int slv_addr,unsigned char *buf,int len);
void iic_read(unsigned int slv_addr,unsigned char *buf,int len);
void iic_interrupt_svr(void);



#endif

