#ifndef _UTILS_H
#define _UTILS_H

static inline int align4(int n)
{
    return n + ((4 - (n & 3)) & 3);
}

#endif
