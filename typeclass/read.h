#ifndef __SO_READ_H__
#define __SO_READ_H__

#include    "array.h"

#ifdef __cplusplus
extern "C" {
#endif

#define READ    \
    void    *(*read)(array_t *);   \

typedef struct Read Read;
struct Read{
    READ
};

#ifdef __cplusplus
};
#endif

#endif
