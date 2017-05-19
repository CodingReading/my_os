/**
*   ELF格式解析相关函数
*
*/

#include "common.h"
#include "string.h"
#include "elf.h"

//从multiboot结构获取信息ELF
elf_t elf_from_multiboot(multiboot_t *mb)
{
     elf_t elf;
     elf_section_header_t *sh = (elf_section_header_t*)mb->addr;
     uint32_t shstrtab = sh[mb->shndx].addr;

     for (int i = 0; i < mb->num; i++)
     {
         const char* name = (const char*)(shstrtab + sh[i].name);
         //GRUB提供的multiboot信息中寻找
         //内核ELF格式所提供的字符串表和符号表
         if (strcmp(name,".strtab") == 0)
         {
             elf.strtab = (const char*)sh[i].addr;
             elf.strtabsz = sh[i].size;
         }

         if (strcmp(name,".symtab") == 0)
         {
             elf.symtab = (elf_symbol_t *)sh[i].addr;
             elf.symtabsz = sh[i].size;
         }

    }

     return elf;
}

//查看ELF的符号信息
const char* elf_lookup_symbol(uint32_t addr, elf_t* elf)
{
    
    for (int i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++)
    {
        if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2)
            continue;
        //通过函数调用地址查到函数的名字
        if (addr >= elf->symtab[i].value && addr < elf->symtab[i].value
                                            +elf->symtab[i].size)
            return (const char*)((uint32_t) elf->strtab + elf->symtab[i].name);
    }

    return NULL;
}