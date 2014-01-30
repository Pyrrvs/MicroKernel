#include "common/varargs.h"
#include "common/string.h"
#include "common/stdio.h"

void printk(char const *s, ...)
{
    va_list args;
    unsigned int i, len, addr;
    int val;
    char *str;

    len = strlen(s);
    va_start(args, s);
    for (i = 0; i < len; ++i)
    {
        if (s[i] == '%')
        {
            i = i + 1;
            switch (s[i])
            {
            case 'd':
                val = va_arg(args, int);
                putnbr(val);
                break;
            case 's':
                str = va_arg(args, char*);
                puts(str);
                break;
            case 'x':
                addr = va_arg(args, unsigned int);
                putunbr_base(addr, HEX_BASE);
            default:
                putc(s[i]);
                break;
            }
        }
        else
            putc(s[i]);
    }
}
