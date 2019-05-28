#include    <stdlib.h>
#include    "encoding/base64/sor_base64.h"

static void     base64EncoderReset(SorEncoder *);
static SorString    *base64EncoderEncode(SorEncoder *);
static int64    base64EncoderWrite(SorEncoder *, SorString *);

SorEncoder  *
SorBase64NewEncoder(void)
{
    SorBase64Encoder    *e;

    if(!(e = calloc(1, sizeof(*e))))
        return NULL;
    if(!(e->src = SorStrNew(NULL, 0)))
        goto ERR;
    e->encode = BASE64_STD;
    e->n.reset = base64EncoderReset;
    e->n.write = base64EncoderWrite;
    e->n.encode = base64EncoderEncode;
    return &e->n;
ERR:
    if(e)
        SorBase64DelEncoder(&e->n);
    return NULL;
}

int
SorBase64DelEncoder(SorEncoder *enc)
{
    SorBase64Encoder    *e;

    e = data_offset2(enc, SorBase64Encoder, n);
    if(e->src)
        SorStrDel(e->src);
    free(e);
    return 0;
}

SorEncoder  *
SorBase64NewUrlEncoder(void)
{
    SorBase64Encoder    *e;

    if(!(e = calloc(1, sizeof(*e))))
        return NULL;
    if(!(e->src = SorStrNew(NULL, 0)))
        goto ERR;
    e->encode = BASE64_URL;
    e->n.reset = base64EncoderReset;
    e->n.write = base64EncoderWrite;
    e->n.encode = base64EncoderEncode;
    return &e->n;
ERR:
    if(e)
        SorBase64DelEncoder(&e->n);
    return NULL;
}

int
SorBase64DelUrlEncoder(SorEncoder *enc)
{
    SorBase64Encoder    *e;

    e = data_offset2(enc, SorBase64Encoder, n);
    if(e->src)
        SorStrDel(e->src);
    free(e);
    return 0;
}

SorDecoder  *
SorBase64NewDecoder(void)
{
    return NULL;
}

int
SorBase64DelDecoder(SorEncoder *dec)
{
    return 0;
}

SorDecoder  *
SorBase64NewUrlDecoder(void)
{
    return NULL;
}

int
SorBase64DelUrlDecoder(SorEncoder *dec)
{
    return 0;
}

static void
base64EncoderReset(SorEncoder *enc)
{
    SorBase64Encoder    *e;

    e = data_offset2(enc, SorBase64Encoder, n);
    SorStrReset(e->src);
}

static int64
base64EncoderWrite(SorEncoder *enc, SorString *data)
{
    SorBase64Encoder    *e;

    e = data_offset2(enc, SorBase64Encoder, n);
    BMATCH(SorStrJoin(e->src, data) == -1)
        return -1;
    DEFAULT
        return SorStrLen(data);
    EMATCH
}

static SorString    *
base64EncoderEncode(SorEncoder *enc)
{
    uint32  v;
    char    *p, *q;
    int64   i, j, k;
    SorString   *dst;
    SorBase64Encoder    *e;

    e = data_offset2(enc, SorBase64Encoder, n);
    if(!(dst = SorStrNew(NULL, (SorStrLen(e->src) + 2) / 3 * 4)))
        return NULL;
    k = 0
    q = SorStrStr(dst);
    p = SorStrStr(e->src);
    for(i = 0, j = SorStrLen(e->src); j - i >= 3; i += 3){
        v = (uint32)p[i+0] << 16 | (uint32)p[i+1] << 8 | (uint32)p[i+2];
        p[k++] = e->encode[v>>18&0x3F]; p[k++] = e->encode[v>>12&0x3F];
        p[k++] = e->encode[v>>6&0x3F]; p[k++] = e->encode[v&0x3F];
    }
    if(i == j)
        return dst;
    v = (uint32)p[i+0] << 16;
    if((j - i) == 2)
        v |= (uint32)p[i+1] << 8;
    p[k++] = e->encode[v>>18&0x3F]; p[k++] = e->encode[v>>12&0x3F];
    BMATCH(j-i == 2)
        p[k++] = e->encode[v>>6&0x3F];
    DEFAULT
        p[k++] = '=';
    EMATCH
    p[k++] = '=';
    return dst;
ERR:
    if(dst)
        SorStrDel(dst);
    return NULL;
}
