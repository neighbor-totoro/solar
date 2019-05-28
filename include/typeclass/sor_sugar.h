#ifndef __SOR_SUGAR_H__
#define __SOR_SUGAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif

#define BMATCH(x)   if((x)){
#define BRANCH(x)   }else if((x)){
#define DEFAULT     }else{
#define EMATCH      }

#ifndef offsetof
#define offsetof(TYPE, MEMBER)    ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef data_offset2
#define data_offset2(q, type, link) (type*)((void*)((char*)q - offsetof(type, link)))
#endif

#ifdef __cplusplus
};
#endif

#endif
