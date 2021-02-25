#ifndef __FLASH_H__
#define __FLASH_H__
#include "HC89F3541.H"


#define FLASH_CHECK_ADDRESS   0X3C00                 //用flash末尾1K(总16K)地址作为存储基地址 1024*14 = 0X3800   
#define FLASH_DATA_ADDRESS	FLASH_CHECK_ADDRESS + 4

typedef struct _flash_info_t
{
	u8 gap;
	u8 timer;
	u8 correct_value;
	u8 correct_sign;
	u8 correct_std;
} flash_info_t;

extern flash_info_t flash_info;

void flash_init ( void );
void flah_save_data ( void );


#endif

