#ifndef		LOWLEVEL_IO_H_
# define	LOWLEVEL_IO_H_

# include "common/types.h"

void outb(uint8_t val, uint16_t port);
void outw(uint8_t val, uint16_t port);
void outd(uint8_t val, uint16_t port);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t ind(uint16_t port);

#endif
