#ifndef _SYS_H_
#define _SYS_H_

#include "HC89F3541.H"


#define Length           8
#define Temperature_Value         91.0624
#define HEAT_POWER         150
#define HEAT_PULSE_TIME    30
typedef enum STATUS
{
  False = 0,
  Ture  = 1
};


typedef enum GAP_TEMP
{
    GAP_WARM_temp	= 30,
    GAP_1_temp 	= 43,
    GAP_2_temp	= 47,
    GAP_3_temp	= 50,
    GAP_4_temp	= 54,
    GAP_5_temp	= 60,
    GAP_6_temp	= 65,
    GAP_7_temp	= 70,
    GAP_8_temp	= 72,
    GAP_9_temp	= 75,
    One_Heat_Temp = 77,
};

typedef enum _TIME_COUNT
{
    H_0_5  = (60 * 30),
    H_1_0  = (60 * 60),
    H_1_5  = (60 * 30 * 3),
    H_2_0  = (60 * 60 * 2),
    H_3_0  = (60 * 60 * 3),
    H_4_0  = (60 * 60 * 4),
    H_5_0  = (60 * 60 * 5),
    H_6_0  = (60 * 60 * 6),
    H_7_0  = (60 * 60 * 7),
    H_8_0  = (60 * 60 * 8),
    H_9_0  = (60 * 60 * 9)
};

typedef enum _TIMER_TYPE
{
      TIMER_ON    = 0,
	  TIMER_0_5H 	= 0X01,
	  TIMER_1H	= 0X02,
	  TIMER_2H	= 0X03,
	  TIMER_4H	= 0X04,
	  TIMER_8H	= 0X05,
//    TIMER_ON    = 0,
//    TIMER_0_5H 	= 0X01,
//    TIMER_1H	= 0X02,
//    TIMER_1_5H	= 0X03,
//    TIMER_2H	= 0X04,
//    TIMER_3H	= 0X05,
//    TIMER_4H	= 0X06,
//    TIMER_5H	= 0X07,
//    TIMER_6H	= 0X08,
//    TIMER_7H	= 0X09,
//    TIMER_8H	= 0X0A,
//    TIMER_9H	= 0X0B,
} TIMER_TYPE;

typedef enum GAP_TYPE
{
    GAP_WARM	= 0X00,
    GAP_1 	= 0X01,
    GAP_2	= 0X02,
    GAP_3	= 0X03,
    GAP_4	= 0X04,
    GAP_5	= 0X05,
    GAP_6	= 0X06,
    GAP_7	= 0X07,
    GAP_8	= 0X08,
    GAP_9	= 0X09,

};


typedef enum corrected_value
{
    HEAT_D_value_WARM_temp	= 1,
    HEAT_D_value_GAP_1_temp	= 1,
    HEAT_D_value_GAP_2_temp	= 3,
    HEAT_D_value_GAP_3_temp	= 3,
    HEAT_D_value_GAP_4_temp	= 5,
    HEAT_D_value_GAP_5_temp	= 5,
    HEAT_D_value_GAP_6_temp	= 8,
    HEAT_D_value_GAP_7_temp	= 8,
    HEAT_D_value_GAP_8_temp	= 8,
    HEAT_D_value_GAP_9_temp	= 8,
};

typedef enum PREHEAT_time
{
    PREHEAT_time_warm	= 30 * 1,
    PREHEAT_time_GAP_1	= 30 * 2,
    PREHEAT_time_GAP_2	= 30 * 2,
    PREHEAT_time_GAP_3	= 30 * 2,
    PREHEAT_time_GAP_4	= 30 * 3,
    PREHEAT_time_GAP_5	= 30 * 4,
    PREHEAT_time_GAP_6	= 30 * 5,
    PREHEAT_time_GAP_7	= 60 * 3,
    PREHEAT_time_GAP_8	= 60 * 4,
    PREHEAT_time_GAP_9	= 60 * 5,
};

typedef enum DEVICE_STATE
{
    OFF	= 0X00,
    ON = 0X01
};

typedef struct _Var_system_
{
    u8 bCalibration_std: 1;
    u8 bFirst_heat_std: 1;
    u8 bHeat_start_std: 1;
    u8 bPreheat_std: 1;
    u8 bLed_std: 1;
    u8 bSTATUS: 1;
    u8 bProtect_std: 1;
    u8 bRes_std: 1;

    u8 Led_Timeout;
    u8 bError_F: 1; //Without_blanket
    u8 bError_E: 1;
    u8 bCali_H: 1;
	u8 PWM_Status:1;

    u16 Preheat_time;
    u16 Protect_time;
    u16 Time_cnt;
	u8  Heat_D_Value;
	u8  AC_STATUS;
	u16 AC_POWER_CNT;
} var_system_st;

extern var_system_st g_Var_system;

u8 get_device_state(void);
void set_device_state(u8 state);
void Led_On(void);
void Led_Off(void);
void System_Var_Init(void);
void Led_Process(void);
void key_handle(void);
void temperature_handle(void);
void Time_Count_Process(void);
void Init_Config(void);
void STATUS_MACHINE(void);


#endif

