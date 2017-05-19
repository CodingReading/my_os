#ifndef INCLUDE_MULTIBOOT_H_
#define INCLUDE_MULTIBOOT_H_

#include "types.h"

typedef
struct multiboot_t{
    uint32_t flags;         //multiboot版本信息
    /*
    *从BIOS中获知的可用内存
    *mem_lower和mem_upper 分别指出低端和高端内存大小,K
    *低端内存的首地址是0，高端内存的首地址是1M
    *低端内存的最大可能值是 640K
    *高端内存的最大可能值是最大值减去1M,但并不保证是这个值
    */
    uint32_t mem_lower;
    uint32_t mem_upper;

    uint32_t boot_device;       //指出引导程序从哪个磁盘设备载入的映像BIOSOS
    uint32_t cmdline;           //内核命令行
    uint32_t mods_count;        //BOOT模块列表
    uint32_t mods_addr;

    //ELF 格式内核镜像的section头表。包括每项的大小，
    //一共有几项以及作为名字索引的字符串
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;

    /*
    *以下两项指出保存由 BIOS 提供的内存分布的缓冲区的地址和长度
    *mmap_addr 是缓冲区的地址, mmap_length 是缓冲区的总大小
    *缓冲区由一个或者多个下面的 mmap_entry_t 组成
    */
    uint32_t mmap_length;
    uint32_t mmap_addr;

    uint32_t drives_length;     //指出第一个驱动器结构的物理地址
    uint32_t drives_addr;       //指出第一个驱动器这个结构的大小
    uint32_t config_table;      //ROM配置表
    uint32_t boot_loader_name;  //boot_loader名字
    uint32_t apm_table;         //APM表
    uint32_t vbe_control_info;  
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

/**
 *size 是相关结构的大小,单位是字节,它可能大于最小值 20
 *base_addr_low 是启动地址的低位,32base_addr_high 是高 32 位,启动地址总共有 64 位
 *length_low 是内存区域大小的低位,32length_high 是内存区域大小的高 32 位,总共是 64 位
 *type 是相应地址区间的类型,1 代表可用,所有其它的值代表保留区域 RAM
*/

typedef
struct mmap_entry_t{
    uint32_t size;          //size 是不含size自身变量的大小
    uint32_t base_addr_low; 
    uint32_t base_addr_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
} __attribute__((packed)) mmap_entry_t;

//声明全局的multiboot *指针
extern multiboot_t *glb_mboot_ptr;
#endif