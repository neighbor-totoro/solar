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

typedef struct SorBase64Encoder SorBase64Encoder;
struct SorBase64Encoder{
    bool    flg; // is padding?
    SorEncoder  n;
    SorString   *src;
    const char  *encode;
};

typedef struct SorBase64Decoder SorBase64Decoder;
struct SorBase64Decoder{
    bool    flg;
    SorDecoder  n;
    SorString   *src;
    uint8   decode[256];
};

SorEncoder  *SorBase64NewEncoder(void);
int     SorBase64DelEncoder(SorEncoder *);

SorDecoder  *SorBase64NewDecoder(void);
int     SorBase64DelDecoder(SorDecoder *);

SorEncoder  *SorBase64NewUrlEncoder(void);
int     SorBase64DelUrlEncoder(SorEncoder *);

SorDecoder  *SorBase64NewUrlDecoder(void);
int     SorBase64DelUrlDecoder(SorDecoder *);

#ifdef __cplusplus
};
#endif

#endif
