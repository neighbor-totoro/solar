#include "adt/strings/strings.h"
#include <check.h>

START_TEST
(test_string)
{
    char   c;
    String *xs, *ys;

    xs = string_new(NULL, -1);
    for(c = 'a'; c <= 'z'; c++)
        string_append(xs, c);
    ys = string_new_literal("abcdefghijklmnopqrstuvwxyz");
    fail_unless(string_compare(xs, ys) == 0);
    string_delete(xs);
    string_delete(ys);
}
END_TEST

void tcase_add_strings(Suite *s)
{
    TCase *tc_s;
    tc_s = tcase_create("strings");
    tcase_add_test(tc_s, test_string);
    suite_add_tcase(s, tc_s);
}
