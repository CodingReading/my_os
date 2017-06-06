/*
*   中断描述符相关的函数实现
*
*/

#include "common.h"
#include "string.h"
#include "debug.h"
#include "idt.h"

//中断描述符表
idt_entry_t idt_entries[256];

//IDTR
idt_ptr_t idt_ptr;

//中断处理函数的指针数组
interrupt_handler_t interrupt_handlers[256];

//设置中断描述符
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

//声明加载IDTR的函数
extern void load_idt_to_idtr(uint32_t);

//初始化中断描述符表
void init_idt()
{
	//重新映射IRQ表
	//两片级联的 Intel 8259A 芯片
	//主片端口 0x20 0x21
	//从片端口 0xA0 0xA1

	//初始化主片从片
	//0001 0001
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	//设置主片IRQ从0x20号中断开始
	outb(0x21, 0x20);

	//设置主片IRQ从0x28号中断开始
	outb(0xA1, 0x28);

	//设置主片IR2 引脚连接从片
	outb(0x21, 0X04);

	//告诉从片输出引脚和主片IR2号相连
	outb(0xA1, 0x02);

	//设置主片和从片按照 8086的方式工作
	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	//设置主从片允许中断
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

    //中断描述符表清零
    bzero((uint8_t*)&interrupt_handlers,256 * sizeof(interrupt_handler_t));
    idt_ptr.limit = 256 * sizeof(idt_entry_t) - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    //中断处理函数的指针数组清零
    bzero((uint8_t)&idt_entries,256 * sizeof(idt_entry_t));

    // 0-32:  用于 CPU 的中断处理
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

	// 255 将来用于实现系统调用
	idt_set_gate(255, (uint32_t)isr255, 0x08, 0x8E);

	// 更新设置中断描述符表
	load_idt_to_idtr((uint32_t)&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low  = base & 0xffff;
    idt_entries[num].base_high = (base >> 16) & 0xffff;

    idt_entries[num].sel       = sel;
    idt_entries[num].always0   = 0;
    idt_entries[num].flags     = flags;      // |60 用户态DPL设置为3
}

//注册中断处理函数
void register_interrupt_handler(uint8_t n, interrupt_handler_t h)
{
    interrupt_handlers[n] = h;
}

//调用中断处理函数
void isr_handler(pt_regs *regs)
{
    if (interrupt_handlers[regs->int_num])
        interrupt_handlers[regs->int_num](regs);
    else
        printk_color(sc_black,sc_red,"unhandled interrupt:%d\n",regs->int_num);
}

//IRQ处理函数
void irq_handler(pt_regs *regs)
{
	//发送中断结束信号给PICS
	//按照我们的设置，从32 号中断起为用户自定义中断
	//因为单片的 Intel 8259A 芯片只能处理8级中断
	//所以大于等于 40 的中断号由从片处理

	if (regs->int_num >= 40)
		outb(0xA0, 0x20);	//发送重设信号给从片
	
	outb(0x20, 0x20);		//发送重设信号给主片

	if (interrupt_handlers[regs->int_num])
		interrupt_handlers[regs->int_num](regs);
}