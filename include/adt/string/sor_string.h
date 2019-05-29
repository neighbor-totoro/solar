#ifndef __SOR_STRING_H__
#define __SOR_STRING_H__

#include    "typeclass/sor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SorString SorString;
struct SorString{
    int64   len;
    int64   cap;
    char    *buf;
};

#define SorStrLen(xs)       ((xs)->len)
#define SorStrStr(xs)       ((xs)->buf)
#define SorStrReset(xs)     ((xs)->len = 0)
#define SorStrSetLen(xs, n) ((xs)->len = n)

#define SorStrNewLiteral(xs)     SorStrNew(xs, sizeof(xs) - 1)

int     SorStrDel(SorString *);
SorString   *SorStrNew(const char *, int64);

int     SorStrAppend(SorString *, char);
int     SorStrRemove(SorString *, int64);
int     SorStrJoin(SorString *, SorString *);

SorString   *SorStrDup(SorString *, int64, int64);

int     SorStrCmp(SorString *, SorString *);

#ifdef __cplusplus
};
#endif

#endif
