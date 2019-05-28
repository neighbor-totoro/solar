#include    <check.h>
#include    "unit_test/adt/test_adt.h"

int
test_adt()
{
    int     ret;
    SRunner *sr;
    Suite   *s;

    s = suite_create("adt");

    tcase_add_strings(s);

    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    ret = srunner_ntests_failed(sr);
    srunner_free(sr);

    return ret;
}
