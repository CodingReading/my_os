/**
*       中断描述符结构
*       初始化和安装类似于全局描述符
*/

#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_

#include "types.h"

//初始化中断描述符表
void init_idt();

//中断描述符
typedef
struct idt_entry_t
{
    uint16_t    base_low;   //中断处理程序0~15位
    uint16_t    sel;        //段选择子
    uint8_t     always0;    //置零
    uint8_t     flags;      //
    uint16_t    base_high;  //中断处理程序16~31位
}__attribute__((packed)) idt_entry_t;

typedef
struct idt_ptr_t
{
    uint16_t    limit;  //界限
    uint32_t    base;   //基址
}__attribute__((packed)) idt_ptr_t;


//中断处理需要保护的状态
typedef
struct pt_regs_t
{
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_num;    //中断号
    uint32_t err_code;  //错误码

    //以下由处理器自动压入
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t usresp;
    uint32_t ss;
}__attribute__((packed)) pt_regs;

//定义中断处理函数指针
typedef void (*interrupt_handler_t)(pt_regs*);

//注册一个中断处理函数
void register_interrupt_handler(uint8_t n, interrupt_handler_t h);

//调用中断处理函数
void isr_handler(pt_regs *regs);

/**
*       按照Intel的规定,0~19号中断属于CPU所有 ,而且第20-31号中断也被Intel保留,
*       所以从32~255号才属于用户自定义中断。虽说是"用户自定义",其实在x86上有些
*       中断按照习惯还是给予了固定的设备。比如32号是timer中断,33号是键盘中断等等。
*/

// 声明中断处理函数 0 ~ 19 属于 CPU 的异常中断
// ISR中断服务程序:(interrupt service routine)
void isr0();        // 0 #DE 除 0 异常
void isr1();        // 1 #DB 调试异常
void isr2();        // 2 NMI
void isr3();        // 3 BP 断点异常
void isr4();        // 4 #OF 溢出
void isr5();        // 5 #BR 对数组的引用超出边界
void isr6();        // 6 #UD 无效或未定义的操作码
void isr7();        // 7 #NM 设备不可用无数学协处理器()
void isr8();        // 8 #DF 双重故障有错误代码()
void isr9();        // 9 协处理器跨段操作
void isr10();       // 10 #TS 无效TSS有错误代码()
void isr11();       // 11 #NP 段不存在有错误代码()
void isr12();       // 12 #SS 栈错误有错误代码()
void isr13();       // 13 #GP 常规保护有错误代码()
void isr14();       // 14 #PF 页故障有错误代码()
void isr15();       // 15 CPU 保留
void isr16();       // 16 #MF 浮点处理单元错误
void isr17();       // 17 #AC 对齐检查
void isr18();       // 18 #MC 机器检查
void isr19();       // 19 #XM SIMD单指令多数据()浮点异常

//20~31 intel公司保留，建议不要使用
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

//32~255    用户自定义中断
void isr255();

#endif