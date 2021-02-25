#ifndef _DEBUG_H
#define _DEBUG_H

#include "HC89F3541.H"



#define WIFI_TO_MCU_COMMAND_BUFFER_SIZE  10 
#define WIFI_COMMAND_RESEND_TIME         24

typedef struct _Command_Info_t
{
 unsigned char cmd;
 unsigned char param;
}Command_Info_t;


typedef struct
{
 Command_Info_t cmd_buf[WIFI_TO_MCU_COMMAND_BUFFER_SIZE];
 unsigned char read_index;
 unsigned char write_index;
 unsigned char command_resend_time;
}wifi_command_Q_t;  



#endif
