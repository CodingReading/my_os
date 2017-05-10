;--------------------------------------------
;
;   boot.s  内核入口
;   包含根据GRUB Multiboot规范的定义
;----------------------------------------------

MBOOT_HEADER_MAGIC          equ 0x1BADB002  ;由规范定义
MOOT_PAGE_ALIGN             equ 1 << 0      ;4KB对齐
MBOOT_MEM_INFO              equ 1 << 1      ;通过Multiboot信息结构mem_*域包括可用内存信息
                                    ;(告诉GRUB把内存空间的信息包含在Multiboot信息结构中)
;定义我们使用的Multiboot标记
MBOOT_HEADER_FLAGS          equ MOOT_PAGE_ALIGN | MBOOT_MEM_INFO

;checksum必须为 magic + flags + checksum = 0
MBOOT_CHECKSUM              equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

;符合Multiboot规范的OS镜像需要magic Multiboot 头
;Multiboot头定义如下
;----------------------------------------------------
;偏移量    类型  域名      备注
;   0     u32   magic      必须
;   4     u32   flags      必须
;   8     u32   checksum   必须
;-----------------------------------------------------

[BITS 32]
section .text       ;代码段起始点
;   代码起始点设置符合Multiboot规范的标记
dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]          ;内核代码入口
[GLOBAL glb_mboot_ptr]  ;全局 struct multiboot* 变量
[EXTERN kern_entry]     ;声明内核C代码入口函数

start:
        cli                           ;未进入保护模式，关中断
        mov     esp , STACK_TOP       ;内核栈地址
        mov     ebp , 0               ;栈帧指针置0
        and     esp , 0xfffffff0      ;16字节对齐
        mov     [glb_mboot_ptr] , ebx ;ebx存储的指针值存入全局变量
        call    kern_entry            ;调用内核入口函数
stop:
        hlt                           ;停机
        jmp     stop                  ;结束
;----------------------------------------------------------------
section .bss                          ;未初始化数据段

stack:
        resb    0x8000                ;内核栈
glb_mboot_ptr:
        resb    4                     ;全局 multiboot指针
STACK_TOP   equ $ - stack - 1         ;内核栈顶



