#include "debug.h"

wifi_command_Q_t g_wifi_cmd_quene;
Command_Info_t   g_SystemVar;

void wifi_cmd_in_quene(unsigned char cmd, unsigned char param)  //wifi命令进入循环队列
{
    if (g_wifi_cmd_quene.write_index < WIFI_TO_MCU_COMMAND_BUFFER_SIZE) //写入队列index 小于队列大小才可以写入，否则队列满不能写入
    {
        g_wifi_cmd_quene.cmd_buf[g_wifi_cmd_quene.write_index].cmd = cmd;  //进队列时传入的参数 cmd param
        g_wifi_cmd_quene.cmd_buf[g_wifi_cmd_quene.write_index].param = param;
        g_wifi_cmd_quene.write_index++;                               //队列index ++ 直到循环队列满时才不能写入参数
    }
}

unsigned char wifi_cmd_out_quene(Command_Info_t *wifi_cmd)
{
    if (g_wifi_cmd_quene.write_index == g_wifi_cmd_quene.read_index) //判断wifi循环队列里面是否所有消息全部取出
    {
        g_wifi_cmd_quene.write_index = 0;
        g_wifi_cmd_quene.read_index = 0;                              //wifi消息队列里面没有消息或者全部消息都已经取出
        return 0;                                                     //没有消息返回0 标识WiFi没有消息要发送
    }

    wifi_cmd->cmd = g_wifi_cmd_quene.cmd_buf[g_wifi_cmd_quene.read_index].cmd;
    wifi_cmd->param = g_wifi_cmd_quene.cmd_buf[g_wifi_cmd_quene.read_index].param;//从WiFi循环队列取出消息
    g_wifi_cmd_quene.read_index++;                                   //取一次循环队列 index++ 直到读指针和写指针相等表示队列里面没有消息
}

void user_send_command(unsigned char cmd, unsigned char param)
{
    cmd = 1;
    param = 2;
}
void user_respond_command(unsigned char cmd)
{
    cmd = 0;
}
void wifi_routine_handler(void)
{
    if (g_wifi_cmd_quene.command_resend_time > 0) //判断超时时间是否被置0 没有表示没有收到串口回传数据
    {
        g_wifi_cmd_quene.command_resend_time--;
        if (g_wifi_cmd_quene.command_resend_time == (WIFI_COMMAND_RESEND_TIME -
                2)) //没有收到设备返回值再进行一次函数发送保证通讯成功
        {
            user_send_command(g_SystemVar.cmd, g_SystemVar.param);   //串口重新发送数据
        }
    }
    else
    {
        if (wifi_cmd_out_quene(&g_SystemVar))
        {
            g_wifi_cmd_quene.command_resend_time = WIFI_COMMAND_RESEND_TIME; //第一次发送打开超时
            user_send_command(g_SystemVar.cmd, g_SystemVar.param);           //串口发送函数
        }
    }
}


