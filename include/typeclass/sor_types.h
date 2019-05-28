#ifndef __SOR_TYPES_H__
#define __SOR_TYPES_H__

#include    <stdio.h>
#include    <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE   (!TRUE)
#endif

#ifndef MAX
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

#define MIN_INT8    INT8_MIN
#define MIN_INT16   INT16_MIN
#define MIN_INT32   INT32_MIN
#define MIN_INT64   INT64_MIN

#define MAX_INT8    INT8_MAX
#define MAX_INT16   INT16_MAX
#define MAX_INT32   INT32_MAX
#define MAX_INT64   INT64_MAX

#define MAX_UINT8   UINT8_MAX
#define MAX_UINT16  UINT16_MAX
#define MAX_UINT32  UINT32_MAX
#define MAX_UINT64  UINT64_MAX

#define MAX_FLOAT32     3.40282346638528859811704183484516925440e+38
#define MAX_FLOAT64     1.797693134862315708145274237317043567981e+308

typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;

typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

typedef float       float32;
typedef double      float64;

typedef intptr_t    intptr;
typedef uintptr_t   uintptr;

typedef uint8       bool;

enum{true = 1, false = 0};

#ifdef __cplusplus
};
#endif

#endif
