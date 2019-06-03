#include    <stdlib.h>
#include    <string.h>
#include    "typeclass/sor_sugar.h"
#include    "adt/buffer/sor_buffer.h"

static int64    sorBufRead(SorReader *, SorString *);
static int64    sorBufWrite(SorWriter *, SorString *);

SorBuffer   *
SorBufNew(void)
{
    SorBuffer   *bp;

    if(!(bp = calloc(1, sizeof(*bp))))
        return NULL;
    bp->rn.read = sorBufRead;
    bp->wn.write = sorBufWrite;
    return bp;
}

int
SorBufDel(SorBuffer *bp)
{
    if(bp->buf)
        free(bp->buf);
    free(bp);
    return 0;
}

static int64
sorBufRead(SorReader *sr, SorString *xs)
{
    int64   n;
    SorBuffer   *bp;

    bp = data_offset2(sr, SorBuffer, rn);
    if(bp->off == bp->len) // end of file
        return EOF;
    n = SorStrLen(xs) < bp->len - bp->off ? SorStrLen(xs) : bp->len - bp->off;
    memmove(SorStrStr(xs), bp->buf + bp->off, n);
    return n;
}

static int64
sorBufWrite(SorWriter *sw, SorString *xs)
{
    SorBuffer   *bp;

    bp = data_offset2(sw, SorBuffer, wn);
    if(SorStrJoin(SorBufToStr(bp), xs) == -1)
        return EOF;
    return SorStrLen(xs);
}
