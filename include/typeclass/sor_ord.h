#ifndef __SOR_ORD_H__
#define __SOR_ORD_H__

#include    "sor_eq.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_ORD     \
    bool    (*lt)(SorOrd *, SorOrd *);  \
    bool    (*le)(SorOrd *, SorOrd *);  \
    bool    (*gt)(SorOrd *, SorOrd *);  \
    bool    (*ge)(SorOrd *, SorOrd *);  \

typedef struct SorOrd SorOrd;
struct SorOrd{
    SOR_EQ
    SOR_ORD
};

#ifdef __cplusplus
};
#endif

#endif
