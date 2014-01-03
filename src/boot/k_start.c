#include "console/console.h"

int k_start(void)
{
  while (1)
    {
      console_putc('#');
    }
  return 0xBABA;
}
