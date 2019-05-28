#ifndef __SOR_READ_H__
#define __SOR_READ_H__

#include    "sor_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_READ    \
    SorRead     *(*read)(SorString *);   \

typedef struct SorRead SorRead;
struct SorRead{
    SOR_READ
};

#ifdef __cplusplus
};
#endif

#endif
