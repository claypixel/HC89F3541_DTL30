#include "sys.h"
#include "uart.h"
#include "timer.h"
#include "flash.h"
#include "key.h"
#include "lcd_display.h"
#include "ht1621b.h"
#include "oled.h"
#include "adc.h"
#include "pwm.h"
#include "delay.h"
#include "wdt.h"
#include "product.h"

var_system_st g_Var_system;

#define SKU_NUM   5

void Init_Config(void)
{
    device_init();
    EA = 1;
    Timer1Init();
    uart_init();
    key_init();
    adc_init();
    init_lcd_ht1621b();
    flash_init();
    pwm_init();
    System_Var_Init();
    wdt_init(2);
    set_pwm(5);
    product_check_process();
    set_pwm(0);
}

void System_Var_Init(void)
{
    g_Var_system.bCalibration_std = False;
    g_Var_system.bFirst_heat_std = False;
    g_Var_system.bHeat_start_std = False;
    g_Var_system.bLed_std = False;
    g_Var_system.bPreheat_std = False;
    g_Var_system.bProtect_std = False;
    g_Var_system.bSTATUS = OFF;
    g_Var_system.bError_E = False;
    g_Var_system.bRes_std = False;
    g_Var_system.bError_F = False;
    g_Var_system.Led_Timeout = 0;
    g_Var_system.Preheat_time = 0;
    g_Var_system.Time_cnt = 0;
    g_Var_system.Protect_time = 0;
    g_Var_system.Heat_D_Value = 0;
    g_Var_system.PWM_Status = OFF;
    g_Var_system.AC_POWER_CNT = HEAT_POWER;
    g_Var_system.AC_STATUS = 0;
    LED_BACK = 1;
    delay_ms(2000);//500ms
    ht1621_all_clear();
//    gap_display(5);
    lcd_display_gap(SKU_NUM);
    delay_ms(2000);//500ms
    LED_BACK = 0;
}

/*********************************************************************************************/
static void Set_Preheat_time(u8 gap)
{
    switch (gap)
    {
        case GAP_WARM:
            g_Var_system.Preheat_time = PREHEAT_time_warm;
            break;
        case GAP_1:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_1;
            break;
        case GAP_2:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_2;
            break;
        case GAP_3:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_3;
            break;
        case GAP_4:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_4;
            break;
        case GAP_5:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_5;
            break;
        case GAP_6:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_6;
            break;
        case GAP_7:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_7;
            break;
        case GAP_8:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_8;
            break;
        case GAP_9:
            g_Var_system.Preheat_time = PREHEAT_time_GAP_9;
            break;
    }
}
static void D_Value_Set(void)
{
    switch (flash_info.gap)
    {
        case GAP_WARM:
            g_Var_system.Heat_D_Value = HEAT_D_value_WARM_temp;
            break;
        case GAP_1:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_1_temp;
            break;
        case GAP_2:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_2_temp;
            break;
        case GAP_3:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_3_temp;
            break;
        case GAP_4:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_4_temp;
            break;
        case GAP_5:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_5_temp;
            break;
        case GAP_6:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_6_temp;
            break;
        case GAP_7:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_7_temp;
            break;
        case GAP_8:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_8_temp;
            break;
        case GAP_9:
            g_Var_system.Heat_D_Value = HEAT_D_value_GAP_9_temp;
            break;
    }
}
static void set_time_sec(void)
{
    switch (flash_info.timer)
    {
        case TIMER_ON:
            g_Var_system.Time_cnt = 0;

            break;
        case TIMER_0_5H:
            g_Var_system.Time_cnt = H_0_5;

            break;
        case TIMER_1H:
            g_Var_system.Time_cnt = H_1_0;

            break;
        case TIMER_2H:
            g_Var_system.Time_cnt = H_2_0;

            break;
       
        case TIMER_4H:
            g_Var_system.Time_cnt = H_4_0;

            break;
       
        case TIMER_8H:
            g_Var_system.Time_cnt = H_8_0;

            break;

    }
}

static void Protect_Temperature(void)
{
    if(flash_info.gap >= GAP_6)
    {     
       g_Var_system.Protect_time++;
        if(g_Var_system.Protect_time > H_1_0)
        {
//         flash_info.gap = GAP_5;
//         Var_info_display.gap = GAP_5;
		 g_Var_system.Protect_time = 0;
        }  
    }
   
}

static void Res_Test(void)
{
  if(Res_IO)
  	{
      g_Var_system.bRes_std = Ture;
    }
}

static void Preheat_Process(void)
{
    if (g_Var_system.bHeat_start_std == Ture)
    {
        if (--g_Var_system.Preheat_time < 1)
        {
            g_Var_system.bPreheat_std = False;
            g_Var_system.bHeat_start_std = False;
            D_Value_Set();
        }
    }

}

void Time_Count_Process(void)
{
    if (get_device_state() == ON)
    {
        Preheat_Process();
		Protect_Temperature();
        if (g_Var_system.Time_cnt > 1)
        {
            g_Var_system.Time_cnt--;
        }
        else if(flash_info.timer != TIMER_ON)
        {
            g_Var_system.Time_cnt = 0;
            g_Var_system.Preheat_time = 0;
            set_device_state(OFF);
            ht1621_send_cmd(LCD_OFF);
        }
    }
}

void Controll_Heat(u16 temp_set, u16 temp_now)
{
    if (temp_now >  temp_set)
    {
        set_pwm(0);
    }
    else if (temp_now < (temp_set - g_Var_system.Heat_D_Value))
    {
        set_pwm(5);
    }
}

void Set_Temp(u16 temp)
{
    if (g_Var_system.bPreheat_std == Ture)
    {

        Controll_Heat(One_Heat_Temp, temp);
    }
    else
    {
        switch (flash_info.gap)
        {
            case GAP_WARM:
                Controll_Heat(GAP_WARM_temp, temp);
                break;
            case GAP_1:
                Controll_Heat(GAP_1_temp, temp);
                break;
            case GAP_2:
                Controll_Heat(GAP_2_temp, temp);
                break;
            case GAP_3:
                Controll_Heat(GAP_3_temp, temp);
                break;
            case GAP_4:
                Controll_Heat(GAP_4_temp, temp);
                break;
            case GAP_5:
                Controll_Heat(GAP_5_temp, temp);
                break;
            case GAP_6:
                Controll_Heat(GAP_6_temp, temp);
                break;
            case GAP_7:
                Controll_Heat(GAP_7_temp, temp);
                break;
            case GAP_8:
                Controll_Heat(GAP_8_temp, temp);
                break;
            case GAP_9:
                Controll_Heat(GAP_9_temp, temp);
                break;
        }
    }
}


/*********************************************************************************************/
static u16 temp_calc(u16 uR510, u16 uRw)
{
    u8 i = 0;
    u8 basi_tmp = 50;
    u8 k = 10;
    float u1 = 0;

    if ((uR510 < 50) || (uR510 > uRw))
    {
        return 101;
    }
    u1 = (((float) uRw / 1000) - ((float) uR510 / 1000)) / (((float) uR510 / 1000) / 510);
    if (u1 < 0)
    {
        return 102;
    }
//    	gm_printf ( "R = %f  \r\n",u1 );
    u1 = u1 / Length;
    if (u1 < 73)
    {
        return 0;
    }
    //	 gm_printf("average R = %f \r\n",u1);
    u1 = u1 / Temperature_Value;
   // gm_printf("cmp = %f \r\n",u1);
    if (u1 * Temperature_Value > Temperature_Value)
    {
        while (1)
        {
            u1 = u1 / (1 + 0.0048);
            i++;
            if (u1 <= 1)
            {
                break;
            }

        }
        basi_tmp = basi_tmp + i;

    }
    else
    {
        while (1)
        {
            u1 = u1 / (1 - 0.0048);
            i++;
            if (u1 >= 1)
            {
                break;
            }
        }

        basi_tmp = basi_tmp - i;
    }

    return (basi_tmp);
}

void temperature_handle(void)    //per second
{
    u16 temp = 0;
    u16 adc_val1 = 0, adc_val3 = 0;
    Res_Test();
    get_voltage(&adc_val1, &adc_val3);
    //KEY_printf ( "adv1 = %d adv3 =%d \r\n",adc_val1,adc_val3 );  //pjw set
    temp = temp_calc(adc_val1, adc_val3);
//    gm_printf ( "temp val:%d \r\n",temp );

    if ((adc_val1 > 50) && (g_Var_system.bRes_std == 0))
    {
        if (get_device_state() == ON)
        {
            if (g_Var_system.bFirst_heat_std == 1)
            {
                g_Var_system.bFirst_heat_std = 0;
                if (temp > 50)
                {
                    g_Var_system.bHeat_start_std = 1;
                    g_Var_system.bPreheat_std = 0;
                    g_Var_system.Heat_D_Value = HEAT_D_value_GAP_9_temp;

                }
                else
                {
                    g_Var_system.bHeat_start_std = 1;
                    g_Var_system.bPreheat_std = 1;
                    g_Var_system.Heat_D_Value = HEAT_D_value_WARM_temp;
                }
            }
            Set_Temp(temp);
        }
        else
        {
            set_pwm(0);
            ht1621_send_cmd(LCD_OFF);
        }
        g_Var_system.bError_F = False;
        lcd_display_blink_set(NO_EORROR);
    }
    else if (g_Var_system.bRes_std == 0)
    {
        g_Var_system.bCalibration_std = False;
        lcd_display_blink_set(F_FLASH);
        set_pwm(0);
        g_Var_system.bError_F = Ture;
    }
    else if (g_Var_system.bRes_std == Ture)
    {
        g_Var_system.bCalibration_std = False;
        lcd_display_blink_set(E_FLASH);
        set_pwm(0);
        g_Var_system.bError_F = Ture;
    }
    display_gap_process(Var_info_display.blink_std);
}
/*********************************************************************************************/

void Led_On(void)
{
    g_Var_system.bLed_std = ON;
    g_Var_system.Led_Timeout = 0;
}

void Led_Off(void)
{
    g_Var_system.bLed_std = OFF;
    g_Var_system.Led_Timeout = 0;
}

void Led_Process(void)
{
    if (g_Var_system.bLed_std == ON)
    {
        LED_BACK = 1;
        if (++g_Var_system.Led_Timeout >= 150)
        {
            LED_BACK = 0;
            g_Var_system.Led_Timeout = 0;
            g_Var_system.bLed_std = OFF;
        }
    }
    else
    {
        LED_BACK = 0;
    }
}
/*********************************************************************************************/

u8 get_device_state(void)
{
    return g_Var_system.bSTATUS;
}

void set_device_state(u8 state)
{
    g_Var_system.bSTATUS = state;
}

static void Set_SYS_Status(void)
{
    if (g_Var_system.bError_F == False)
    {
        if (get_device_state() == ON)
        {
            set_device_state(OFF);
            ht1621_send_cmd(LCD_OFF);
            Led_Off();
        }
        else
        {
            set_device_state(ON);
            Led_On();
            set_time_sec();
            g_Var_system.bFirst_heat_std = 1;
            Set_Preheat_time(flash_info.gap);
            lcd_display_gap(flash_info.gap);
            lcd_display_time(flash_info.timer);
        }
    }
}

static void Gap_Status_Set(void)
{
    if ((get_device_state() == ON) && (g_Var_system.bError_F == False))
    {
        Led_On();
        if (flash_info.gap < GAP_9)
        {
            flash_info.gap++;
        }
        else
        {
            flash_info.gap = GAP_1;
        }
        g_Var_system.bFirst_heat_std = 1;
        lcd_display_gap(flash_info.gap);
        Set_Preheat_time(flash_info.gap);
        flah_save_data();
    }
}

static void Time_Status_Set(void)
{
    if ((get_device_state() == ON) && (g_Var_system.bError_F == False))
    {
        Led_On();
        if (flash_info.timer < TIMER_8H)
        {
            flash_info.timer++;
        }
        else
        {
            flash_info.timer = TIMER_ON;
        }
        lcd_display_time(flash_info.timer);
        set_time_sec();
        flah_save_data();
    }
}
void key_handle(void)
{
    u8 temp = key_scan();
    switch (temp)
    {
        case LED_STAY_ON:
            Set_SYS_Status();
            break;
        case KEY_3_PRES:
            Time_Status_Set();
            break;
        case KEY_2_PRES:
            Gap_Status_Set();
            break;
    }

}


void STATUS_MACHINE(void)
{
  if(Vartime.bSystick_10ms == Ture)
  	{
      key_handle(); 
	  Vartime.bSystick_10ms = False;
    }
  if(Vartime.bSystick_20ms == Ture)
  	{
      Led_Process(); 
	  Vartime.bSystick_20ms = False;
    }
  if(Vartime.bSystick_500ms == Ture)
  	{
      temperature_handle(); 
	  Vartime.bSystick_500ms = False;
    }
  if(Vartime.bSystick_100ms == Ture)
  	{
      display_process(); 
	  Vartime.bSystick_100ms = False;
    }
   if(Vartime.bSystick_1s == Ture)
  	{
      Time_Count_Process(); 
	  Vartime.bSystick_1s = False;
    }
}

