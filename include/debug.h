#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "console.h"
#include "vargs.h"
#include "elf.h"

#define assert(x, info)                     \
        do{                                 \
            if (!x)                         \
                panic(info);                \
        }while(0)

//编译期间静态检测
#define static_assert(x)                    \
        switch (x) {case 0: case(x): ;}

//初始化debug信息
void init_debug();

//打印当前的函数调用栈信息
void panic(const char *msg);

//打印当前的段寄存器值
void print_cur_status();

//内核的打印函数
void printk(const char *format, ...);

//内核的打印函数带颜色
void pirntk_color(screen_color_t back, screen_color_t fore, const char *format, ...);

#endif