#ifndef __SOR_BASE64_H__
#define __SOR_BASE64_H__

#include    "typeclass/sor_sugar.h"
#include    "adt/string/sor_string.h"
#include    "encoding/sor_encoding.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BASE64_STD  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define BASE64_URL  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"

#define SOR_BASE64_STR_APPEND(xs, x)    {if(SorStrAppend((xs), (x)) == 1) goto ERR;}

typedef struct SorBase64Encoder SorBase64Encoder;
struct SorBase64Encoder{
    SorEncoder  n;
    SorString   *src;
    const char  *encode;
};

typedef struct SorBase64Decoder SorBase64Decoder;
struct SorBase64Decoder{
    SorDecoder  n;
};

SorEncoder  *SorBase64NewEncoder(void);
int     SorBase64DelEncoder(SorEncoder *);

SorDecoder  *SorBase64NewDecoder(void);
int     SorBase64DelDecoder(SorEncoder *);

SorEncoder  *SorBase64NewUrlEncoder(void);
int     SorBase64DelUrlEncoder(SorEncoder *);

SorDecoder  *SorBase64NewUrlDecoder(void);
int     SorBase64DelUrlDecoder(SorEncoder *);

#ifdef __cplusplus
};
#endif

#endif
