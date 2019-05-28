#include    <check.h>
#include    "adt/string/sor_string.h"

START_TEST
(test_string)
{
    char   c;
    SorString *xs, *ys;

    xs = SorStrNew(NULL, -1);
    for(c = 'a'; c <= 'z'; c++)
        SorStrAppend(xs, c);
    ys = SorStrNewLiteral("abcdefghijklmnopqrstuvwxyz");
    fail_unless(SorStrCmp(xs, ys) == 0);
    SorStrDel(xs);
    SorStrDel(ys);
}
END_TEST

void tcase_add_strings(Suite *s)
{
    TCase *tc_s;
    tc_s = tcase_create("string");
    tcase_add_test(tc_s, test_string);
    suite_add_tcase(s, tc_s);
}
