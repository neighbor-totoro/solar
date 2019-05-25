#ifndef __SO_EQ_H__
#define __SO_EQ_H__

#include    "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EQ  \
    bool    (*eq)(Eq *, Eq *);  \
    bool    (*not_eq)(Eq *, Eq *);  \

typedef struct Eq Eq;
struct Eq{
    EQ
};

#ifdef __cplusplus
};
#endif

#endif
