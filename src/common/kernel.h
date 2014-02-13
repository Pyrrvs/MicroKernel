#ifndef		KERNEL_H_
# define	KERNEL_H_

# include "common/stdio.h"
# include "common/types.h"

# ifndef NULL
#  define NULL 0
# endif

# define KERNEL_VIRTUAL_BASE 0xC0000000
# define PANIC(msg) do { puts(ERR_COLOR msg); while (1); } while (0);
# define ALIGN_TO_PAGE(x) ((void*)(((uint32_t)x + 0xFFF) & 0xFFFFF000))

#endif
