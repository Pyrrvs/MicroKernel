# include "common/string.h"
# include "io/vfb.h"

void putc(char c)
{
  vfb_write(&c, 1);
}

void puts(const char *str)
{
  vfb_write(str, strlen(str));
}

void putnbr(int nbr)
{
  if (nbr < 0)
    {
      putc('-');
      putnbr(nbr / -10);
      putc(-(nbr % 10) + '0');
    }
  else
    {
      if (nbr >= 10)
	putnbr(nbr / 10);
      putc((nbr % 10) + '0');      
    }
}

void putnbr_base(int nbr, const char *base)
{
  int len = strlen(base);
  if (nbr < 0)
    {
      putc('-');
      putnbr_base(nbr / -len, base);
      putc(base[-(nbr % len)]);
    }
  else
    {
      if (nbr >= len)
	putnbr_base(nbr / len, base);
      putc(base[(nbr % len)]);      
    }
}

void putunbr(unsigned int nbr)
{
  if (nbr >= 10)
    putnbr(nbr / 10);
  putc((nbr % 10) + '0');      
}

void putunbr_base(unsigned int nbr, const char *base)
{
  int len = strlen(base);
  if (nbr < 0)
    {
      putc('-');
      putnbr_base(nbr / -len, base);
      putc(base[-(nbr % len)]);
    }
  else
    {
      if (nbr >= len)
	putnbr_base(nbr / len, base);
      putc(base[(nbr % len)]);      
    }
}
