#ifndef __SOR_FILE_H__
#define __SOR_FILE_H___

#include    "adt/string/sor_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOR_CLOSER  \
    int     (*close)(SorCloser *);  \

#define SOR_READER  \
    int64   (*read)(SorReader *, SorString *);  \

#define SOR_WRITER  \
    int64   (*write)(SorWriter *, SorString *); \

#define SOR_SEEKER  \
    int64   (*seek)(SorSeeker *, int64, int8);  \

typedef struct SorCloser SorCloser;
struct SorCloser{
    SOR_CLOSER
};

typedef struct SorSeeker SorSeeker;
struct SorSeeker{
    SOR_SEEKER
};

typedef struct SorReader SorReader;
struct SorReader{
    SOR_READER
};

typedef struct SorWriter SorWriter;
struct SorWriter{
    SOR_WRITER
};

#ifdef __cplusplus
};
#endif

#endif
