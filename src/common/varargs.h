#ifndef VARARGS_H_
# define VARARGS_H_

typedef char *va_list;

# define va_start(list, param) (list = (va_list)((char *)&param + sizeof(param)))
# define va_arg(list, type)    (*(type *)((list += sizeof(type)) - sizeof(type)))

#endif
