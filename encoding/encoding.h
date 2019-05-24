#ifndef __SO_ENCODING_H__
#define __SO_ENCODING_H___

#include    "strings.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ENCODE(x)   ENCODE ## x
#define DECODE(x)   DECODE ## x

#define ENCODER     \
    void    (*reset)(Encoder *);    \
    void    *(*encode)(Encoder *);  \
    int64   (*write)(Encoder *, String *);   \

#define DECODER     \
    void    (*reset)(Decoder *);    \
    void    *(*decode)(Decoder *);  \
    int64   (*write)(Decoder *, String *);   \


typedef struct Encoder Encoder{
    ENCODER
};

typedef struct Decoder Decoder{
    ENCODER
};

#ifdef __cplusplus
};
#endif

#endif
