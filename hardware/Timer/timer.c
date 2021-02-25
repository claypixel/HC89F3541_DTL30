#include "timer.h"
#include "pwm.h"
#include "sys.h"

u16 cnt_systick = 0;
volatile Timer_systick_bit Vartime = {0, 0, 0, 0, 0, 0};


void device_init(void)
{
    /************************************?????****************************************/
    CLKSWR = 0x51;                       //16MHz
    CLKDIV = 0x01;						//Fosc 1????Fcpu,Fcpu=16MH
}


void Timer1Init(void)
{
    //    TCON1 &= 0xEF;//12T??
    //    TMOD &= 0xCF;//??0:16?????
    //    TH1 = 0xCB;//???8?
    //    TL1 = 0xEB;//???8?
    //    TF1 = 0;//??????
    //    ET1 = 1;//????
    //    TR1 = 1;//?????
    TCON1 = 0x00;
    TMOD = 0x00;
    TH0 = 0xCB;
    TL0 = 0xEB;
    IE |= 0x02;
    TCON |= 0x10;
}

//T1??????
void TIMER0_Rpt(void) interrupt TIMER0_VECTOR
{
    cnt_systick++;
    Vartime.bSystick_10ms = Ture;

    if (cnt_systick % 10 == 0)
    {
        Vartime.bSystick_100ms = Ture;
    }
    if (cnt_systick % 5 == 0)
    {
        Vartime.bSystick_50ms = Ture;
    }
    if (cnt_systick % 50 == 0)
    {
        Vartime.bSystick_500ms = Ture;
    }
    if (cnt_systick % 100 == 0)
    {
        Vartime.bSystick_1s = Ture;
    }
    if (cnt_systick % 2 == 0)
    {
        Vartime.bSystick_20ms = Ture;
    }
    //TaskRemarks();

    TF1 = 0;

}




