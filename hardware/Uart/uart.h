#ifndef __UART_H__
#define __UART_H__
#include "HC89F3541.H"

#include "stdio.h"//printf

#define _DEBUG_PRINTF_    1
#define KEY_DEBUG_PRINT   1
#define ADC_DEBUG_PRINT   1

#if _DEBUG_PRINTF_
	#define	gm_printf printf
#else
	#define	gm_printf (...)
#endif
//
//#if ADC_DEBUG_PRINT
//	#define	ADC_printf printf
//#else
//	#define	ADC_printf (...)
//#endif
//
//
//#if KEY_DEBUG_PRINT
//	#define	KEY_printf printf
//#else
//	#define	KEY_printf (...)
//#endif
typedef enum
{
   DEC_TYPE = 0,
   HEX_TYPE,
}data_type_t;
   
void uart_init(void);

void hal_uart_putchar(char Char);


#endif


