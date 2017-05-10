/*----------------------
*   实现common中的端口读写函数
*-----------------------
*
*   gcc拓展内联汇编
*
*   具体语法参见 http://www.cnblogs.com/big-tree/p/5884543.html
*              http://wiki.osdev.org/Inline_Assembly/Examples#OUTx
*/

#include "common.h"

//端口写一个字节
inline void outb(uint16_t port, uint8_t value)
{       
    asm volatile ("outb %1, %0": :"dN"(port),"a"(value));
}

inline 