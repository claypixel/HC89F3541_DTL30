#ifndef __TIMER_H__
#define __TIMER_H__
#include "HC89F3541.H"




typedef struct _Var_timer_
{
  u8  bSystick_10ms:1;
  u8  bSystick_50ms:1;
  u8  bSystick_100ms:1;
  u8  bSystick_200ms:1;
  u8  bSystick_500ms:1;
  u8  bSystick_1s:1;
  u8  bSystick_1_5s:1;
  u8  bSystick_20ms:1;
}Timer_systick_bit;

extern Timer_systick_bit Vartime;

void Timer1Init(void);
void device_init ( void );

#endif

