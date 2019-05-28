#ifndef __UNIT_TEST_ADT_H__
#define __UNIT_TEST_ADT_H__

#include    <check.h>

#ifdef __cplusplus
extern "C" {
#endif

void tcase_add_strings(Suite *s);

int test_adt();

#ifdef __cplusplus
};
#endif
#endif
