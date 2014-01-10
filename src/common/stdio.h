#ifndef		STDIO_H_
# define	STDIO_H_

# define ERR_COLOR "\x1B[31m"

void putc(char c);
void puts(const char *str);
void putnbr(int nbr);
void printk(char const *s, ...);

#endif
