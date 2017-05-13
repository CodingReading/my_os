/*--------------------------------------------------
*   实现屏幕操作的函数
*   文本模式下VGA保留内存0xb8000-0xb8fa0
*   0xfa0 = 25 * 80 * 2  对应80 × 25 文本模式
    每个字符占两个字节，低字节为字符，高字节为显示的颜色
*--------------------------------------------------
*/

#include "types.h"
#include "console.h"

//显示缓冲区起始地址为0xb8000
static uint16_t *video_mem = (uint16_t*) 0xb8000;

//光标坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0; 

/*              移动光标
*索引寄存器端口号 0x3d4，向它写入一个值来指定某个内部寄存器
*   两个光标寄存器索引值分别为 14， 15 分别提供高8位低8位
*指定寄存器后通过数据端口 0x3d5 来进行读写
*/
static void move_cursor()
{
    uint16_t cursor_location = cursor_x + cursor_y * 80;
    outb(0x3d4, 14);
    outb(0x3d5, cursor_location >> 8);
    outb(0x3d4, 15);
    outb(0x3d5, cursor_location);
}

//屏幕滚动
static void scroll()
{
    //attribute_byte构造出黑底白字
    uint8_t  attribute_byte = 0x0f;  //亮白色字，黑底
    uint16_t blank = 0x20 | (attribute_byte << 8);  //空格为0x20

    //纵坐标大于等于25换行
    if (cursor_y >= 25)
    {
        //所有行的数据移动到第一行, 第一行消失
        for (uint32_t i = 0; i < 24 * 80; i++)
            video_mem[i] = video_mem[i + 80];
        //最后一行空格填充
        for (uint32_t i = 24 * 80; i < 25 * 80; i++)
            video_mem[i] = blank;

        cursor_y = 24;
    }
}

//清屏
void console_clear()
{
    uint8_t   attribute_byte = 0x0f;
    uint16_t blank = 0x20 | (attribute_byte << 8);
    for (uint32_t i = 0; i < 25 * 80; i++)
        video_mem[i] = blank;
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

//输出一个字符
void console_putc_color(char c, screen_color_t back , screen_color_t fore)
{
    uint8_t backcolor = (uint8_t) back;
    uint8_t forecolor = (uint8_t) fore;
    uint8_t attribute_byte = (backcolor << 4) | (forecolor);
    uint16_t attribute     = attribute_byte << 8;

    //0x8退格 0x9tab
    if (c == 0x8 && cursor_x)
        cursor_x--;
    else if (c == 0x9)
        cursor_x = (cursor_x + 8) & (~7);
    else if (c == '\r')
        cursor_x = 0;
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        video_mem[cursor_x + cursor_y * 80] = c | attribute;
        cursor_x++;
    }
    
    //满80换行
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();   //纵坐标大于等于25换行
    move_cursor();
}

//屏幕打印字符串(黑底白字)
void console_print(char *cstr)
{
    while (*cstr)
        console_putc_color(*cstr++, sc_black, sc_white);
}

//屏幕打印字符串带颜色
void console_print_color(char *cstr,screen_color_t back,screen_color_t fore)
{
    while(*cstr)
        console_putc_color(*cstr++,back,fore);
}

void console_print_hex(uint32_t n, screen_color_t back , screen_color_t fore)
{
    console_print_color("0x",back,fore);
    if (n == 0)
        console_print_color("0",back,fore);
    char a[8];
    uint16_t count = 0;
    while (n)
    {
        uint32_t temp = n % 16;
        if (temp < 10)
            a[count++] = '0' + temp;
        else
            a[count++] = 'A' + temp - 10;
        n >>= 4;
    }

    for (uint16_t i = count - 1; i >= 0; i--)
        console_putc_color(a[i],back,fore);
}

//屏幕输出十进制整数
void console_print_dec(uint32_t n, screen_color_t back, screen_color_t fore)
{
    char a[32];
    uint16_t count = 0;
    while (n)
    {
        uint32_t temp = n % 10;
        a[count++] = temp + '0';
        n /= 10;
    }

    for (uint16_t i = count - 1; i >= 0; i--)
        console_putc_color(a[i], back, fore);
}

