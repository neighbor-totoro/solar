#ifndef __SO_ORD_H__
#define __SO_ORD_H__

#include    "eq.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ORD     \
    bool    (*lt)(Ord *, Ord *);  \
    bool    (*le)(Ord *, Ord *);  \
    bool    (*gt)(Ord *, Ord *);  \
    bool    (*ge)(Ord *, Ord *);  \

typedef struct Ord Ord;
struct Ord{
    EQ
    ORD
};

#ifdef __cplusplus
};
#endif

#endif
