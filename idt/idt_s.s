;定义两个中断处理函数的宏

;宏汇编技术 无错误代码的中断
%macro ISR_NOERRCODE 1      
[GLOBAL isr%1]
isr%1:
    cli                 ;关中断
    push 0              ;push无效的中断错误码，用来占位，
                        ;方便清理的时候统一处理有中断号和无中断号的例程
    push %1             ;push中断号
    jmp isr_common_stub
%endmacro

;有错误代码的中断
%macro ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
    cli                 ;关中断
    push %1             ;push中断号
    jmp isr_common_stub
%endmacro

;定义中断处理函数
ISR_NOERRCODE 0         ;0  #DE  除0异常
ISR_NOERRCODE 1         ;1  #DB  调试异常
ISR_NOERRCODE 2         ;2  #NMI
ISR_NOERRCODE 3         ;3  #BP  断点
ISR_NOERRCODE 4         ;4  #OF  溢出
ISR_NOERRCODE 5         ;5  #BR  对数组的引用超过边界
ISR_NOERRCODE 6         ;6  #UD  无效或未定义的操作码
ISR_NOERRCODE 7         ;7  #NM  设备不可用（无数学协处理器）
ISR_ERRCODE   8         ;8  #DF  双重故障
ISR_NOERRCODE 9         ;9       协处理器段超越（保留）。协处理器执行浮点运算时，至少
                        ;        有两个操作数不在一个段内（跨段）
ISR_ERRCODE   10        ;10 #TS  无效TSS
ISR_ERRCODE   11        ;11 #NP  段不存在
ISR_ERRCODE   12        ;12 #SS  栈段故障
ISR_ERRCODE   13        ;13 #GP  常规保护
ISR_ERRCODE   14        ;14 #PF  页故障
ISR_NOERRCODE 15        ;15      intel保留，不能使用
ISR_NOERRCODE 16        ;16 #MF  X87FPU(浮点处理单元)浮点处理错误
ISR_ERRCODE   17        ;17 #AC  对齐检查
ISR_NOERRCODE 18        ;18 #MC  机器检查
ISR_NOERRCODE 19        ;19 #XM  SIMD(单指令多数据) 浮点异常

;20~31 intel公司保留建议不要使用
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

; 32 ~ 255 用户自定义
ISR_NOERRCODE 255

