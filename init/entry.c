#include "types.h"
#include "console.h"
#include "common.h"

int kern_entry()
{
    console_clear();
    console_print_color("hello,my OS!\n",sc_white,sc_yello);
    return 0;
}