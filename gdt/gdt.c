#include  "gdt.h"
#include  "string.h"

//全局描述符表长度
#define GDT_LENGTH 5

gdt_entry_t gdt_entries[GDT_LENGTH];

//GDTR
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit,
                        uint8_t access, uint8_t gran);

//声明内核栈地址
extern uint32_t stack;

//初始化
void init_gdt()
{
    gdt_ptr.limit =  sizeof(gdt_entry_t) * GDT_LENGTH - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    //平坦模式
    gdt_set_gate(0,0,0,0,0);                    //第一个必须为0
    gdt_set_gate(1,0,0xffffffff,0x9a,0xcf);     //指令段
    gdt_set_gate(2,0,0xffffffff,0x92,0xcf);     //数据段
    gdt_set_gate(3,0,0xffffffff,0xfa,0xcf);     //用户代码段
    gdt_set_gate(4,0,0xffffffff,0xf2,0xcf);     //用户数据段

    //加载全局描述符表到 GDTR 寄存器
    load_gdt_to_gdtr((uint32_t)&gdt_ptr);
}

//构造全局描述符表
static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit,
                        uint8_t access, uint8_t gran)
{
    gdt_entries[num].seg_base_low       = (base & 0xffff);
    gdt_entries[num].seg_base_middle    = (base >> 16) & 0xff;
    gdt_entries[num].seg_base_high      = (base >> 24) & 0xff;

    gdt_entries[num].seg_limit_low      = (limit & 0xffff);
    gdt_entries[num].granularity        = (limit >> 16) & 0x0f;

    gdt_entries[num].granularity        |= gran & 0xf0;
    gdt_entries[num].access             = access;
}                        
                        

                                        