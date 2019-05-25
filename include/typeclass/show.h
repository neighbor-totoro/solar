#ifndef __SO_SHOW_H__
#define __SO_SHOW_H__

#include    "array.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHOW    \
    array_t     *(*show)(Show *);   \

typedef struct Show Show;
struct Show{
    SHOW
};

#ifdef __cplusplus
};
#endif

#endif
