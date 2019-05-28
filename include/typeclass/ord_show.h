#ifndef __SO_SHOW_H__
#define __SO_SHOW_H__

#include    "sor_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_SHOW    \
    SorString   *(*show)(SorShow *);   \

typedef struct SorShow SorShow;
struct SorShow{
    SOR_SHOW
};

#ifdef __cplusplus
};
#endif

#endif
