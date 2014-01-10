#ifndef		KERNEL_H_
# define	KERNEL_H_

# include "common/stdio.h"

# define PANIC(msg) do { puts(ERR_COLOR msg); while (1); } while (0);

#endif
