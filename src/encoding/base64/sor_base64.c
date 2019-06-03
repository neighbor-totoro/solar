#include    <stdlib.h>
#include    "encoding/base64/sor_base64.h"

static void     base64EncoderReset(SorEncoder *);
static SorString    *base64EncoderEncode(SorEncoder *);
static int64    base64EncoderWrite(SorEncoder *, SorString *);

static void     base64DecoderReset(SorDecoder *);
static SorString    *base64DecoderDecode(SorDecoder *);
static int64    base64DecoderWrite(SorDecoder *, SorString *);

SorEncoder  *
SorBase64NewEncoder(void)
{
    SorBase64Encoder    *e;

    if(!(e = calloc(1, sizeof(*e))))
        return NULL;
    if(!(e->src = SorStrNew(NULL, 0)))
        goto ERR;
    e->flg = true;
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
    e->flg = false;
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
    int     i;
    SorBase64Decoder    *d;

    if(!(d = calloc(1, sizeof(*d))))
        return NULL;
    if(!(d->src = SorStrNew(NULL, 0)))
        goto ERR;
    for(i = 0; i < sizeof(BASE64_STD); i++)
        d->decode[BASE64_STD[i]] = (uint8)i;
    d->flg = true;
    d->n.reset = base64DecoderReset;
    d->n.write = base64DecoderWrite;
    d->n.decode = base64DecoderDecode;
    return &d->n;
ERR:
    if(d)
        SorBase64DelDecoder(&d->n);
    return NULL;
}

int
SorBase64DelDecoder(SorDecoder *dec)
{
    SorBase64Decoder    *d;

    d = data_offset2(dec, SorBase64Decoder, n);
    if(d->src)
        SorStrDel(d->src);
    free(d);
    return 0;
}

SorDecoder  *
SorBase64NewUrlDecoder(void)
{
    int     i;
    SorBase64Decoder    *d;

    if(!(d = calloc(1, sizeof(*d))))
        return NULL;
    if(!(d->src = SorStrNew(NULL, 0)))
        goto ERR;
    for(i = 0; i < sizeof(BASE64_STD); i++)
        d->decode[BASE64_URL[i]] = (uint8)i;
    d->flg = false;
    d->n.reset = base64DecoderReset;
    d->n.write = base64DecoderWrite;
    d->n.decode = base64DecoderDecode;
    return &d->n;
ERR:
    if(d)
        SorBase64DelDecoder(&d->n);
    return NULL;
}

int
SorBase64DelUrlDecoder(SorDecoder *dec)
{
    SorBase64Decoder    *d;

    d = data_offset2(dec, SorBase64Decoder, n);
    if(d->src)
        SorStrDel(d->src);
    free(d);
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
    k = 0;
    q = SorStrStr(dst);
    p = SorStrStr(e->src);
    for(i = 0, j = SorStrLen(e->src); j - i >= 3; i += 3){
        v = (uint32)p[i+0] << 16 | (uint32)p[i+1] << 8 | (uint32)p[i+2];
        q[k++] = e->encode[v>>18&0x3F]; q[k++] = e->encode[v>>12&0x3F];
        q[k++] = e->encode[v>>6&0x3F]; q[k++] = e->encode[v&0x3F];
    }
    if(i == j)
        return dst;
    v = (uint32)p[i+0] << 16;
    if((j - i) == 2)
        v |= (uint32)p[i+1] << 8;
    q[k++] = e->encode[v>>18&0x3F]; q[k++] = e->encode[v>>12&0x3F];
    BMATCH(j-i == 2)
        q[k++] = e->encode[v>>6&0x3F];
    DEFAULT
        if(e->flg)
            q[k++] = '=';
    EMATCH
    if(e->flg)
        q[k++] = '=';
    SorStrSetLen(dst, k);
    return dst;
ERR:
    if(dst)
        SorStrDel(dst);
    return NULL;
}

static void
base64DecoderReset(SorDecoder *dec)
{
    SorBase64Decoder    *d;

    d = data_offset2(dec, SorBase64Decoder, n);
    SorStrReset(d->src);
}

static int64
base64DecoderWrite(SorDecoder *dec, SorString *data)
{
    SorBase64Decoder    *d;

    d = data_offset2(dec, SorBase64Decoder, n);
    BMATCH(SorStrJoin(d->src, data) == -1)
        return -1;
    DEFAULT
        return SorStrLen(data);
    EMATCH
}

static SorString    *
base64DecoderDecode(SorDecoder *dec)
{
    uint32   v;
    int64 i, j, k;
    char    *p, *q;
    SorString   *dst;
    uint8   v0, v1, v2, v3;
    SorBase64Decoder    *d;

    d = data_offset2(dec, SorBase64Decoder, n);
    for(i = SorStrLen(d->src) % 4; i > 0 && i < 4; i++)
        SorStrAppend(d->src, 0);
    if(!(dst = SorStrNew(NULL, (SorStrLen(d->src) / 4 * 3))))
        return NULL;
    k = 0;
    q = SorStrStr(dst);
    p = SorStrStr(d->src);
    for(i = 0, j = SorStrLen(d->src); i < j; i += 4){
        if((v0 = d->decode[p[i+0]]) == 0xFF)
            goto ERR;
        if((v1 = d->decode[p[i+1]]) == 0xFF)
            goto ERR;
        if((v2 = d->decode[p[i+2]]) == 0xFF)
            goto ERR;
        if((v3 = d->decode[p[i+3]]) == 0xFF)
            goto ERR;
        v = v0 << 18 | v1 << 12 | v2 << 6 | v3;
        q[k++] = v >> 16 & 0xFF;
        q[k++] = v >> 8 & 0xFF;
        q[k++] = v & 0xFF;
    }
    if(p[j-1] == '=' || p[j-1] == 0)
        SorStrSetLen(dst, SorStrLen(dst) - 1);
    if(p[j-2] == '=' || p[j-1] == 0)
        SorStrSetLen(dst, SorStrLen(dst) - 1);
    return dst;
ERR:
    if(dst)
        SorStrDel(dst);
    return NULL;
}
