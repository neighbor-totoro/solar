#ifndef __SOR_ENCODING_H__
#define __SOR_ENCODING_H___

#include    "adt/string/sor_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_ENCODER     \
    void    (*reset)(SorEncoder *);     \
    SorString   *(*encode)(SorEncoder *);   \
    int64   (*write)(SorEncoder *, SorString *);    \

#define SOR_DECODER     \
    void    (*reset)(SorDecoder *);     \
    SorString   *(*decode)(SorDecoder *);   \
    int64   (*write)(SorDecoder *, SorString *);    \

typedef struct SorEncoder SorEncoder;
struct SorEncoder{
    SOR_ENCODER
};

typedef struct SorDecoder SorDecoder;
struct SorDecoder{
    SOR_ENCODER
};

#ifdef __cplusplus
};
#endif

#endif
