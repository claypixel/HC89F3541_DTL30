#include "my_stdio.h"


int my_memcmp(void *s1,void *s2,u16 len)
{
 int count = 0;
    const char *str1,*str2;
    str1 = (const char*)s1;
    str2 = (const char*)s2;
    for(count = 0;count < len;count++)
    {
     if(*(str1 + count) != *(str2 + count))
     {
         return *(str1 + count) > *(str2 + count) ?1:-1;
     } 
    }
    return 0;
}
void *my_memset(void *src,unsigned char ch,unsigned char count)
{
  unsigned char *tmp = (unsigned char *)src; //目前仅支持uchar型数组
  if(src == NULL)
      return NULL;
  while(count--)
  {
   *tmp ++ = ch;
  }
  return src;
}

void *my_memcpy(void * dest,const void *src,unsigned short count)
{
    unsigned char *pdest = (unsigned char*)dest;
    const unsigned char *psrc = (const unsigned char *)src;
    unsigned short i = 0;
    if((dest == NULL)||(src == NULL))
    {
     return NULL;
    } 
    if((pdest <= psrc)||(pdest > psrc + count))
    {
     for(i = 0;i < count;i ++)
        {
         pdest[i] = psrc[i];
        }
    }
    else
    {
     for(i = count;i > 0;i --)
        {
         pdest[i - 1] = psrc[i - 1];
        }
    }
    
    return dest;
}

char *my_strcpy(char * dest,const char *src)
{
 char * p = dest;
    while(*src != '\0')
    {
     *dest++ = *src;
    }  
     *dest = '\0';
    return p;
}


/*
 字符串比较函数
返回值
=0：s1 = s2
<0: s1 < s2
>0: s1 > s2
*/
int my_strcmp(char * s1,char *s2) 
{
  while(*s1 && *s2 && *s1 == *s2)
  {
     s1++;
     s2++;
  }
  return *s1 - *s2;
}

u16 my_strlen(unsigned char *src)
{
 u16 len = 0;
   if(src == NULL)
   {
    return 0;
   }
   for(len = 0;*src ++ != '\0';)
   {
    len ++;
   }
   return len;
}