#include"s3c24xx.h"
#include"stdio.h"

// ADCCON寄存器
#define PRESCALE_DIS        (0 << 14)
#define PRESCALE_EN         (1 << 14)
#define PRSCVL(x)           ((x) << 6)
#define ADC_INPUT(x)        ((x) << 3)
#define ADC_START           (1 << 0)
#define ADC_ENDCVT          (1 << 15)

// ADCTSC寄存器
#define UD_SEN          (1 << 8)
#define DOWN_INT        (UD_SEN*0)
#define UP_INT          (UD_SEN*1)
#define YM_SEN          (1 << 7)
#define YM_HIZ          (YM_SEN*0)
#define YM_GND          (YM_SEN*1)
#define YP_SEN          (1 << 6)
#define YP_EXTVLT       (YP_SEN*0)
#define YP_AIN          (YP_SEN*1)
#define XM_SEN          (1 << 5)
#define XM_HIZ          (XM_SEN*0)
#define XM_GND          (XM_SEN*1)
#define XP_SEN          (1 << 4)
#define XP_EXTVLT       (XP_SEN*0)
#define XP_AIN          (XP_SEN*1)
#define XP_PULL_UP      (1 << 3)
#define XP_PULL_UP_EN   (XP_PULL_UP*0)
#define XP_PULL_UP_DIS  (XP_PULL_UP*1)
#define AUTO_PST        (1 << 2)
#define CONVERT_MAN     (AUTO_PST*0)
#define CONVERT_AUTO    (AUTO_PST*1)
#define XP_PST(x)       (x << 0)

#define NOP_MODE        0
#define X_AXIS_MODE     1
#define Y_AXIS_MODE     2
#define WAIT_INT_MODE   3



#define wait_down_int() { ADCTSC = DOWN_INT | XP_PULL_UP_EN | \
                          XP_AIN | XM_HIZ | YP_AIN | YM_GND | \
                          XP_PST(WAIT_INT_MODE); }

#define wait_up_int()   { ADCTSC = UP_INT | XP_PULL_UP_EN | XP_AIN | XM_HIZ | \
                          YP_AIN | YM_GND | XP_PST(WAIT_INT_MODE); }

#define mode_auto_xy()  { ADCTSC = CONVERT_AUTO | XP_PULL_UP_DIS | XP_PST(NOP_MODE); }


extern void (*isr_handle_array[50])(void);

static void screen_touch_interrupt(void)
{
	 
    printf("xdata = %4d, ydata = %4d\r\n", (int)(ADCDAT0 & 0x3ff), (int)(ADCDAT1 & 0x3ff));
    wait_up_int();        
    SUBSRCPND |= BIT_SUB_ADC;
    SRCPND    |= BIT_ADC;
    INTPND    |= BIT_ADC;
}


void screen_touch(void)
{
	isr_handle_isr[ISR_ADC_OFT]=screen_touch_interrupt;
	INTMSK &= ~BIT_ADC;        
    INTSUBMSK &= ~(BIT_SUB_TC); 
    INTSUBMSK &= ~(BIT_SUB_ADC); 
    ADCCON = PRESCALE_EN | PRSCVL(49);
    ADCDLY = 50000;
    wait_down_int();    
    INTSUBMSK |= BIT_SUB_TC;
    INTSUBMSK |= BIT_SUB_ADC;
    INTMSK |= BIT_ADC;
	
	
	
}










































































































