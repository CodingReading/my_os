#include "console.h"
#include "debug.h"
#include "gdt.h"
int kern_entry()
{
    init_debug();

	init_gdt();

	init_idt();
	console_clear();

	printk_color(sc_black, sc_green, "Hello, OS kernel!\n");

	/*
	*	调用int n 后处理器自动压栈ss,usresp,eflags,cs,eip 执行宏汇编中断
  	*	处理函数ISR_(NO)ERRCODE 压栈 错误码（err_code）,中断号(int_num)
	*	然后jmp入 isr_common_stub 将 pt_regs 结构体中剩余寄存器压栈
	*   然后将此时esp值(实际处理函数的参数pt_regs*)压栈,调用isr_handle函数
	*/
	init_timer(200);
	//panic("test");

	//开中断
	asm volatile ("sti");
	return 0;
}