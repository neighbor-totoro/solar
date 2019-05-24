#include    "sugar.h"
#include    "strings.h"
#include    <stdlib.h>
#include    <string.h>

static int  string_grow(String *xs);
static int  string_append_string(String *xs, const char *s, int64 n);

String  *
string_new(const char *s, int64 n)
{
    String  *xs;

    if(!(xs = calloc(1, sizeof(*xs))))
        return NULL;
    if(n > 0 && string_append_string(xs, s, n) != 0)
        goto ERR;
    return xs;
ERR:
    if(xs)
        string_delete(xs);
    return NULL;
}

int
string_delete(String *xs)
{
    if(xs->buf)
        free(xs->buf);
    free(xs);
    return 0;
}

int
string_remove(String *xs, int64 idx)
{
    if(idx >= xs->len)
        return -1;
    xs->len--;
    memmove(xs->buf+idx, xs->buf+idx+1, (xs->len - idx));
    return 0;
}

int
string_append(String *xs, char c)
{
    if(xs->len == xs->cap && string_grow(xs) != 0)
        return -1;
    xs->buf[xs->len++] = c;
    return 0;
}

int
string_join(String *xs, String *ys)
{
    return string_append_string(xs, ys->buf, ys->len);
}

String  *
string_dup(String *xs, int64 x, int64 y)
{
    if(y > xs->len)
        return NULL;
    if(x <= 0)
        x = 0;
    if(y == -1)
        y = xs->len;
    if(x >= y)
        return NULL;
    return string_new(xs->buf + x, y - x);
}

int
string_compare(String *xs, String *ys)
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
string_grow(String *xs)
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
string_append_string(String *xs, const char *s, int64 n)
{
    while(xs->len + n >= xs->cap){
        if(string_grow(xs) != 0)
            return -1;
    }
    memmove(xs->buf + xs->len, s, n);
    xs->len = xs->len + n;
    return 0;
}
