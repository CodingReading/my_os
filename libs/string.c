#include "string.h"
/*
*   目前所有函数都未检查入口参数，未做边界，堆栈溢出检查
*/

inline void memcpy(char *dest, const char *src, uint32_t len)
{
    while (len--)
        *dest++ = *src++;
}

inline void memset(char *dest, uint32_t val, uint32_t len)
{
    while (len--)
        *dest++ = val;
}

inline void bzero(char *dest, uint32_t len)
{
    memset(dest, 0, len);
}

inline int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 > *str2)
            return 1;
        else if (*str1 < *str2)
            return -1;
        str1++;
        str2++;
    }

    if ((*str1 == 0) && (*str2 == 0)) 
        return 0;
    if (*str1)
        return 1;
    else return -1;
}

inline char* strcpy(char *dest, const char *src)
{
    while (*src)
        *dest++ = *src++;
    return dest;
}

inline uint32_t strlen(const char *str)
{
    uint32_t res = 0;
    while (*str++)
        res++;
    return res;
}




