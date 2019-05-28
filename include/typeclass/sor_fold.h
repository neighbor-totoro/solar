#ifndef __FOLD_H__
#define __FOLD_H__

#include    "sor_ord.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_RANGE(x)    SOR_RANGE ## x

#define SOR_FOLD    \
    bool    (*null)(SorFold *);     \
    int64   (*length)(SorFold *);   \
    SorEq   *(*elem)(SorFold *, SorEq *);   \
    SorFold *(*map)(SorFold *, SorMapFunc);     \
    void    *(*foldl)(SorFold *, SorFoldFunc, void *);  \
    void    *(*foldr)(SorFold *, SorFoldFunc, void *);  \

typedef SorOrd  *(*SorMapFunc)(SorOrd *);
typedef void    *(*SorFoldFunc)(SorOrd *, void *);

typedef struct SorFold SorFold;
struct SorFold{
    SOR_FOLD
};

#ifdef __cplusplus
};
#endif

#endif
