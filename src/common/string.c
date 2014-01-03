# include "common/types.h"

void *memset(void *s, int c, size_t size)
{
  char *tmp = s;
  for (int i = 0; i < size; ++i)
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
