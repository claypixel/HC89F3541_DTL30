#ifndef __PWM_H__
#define __PWM_H__
#include "HC89F3541.H"


#define  HOT_PIN  P0_0
//#define  PWM_FREQ 100
#define  AC_CY   P0_2


void pwm_init(void);
void set_pwm(u8 duty);
void PWM_OUT(void);

#endif

