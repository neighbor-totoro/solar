#ifndef __SOR_BUFFER_H__
#define __SOR_BUFFER_H__

#include    "file/sor_file.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * buffer提供一个字节数组的缓存，支持reader和writer接口
 * buffer的大部分操作需要调用SorBufToStr转换为SorString来完成
 */
typedef struct SorBuffer SorBuffer;
struct SorBuffer{
    int64   len;
    int64   cap;
    char    *buf;
    int64   off;
    SorReader   rn;
    SorWriter   wn;
};

#define SorBufToStr(bp)     ((SorString *)(bp))

#define SorBufToReader(bp)  (&(bp)->rn)
#define SorBufToWriter(bp)  (&(bp)->wn)

SorBuffer   *SorBufNew(void);
int     SorBufDel(SorBuffer *);

#ifdef __cplusplus
};
#endif

#endif
