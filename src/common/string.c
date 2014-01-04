# include "common/types.h"

void *memset(void *s, int c, size_t size)
{
  int i;
  char *tmp = s;
  for (i = 0; i < size; ++i)
    tmp[i] = c;
  return s;
}

int strlen(const char *str)
{
  int i = 0;

  while (str[i])
    ++i;
  return i;
}
