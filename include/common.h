/*------------------------
*   类型定义，函数声明
*-------------------------
*/

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

//写端口一个字节
void outb(uint16_t port, uint8_t value);

//读端口一个字节
uint8_t inb(uint16_t port);

//读端口一个字
uint16_t inw(uint16_t port);

#endif