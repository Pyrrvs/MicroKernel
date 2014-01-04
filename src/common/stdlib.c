int atoi(const char *str)
{
  int res = 0, sign = 1, len = 0, i;

  for (i = 0; str[i] == '-' || str[i] == '+'; ++i)
    if (str[i] == '-')
      sign *= -1;
  for (int j = i; str[j] >= '0' && str[j] <= '9'; ++j)
    len += 1;
  for (; len; --len, ++i)
    res = res * 10 + (str[i] - '0');
  return res * sign;
}
