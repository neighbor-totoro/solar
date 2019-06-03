#include    <check.h>
#include    "unit_test/encoding/test_sor_encoding.h"

int
TestSorEncoding()
{
    int     ret;
    SRunner *sr;
    Suite   *s;

    s = suite_create("encoding");

    TcaseAddSorBase64(s);

    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    ret = srunner_ntests_failed(sr);
    srunner_free(sr);

    return ret;
}
