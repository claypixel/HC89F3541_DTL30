/**
*	************************************************************************************
*	@Examle Version		K9029
*	@Demo	Version		V1.00.00
*	@Date				2021.1.18
*	************************************************************************************
*
**/

#define	ALLOCATE_EXTERN
#include "HC89F3541.H"
#include "uart.h"
#include "timer.h"
#include "flash.h"
#include "key.h"
#include "lcd_display.h"
#include "sys.h"
#include "adc.h"
#include "pwm.h"
#include "wdt.h"
#include "product.h"


void main(void)
{
    Init_Config();
    System_Var_Init();
    
    
    while (1)
    {
     PWM_OUT();   
	 STATUS_MACHINE();
     clear_wdt();
    }
}



