#ifndef __SOR_EQ_H__
#define __SOR_EQ_H__

#include    "sor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_EQ  \
    bool    (*eq)(SorEq *, SorEq *);  \
    bool    (*not_eq)(SorEq *, SorEq *);  \

typedef struct SorEq SorEq;
struct SorEq{
    SOR_EQ
};

#ifdef __cplusplus
};
#endif

#endif
