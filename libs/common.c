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
{//在修改asm命令之前，a修饰符将val放在eax寄存器中，并且Nd允许将一个字节的常量值组合为常数
 //为其他情况释放edx寄存器。
    asm volatile ("outb %1, %0": :"dN"(port),"a"(value));
}

inline uint8_t inb(uint16_t port)
{   //强制返回值ret保存在输出寄存器eax中
    uint8_t ret;
    asm volatile ("inb %1, %0"
                  : "=a"(ret)
                  : "Nd"(port));
    return ret;
}

inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0"
                  : "=a"(ret)
                  : "Nd"(port));
    return ret;
}