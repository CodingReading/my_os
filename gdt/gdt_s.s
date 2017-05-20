[GLOBAL load_gdt_to_gdtr]

load_gdt_to_gdtr:
    mov     eax, [esp + 4]
    lgdt    [eax]

    mov     ax, 0x10        ;数据段选择子
    mov     ds, ax
    mov     es, ax
    mov     ss, ax
    mov     fs, ax
    mov     gs, ax
    jmp     0x08:.flush   ;清空流水线，串行化处理器


.flush
    ret
