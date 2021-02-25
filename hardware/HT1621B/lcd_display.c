#include "lcd_display.h"
#include "ht1621b.h"
#include "sys.h"


var_info_t Var_info_display = {0, 0, 0, 0};


void ht1621_all_display(void)
{
    u8 i = 0;

    for (i = 0; i < 32; ++i)   //max seg 31
    {
        ht1621_write_byte(i, 0x0F);   //置1为点亮 com全开
    }

}

void ht1621_all_clear(void)
{
    u8 i = 0;

    for (i = 0; i < 32; ++i)   //max seg 31
    {
        ht1621_write_byte(i, 0x00);   //置1为点亮 com全关
    }

}


static void gap_display(u8 gap_num)
{
    switch (gap_num)
    {
        case GAP_1:
            ht1621_write_byte(Gap_29_Pin, COM2 | COM3);
            ht1621_write_byte(Gap_30_Pin, COM_OFF);
            break;
        case GAP_2:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM2 | COM4);
            ht1621_write_byte(Gap_30_Pin, COM3 | COM4);
            break;
        case GAP_3:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM2 | COM3 | COM4);
            ht1621_write_byte(Gap_30_Pin,  COM3);
            break;
        case GAP_4:
            ht1621_write_byte(Gap_29_Pin,  COM2 | COM3);
            ht1621_write_byte(Gap_30_Pin,  COM2 | COM3);
            break;
        case GAP_5:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM3 | COM4);
            ht1621_write_byte(Gap_30_Pin,  COM2 | COM3);
            break;
        case GAP_6:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM3 | COM4);
            ht1621_write_byte(Gap_30_Pin, COM2 | COM3 | COM4);
            break;
        case GAP_7:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM2 | COM3);
			ht1621_write_byte(Gap_30_Pin, COM_OFF);
            break;
        case GAP_8:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM2 | COM3 | COM4);
            ht1621_write_byte(Gap_30_Pin, COM2 | COM3 | COM4);
            break;
        case GAP_9:
            ht1621_write_byte(Gap_29_Pin, COM1 | COM2 | COM3 | COM4);
            ht1621_write_byte(Gap_30_Pin,  COM2 | COM3);
            break;
    }

}
void display_gap_process(EORROR_Index index)
{
    static u8 BLINK = 0;
    switch (index)
    {
        case  NO_EORROR:
            gap_display(Var_info_display.gap);
            if(get_device_state() == ON)
            lcd_display_time(flash_info.timer);
            break;
        case  F_FLASH:
            ht1621_send_cmd(LCD_ON);
            if (BLINK == 0)
            {
                Led_On();
                ht1621_write_byte(Gap_29_Pin, COM1);
                ht1621_write_byte(Gap_30_Pin,  COM2 | COM3 | COM4);
                BLINK = 1;
            }
            else
            {
                Led_Off();
                ht1621_write_byte(Gap_29_Pin, COM_OFF);
                ht1621_write_byte(Gap_30_Pin,  COM_OFF);
				ht1621_write_byte(Time_27_Pin, COM_OFF);
                ht1621_write_byte(Time_28_Pin, COM_OFF);
                ht1621_write_byte(Time_31_Pin, COM_OFF); //8H
                BLINK = 0;
            }
            break;
        case  E_FLASH:
            ht1621_send_cmd(LCD_ON);
            if (BLINK == 0)
            {
                Led_On();
                ht1621_write_byte(Gap_29_Pin, COM1 | COM4);
                ht1621_write_byte(Gap_30_Pin, COM2 | COM3 | COM4);
                BLINK = 1;
            }
            else
            {
                Led_Off();
                ht1621_write_byte(Gap_29_Pin, COM_OFF);
                ht1621_write_byte(Gap_30_Pin, COM_OFF);
                ht1621_write_byte(Time_27_Pin, COM_OFF);
                ht1621_write_byte(Time_28_Pin, COM_OFF);
                ht1621_write_byte(Time_31_Pin, COM_OFF); //8H
                BLINK = 0;
            }
            break;
    }

}
void display_process(void)
{
    if (Var_info_display.reflish_std == SET)
    {

        Var_info_display.reflish_std = 0;
        switch (Var_info_display.time)
        {
            case TIMER_ON:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4);
                ht1621_write_byte(Time_28_Pin, COM2 | COM4 | COM3); //ON
                ht1621_write_byte(Time_31_Pin, COM2 | COM4);
                break;
            case TIMER_0_5H:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4 | COM1); //0.5H
                ht1621_write_byte(Time_28_Pin, COM2 | COM4);
                ht1621_write_byte(Time_31_Pin, COM2 | COM4);
                break;
            case TIMER_1H:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4 | COM3); //1H
                ht1621_write_byte(Time_28_Pin, COM2 | COM4);
                ht1621_write_byte(Time_31_Pin, COM2 | COM4);
                break;
            case TIMER_2H:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4);
                ht1621_write_byte(Time_28_Pin, COM2 | COM4);
                ht1621_write_byte(Time_31_Pin, COM2 | COM4 | COM1); //2H
                break;
            case TIMER_4H:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4);
                ht1621_write_byte(Time_28_Pin, COM2 | COM4 | COM1); //4h
                ht1621_write_byte(Time_31_Pin, COM2 | COM4);
                break;
            case TIMER_8H:
                ht1621_write_byte(Time_27_Pin, COM2 | COM4);
                ht1621_write_byte(Time_28_Pin, COM2 | COM4);
                ht1621_write_byte(Time_31_Pin, COM2 | COM4 | COM3); //8H
                break;
        }


    }
}
void init_lcd_ht1621b(void)
{
    ht1621_init_pin();

    ht1621_send_cmd(BIAS);
    ht1621_send_cmd(RC256);    //RC256  XTAL_32K
    ht1621_send_cmd(WDTDIS);
    ht1621_send_cmd(TMDIS);
    ht1621_send_cmd(SYSEN);
    ht1621_send_cmd(LCD_ON);
    ht1621_all_display();
}

void lcd_display_time_set(u8 time_gap)
{
    Var_info_display.reflish_std = SET;
    switch (time_gap)
    {
        case TIMER_ON:
            Var_info_display.time = TIMER_ON;
            break;
        case TIMER_0_5H:
            Var_info_display.time = TIMER_0_5H;
            break;
        case TIMER_1H:
            Var_info_display.time = TIMER_1H;
            break;
        case TIMER_2H:
            Var_info_display.time = TIMER_2H;
            break;
        case TIMER_4H:
            Var_info_display.time = TIMER_4H;
            break;
        case TIMER_8H:
            Var_info_display.time = TIMER_8H;
            break;

    }


}

void lcd_display_blink_set(EORROR_Index index)
{
    switch (index)
    {
        case NO_EORROR:
            Var_info_display.blink_std = NO_EORROR;
            break;
        case F_FLASH:
            Var_info_display.blink_std = F_FLASH;
            break;
        case E_FLASH:
            Var_info_display.blink_std = E_FLASH;
            break;
    }
}


void lcd_display_time(u8 time_type)
{
    ht1621_send_cmd(LCD_ON);
    lcd_display_time_set(time_type);
}

void lcd_display_gap(u8 gap)
{
    ht1621_send_cmd(LCD_ON);
    Var_info_display.gap = gap;
    gap_display(gap);
}



