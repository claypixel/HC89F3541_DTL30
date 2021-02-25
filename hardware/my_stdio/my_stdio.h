#ifndef _MY_STDIO_H
#define _MY_STDIO_H
#include "HC89F3541.H" //数据类型重新选择

#define NULL   ((void *)0)

void *my_memset(void *src,unsigned char ch,unsigned char count);
void *my_memcpy(void * dest,const void *src,unsigned short count);
char *my_strcpy(char * dest,const char *src);
int my_strcmp(char * s1,char *s2);
u16 my_strlen(unsigned char *src);
int my_memcmp(void *s1,void *s2,u16 len);
#endif

