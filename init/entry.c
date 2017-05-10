#include "types.h"

int kern_entry()
{
    uint8_t *input = (uint8_t)0xB8000;      //显示缓冲区
    uint8_t  color = (0 << 4) | (15 & 0x0f);

    *input++ = 'H'; *input++ = color;
	*input++ = 'e'; *input++ = color;
	*input++ = 'l'; *input++ = color;
	*input++ = 'l'; *input++ = color;
	*input++ = 'o'; *input++ = color;
	*input++ = ','; *input++ = color;
    *input++ = ' '; *input++ = color;
	*input++ = 'M'; *input++ = color;
	*input++ = 'y'; *input++ = color;
	*input++ = 'O'; *input++ = color;
	*input++ = 'S'; *input++ = color;
	*input++ = ' '; *input++ = color;
	*input++ = 'K'; *input++ = color;
	*input++ = 'e'; *input++ = color;
	*input++ = 'r'; *input++ = color;
	*input++ = 'n'; *input++ = color;
	*input++ = 'e'; *input++ = color;
	*input++ = 'l'; *input++ = color;
	*input++ = '!'; *input++ = color;

    return 0;
}