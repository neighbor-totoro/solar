#ifndef __SOR_COMPRESS_H__
#define __SOR_COMPRESS_H___

#include    "file/sor_file.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_COMPRESSOR  \
    int     (*compress)(SorCompressor *);   \
    int64   (*write)(SorCompressor *, SorString *);     \

#define SOR_DECOMPRESSOR    \
    int     (*decompress)(SorDecompressor *);   \
    int64   (*write)(SorDecompressor *, SorString *);    \

typedef struct SorCompressor SorCompressor;
struct SorCompressor{
    SOR_COMPRESSOR
};

typedef struct SorDecompressor SorDecompressor;
struct SorDecompressor{
    SOR_DECOMPRESSOR
};

#ifdef __cplusplus
};
#endif

#endif
