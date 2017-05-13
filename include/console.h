/*--------------------
*   屏幕操作相关函数头文件
*---------------------
*/

#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"

//定义屏幕颜色的枚举 80 × 25 文本模式下的颜色表
//《x86汇编语言从实模式到保护模式》P51
typedef 
enum screen_color{
    sc_black    = 0,
    sc_blue     = 1,
    sc_green    = 2,
    sc_cyan     = 3,
    sc_red      = 4,
    sc_magenta  = 5,	//品红
    sc_brown    = 6,
    sc_white    = 7,
    sc_gray     = 8,
    sc_light_bule    = 9,
	sc_light_green	 = 10,
	sc_light_cyan	 = 11,
	sc_light_red	 = 12,
	sc_light_magenta = 13,
	sc_yello		 = 14,
	sc_bright_white  = 15,	
}screen_color_t;

//清屏
void console_clear();

//屏幕输出一个带颜色字符	指定字符背景色，前景色
void console_putc_color(char c, screen_color_t back , screen_color_t fore);

//屏幕打印一个字符串
void console_print(char *cstr);

//屏幕输出16进制整数
void console_print_hex(uint32_t n, screen_color_t back , screen_color_t fore);

//屏幕输出一个10进制数
void console_print_dec(uint32_t n, screen_color_t back , screen_color_t fore);

#endif