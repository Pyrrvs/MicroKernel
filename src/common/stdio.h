#ifndef		STDIO_H_
# define	STDIO_H_

# define ERR_COLOR "\x1B[31m"
# define WARN_COLOR "\x1B[33m"
# define INFO_COLOR "\x1B[36m"
# define SUCC_COLOR "\x1B[32m"
# define DEF_COLOR "\x1B[37m"

void putc(char c);
void puts(const char *str);
void putnbr(int nbr);
void printk(char const *s, ...);

#endif
