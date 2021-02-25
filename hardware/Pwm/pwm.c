#include "pwm.h"
#include "sys.h"
#include "delay.h"



void pwm_init(void)
{
    P0M0 = 0xC1;                        //P00设置为推挽输出
    P0M2 = 0x61;                        //P02设置为上拉输入
}

static void AC_TEST(void)
{
    if ((AC_CY == 0) && (g_Var_system.AC_STATUS == 0))
    {
        g_Var_system.AC_STATUS = 1;
        
    }
    else if ((g_Var_system.AC_STATUS == 1) && (AC_CY == 1))
    {
        g_Var_system.AC_STATUS = 2;
        
    }
}


void PWM_OUT(void)
{
    AC_TEST();
    if (g_Var_system.PWM_Status == ON)
    {
        if (g_Var_system.AC_STATUS == 2)
        {
            if (--g_Var_system.AC_POWER_CNT < 1)
            {
                g_Var_system.AC_POWER_CNT = HEAT_POWER;
                HOT_PIN = 1;
                delay_ms(HEAT_PULSE_TIME);   //7.5ms
                HOT_PIN = 0;
                g_Var_system.AC_STATUS = 0;
            }
        }
    }
    else
        HOT_PIN = 0;
}



//void Hot_PWM_Process(void)
//{
//  if(g_Var_system.PWM_Status == ON)
//  	{
//       Set_Heat_Power (5);
//    }
//  else
//  	{
//      HOT_PIN = 0;
//    }
//}

void set_pwm(u8 duty)
{
    if (duty == 0)
    {
        g_Var_system.PWM_Status = OFF;
    }
    else
        g_Var_system.PWM_Status = ON;
}
//
//void pwm_init(void)
//{
//	P0M0 = 0xC1;                        //P00设置为推挽输出
//  P0M2 = 0x61;						//P02设置为上拉输入
//	PWM3_MAP = 0x00;					//PWM3映射P00口
//
//
//	//16MHZ
//	//周期计算 	= 0xFF / (Fosc / PWM分频系数)	 PWM3C
//	//			= 0xFF /(16000000 / 128)
//	// 			= 1/255 /125000
//	// 			= 490HZ
//	pwm_period = 0xFF;			//31250 = 4000000/128
//	PWM3P = pwm_period;					//PWM周期
//	//set_pwm(10);
//	PWM3C = 0x97; 						//使能PWM3，关闭中断，允许输出，时钟128分频 111
//}

