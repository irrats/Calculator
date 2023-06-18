#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define WORDSIZE sizeof(size_t)


#ifndef NDEBUG
#define ER_PRINT(str)    fprintf(stderr, str)

#else
#define ER_PRINT(str)
#endif

#endif

