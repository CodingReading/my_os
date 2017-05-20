/**
*
*       全局描述符表GDT相关定义
*/


#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

typedef
struct gdt_entry_t{
    uint16_t seg_limit_low;     //段界限0~15
    uint16_t seg_base_low;      //段基地址0~15
    uint8_t  seg_base_middle;   //段基地址16~23
    uint8_t  access;            //TYPE,S,DPL,P位
    uint8_t  granularity;       //段界限16~19，AVL,L,D/B,G位
    uint8_t  seg_base_high;     //段基地址31～24
}__attribute__((packed)) gdt_entry_t;

typedef
struct gdt_ptr_t{
    uint16_t limit;     //全局描述符界限
    uint32_t base;      //全局描述符基地址
}__attribute__((packed)) gdt_ptr_t;

//初始化全局描述符表
void init_gdt();

//gdt加载到GDTR寄存器
extern void load_gdt_to_gdtr(uint32_t);

#endif