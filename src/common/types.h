#ifndef		TYPES_H_
# define	TYPES_H_

// We'll need arch dependant typedefs if we want to support 
// other processors.

// 32-bits x86 arch
typedef long long unsigned	uint64_t;
typedef long long		int64_t;
typedef unsigned		uint32_t;
typedef int			int32_t;
typedef unsigned short		uint16_t;
typedef short			int16_t;
typedef unsigned char		uint8_t;
typedef char			int8_t;
typedef uint64_t		size_t;
typedef int64_t			ssize_t;
#endif
