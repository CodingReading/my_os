#ifndef INCLUDE_ELF_H_
#define INCLUDE_ELF_H_

#include "types.h"
#include "multiboot.h"

#define ELF32_ST_TYPE(i) ((i) & 0xf)

//ELF格式区段头
typedef
struct elf_section_header_t{
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
}_attribute_((packed)) elf_section_header_t;

//ELF符号格式
typedef 
struct elf_symbol_t{
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t  info;
    uint8_t  other;
    uint16_t shndx;
}_attribute_((packed)) elf_symbol_t;

//ELF信息
typedef
struct elf_t{
    elf_symbol_t *symtab;
    uint32_t      symtabsz;
    const char   *strtab;
    uint32_t      strtabsz;
}elf_t;

//从multiboot_t 结构获取信息ELF
elf_t elf_from_multiboot(multiboot_t *mb);

//查看的符号信息ELF
const char* elf_lookup_symbol(uint32_t addr, elf_t *elf);

#endif