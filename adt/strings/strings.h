#ifndef __SO_STRINGS_H__
#define __SO_STRINGS_H__

#include    "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct String String;
struct String{
    int64   len;
    int64   cap;
    char    *buf;
};

int     string_delete(String *);
String  *string_new(const char *, int64);

int     string_append(String *, char);
int     string_remove(String *, int64);
int     string_join(String *, String *);

String  *string_dup(String *, int64, int64);

int     string_compare(String *, String *);

#ifdef __cplusplus
};
#endif

#endif
