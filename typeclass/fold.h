#ifndef __FOLD_H__
#define __FOLD_H__

#include    "ord.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RANGE(x)    RANGE ## x

#define FOLD \
    bool    (*null)(Fold *);    \
    int64   (*length)(Fold *);  \
    Eq      *(*elem)(Fold *, Eq *);  \
    Fold    *(*map)(Fold *);         \
    void    *(*foldl)(Fold *, fold_f, void *);    \
    void    *(*foldr)(Fold *, fold_f, void *);    \

typedef Ord     *(*map_f)(Ord *);
typedef void    *(*fold_f)(Ord *, void *);

typedef struct Fold Fold;
struct Fold{
    FOLD
};

#ifdef __cplusplus
};
#endif

#endif
