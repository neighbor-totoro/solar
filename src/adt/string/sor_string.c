#include    <stdlib.h>
#include    <string.h>
#include    "typeclass/sor_sugar.h"
#include    "adt/string/sor_string.h"

static int  strGrow(SorString *);
static int  strAppendString(SorString *, const char *, int64);

SorString   *
SorStrNew(const char *s, int64 n)
{
    SorString   *xs;

    if(!(xs = calloc(1, sizeof(*xs))))
        return NULL;
    if(n > 0 && strAppendString(xs, s, n) != 0)
        goto ERR;
    return xs;
ERR:
    if(xs)
        SorStrDel(xs);
    return NULL;
}

int
SorStrDel(SorString *xs)
{
    if(xs->buf)
        free(xs->buf);
    free(xs);
    return 0;
}

int
SorStrRemove(SorString *xs, int64 idx)
{
    if(idx >= xs->len)
        return -1;
    xs->len--;
    memmove(xs->buf+idx, xs->buf+idx+1, (xs->len - idx));
    return 0;
}

int
SorStrAppend(SorString *xs, char c)
{
    if(xs->len == xs->cap && strGrow(xs) != 0)
        return -1;
    xs->buf[xs->len++] = c;
    return 0;
}

int
SorStrJoin(SorString *xs, SorString *ys)
{
    return strAppendString(xs, ys->buf, ys->len);
}

SorString  *
SorStrDup(SorString *xs, int64 x, int64 y)
{
    if(y > xs->len)
        return NULL;
    if(x <= 0)
        x = 0;
    if(y == -1)
        y = xs->len;
    if(x >= y)
        return NULL;
    return SorStrNew(xs->buf + x, y - x);
}

int
SorStrCmp(SorString *xs, SorString *ys)
{
    int     r;

    BMATCH(xs->len < ys->len)
        return -1;
    BRANCH(xs->len > ys->len)
        return 1;
    DEFAULT
        return (r = memcmp(xs->buf, ys->buf, xs->len)) > 0
            ? 1 : r < 0
            ? -1 : 0;
    EMATCH
}

static int
strGrow(SorString *xs)
{
    int64   cap;
    char    *buf;

    BMATCH(xs->cap == 0)
        cap = 1;
    BRANCH(xs->cap < 1024)
        cap = xs->cap * 2;
    DEFAULT
        cap = xs->cap + xs->cap / 4;
    EMATCH
    if(!(buf = realloc(xs->buf, cap)))
        return -1;
    xs->buf = buf;
    xs->cap = cap;
    return 0;
}

static int
strAppendString(SorString *xs, const char *s, int64 n)
{
    while(xs->len + n >= xs->cap){
        if(strGrow(xs) != 0)
            return -1;
    }
    memmove(xs->buf + xs->len, s, n);
    xs->len = xs->len + n;
    return 0;
}
