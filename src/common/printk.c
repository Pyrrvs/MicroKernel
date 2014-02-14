#include "common/varargs.h"
#include "common/string.h"
#include "common/stdio.h"

#define LONG_MODIF (1 << 0)

static inline int default_print(char c, va_list *args, int modifier)
{
  char *str;
  unsigned int uval;
  int val;

  switch (c)
    {
    case 'u':
      uval = va_arg(*args, unsigned int);
      putunbr(uval);
      break;
    case 'd':
      val = va_arg(*args, int);
      putnbr(val);
      break;
    case 's':
      str = va_arg(*args, char*);
      puts(str);
      break;
    case 'x':
      puts("0x");
      uval = va_arg(*args, unsigned int);
      putunbr_base(uval, HEX_BASE);
      break;
    case 'l':
      return modifier | LONG_MODIF;
    default:
      putc(c);
      break;
    }
  return 0;
}

static inline int long_print(char c, va_list *args, int modifier)
{
  char *str;
  unsigned long long uval;
  long long val;

  switch (c)
    {
    case 'u':
      uval = va_arg(*args, unsigned long long);
      putlunbr(uval);
      break;
    case 'd':
      val = va_arg(*args, long long);
      putlnbr(val);
      break;
    case 'x':
      puts("0x");
      uval = va_arg(*args, unsigned long long);
      putlunbr_base(uval, HEX_BASE);
      break;
    default:
      putc(c);
      break;
    }
  return 0;
}


void printk(char const *s, ...)
{
  va_list args;
  int modifier = 0;
  unsigned int i, len;

  len = strlen(s);
  va_start(args, s);
  for (i = 0; i < len; ++i)
    {
      if (s[i] == '%' || modifier)
        {
	  if (s[i] == '%')
	    i += 1;
	  if (modifier & LONG_MODIF)
	    modifier = long_print(s[i], &args, modifier);
	  else
	    modifier = default_print(s[i], &args, modifier);
        }
      else
	putc(s[i]);
    }
}
