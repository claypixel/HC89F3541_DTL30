#include "uart.h"

//初始化串口9600
void uart_init(void)
{
#if _DEBUG_PRINTF_
    P1M6 = 0xC1;		//P16设置为推挽输出
    P1M7 = 0x61;		//P17设置为上拉输入
    TXD_MAP = 0x16;		//TXD映射P16
    RXD_MAP = 0x17;		//RXD映射P17

    //波特率计算
    //波特率 = 1/16 * (T4时钟源频率 / 定时器4预分频比) / (65536 - 0xFF98)
    //       = 1/16 * ((16000000 / 1) / 104)
    //		 = 9615.38(误差0.16%)

    //波特率9600
    //反推初值 = (65536 - ((T4时钟源频率 / 定时器4预分频比) * (1 / 16)) / 波特率)
    //		   = (65536 - (16000000 * (1 / 16) / 9600))
    //		   = (65536 - 104.167)
    //         = FF98
    // TH4 = 0xFF;
    // TL4 = 0x98;			//波特率9600
    TH4 = 0xFF;//9600  4M 波特率9600
    TL4 = 0x98;
    T4CON = 0x06;		//T4工作模式：UART1波特率发生器
    SCON2 = 0x02;		//8位UART，波特率可变 方式一
    SCON = 0x10;		//允许串行接收
    ES1 = 1;			//使能串口中断
#endif
}


//串口发送一个字符
void hal_uart_putchar(unsigned char Char)
{
    ES1 = 0;				//失能UART1中断
    SBUF = Char;
    while (!TI);
    TI = 0;
    ES1 = 1;				//UART1接收使能

}

//void UartSendByte(unsigned Data)
//{
//    hal_uart_putchar(Data);
//}

//void UartSendString(u8 *pData)
//{
//    u16 Ccount = 0;
//    while (1)
//    {
//        if ((*pData == '\0') || (Ccount++ > 1000) || (*pData == 0) || (*pData == 0xff))
//            break;
//        UartSendByte(*pData++);
//    }
//}





//重写stdio 中的putchar函数  实现printf
char putchar(char c)
{
    hal_uart_putchar(c);
    return c;
}


void UART1_Rpt(void) interrupt UART1_VECTOR
{
//   
//    if (SCON & 0x01)						//判断接收中断标志位
//    {
//        Data = SBUF;				//转存8位串口接收数据
//        SCON &= ~ 0x01;              	//清除接收中断标志位
//        /* receive Data */


//    }
}



