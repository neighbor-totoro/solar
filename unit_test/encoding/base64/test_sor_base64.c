#include    <check.h>
#include    <stdarg.h>
#include    "encoding/base64/sor_base64.h"

static void EncodeTest(SorEncoder *e, SorString *target, SorString *in, ...)
{
    SorString *arg;
    va_list args;
    va_start(args, in);
    e->write(e, in);
    for (;;) {
        arg = va_arg(args, SorString *);
        if (!arg)
            break;
        e->write(e, arg);
    }
    va_end(args);
    SorString *result = e->encode(e);
    fail_unless(SorStrCmp(result, target) == 0);
    SorStrDel(result);
}

static void DecodeTest(SorDecoder *d, SorString *target, SorString *in, ...)
{
    SorString *arg;
    va_list args;
    va_start(args, in);
    d->write(d, in);
    for (;;) {
        arg = va_arg(args, SorString *);
        if (!arg)
            break;
        d->write(d, arg);
    }
    va_end(args);
    SorString *result = d->decode(d);
    fail_unless(SorStrCmp(result, target) == 0);
    SorStrDel(result);
}

START_TEST
(TestBase64Encode)
{
    SorEncoder *e = SorBase64NewEncoder();
    SorString *s1 = SorStrNewLiteral("carpe ");
    SorString *s2 = SorStrNewLiteral("diem");
    SorString *target = SorStrNewLiteral("Y2FycGUgZGllbQ==");

    EncodeTest(e, target, s1, s2, NULL);

    SorStrDel(s1);
    SorStrDel(s2);
    SorStrDel(target);
    SorBase64DelEncoder(e);
}
END_TEST

START_TEST
(TestBase64Decode)
{
    SorDecoder *d = SorBase64NewDecoder();
    SorString *in = SorStrNewLiteral("Y2FycGUgZGllbQ==");
    SorString *target = SorStrNewLiteral("carpe diem");

    DecodeTest(d, target, in, NULL);

    SorStrDel(in);
    SorStrDel(target);
    SorBase64DelDecoder(d);
}
END_TEST

START_TEST
(TestBase64UrlEncode)
{
    SorEncoder *e = SorBase64NewUrlEncoder();
    SorString *s1 = SorStrNewLiteral("carpe ");
    SorString *s2 = SorStrNewLiteral("diem");
    SorString *target = SorStrNewLiteral("Y2FycGUgZGllbQ");

    EncodeTest(e, target, s1, s2, NULL);

    SorStrDel(s1);
    SorStrDel(s2);
    SorStrDel(target);
    SorBase64DelEncoder(e);
}
END_TEST

START_TEST
(TestBase64UrlDecode)
{
    SorDecoder *d = SorBase64NewUrlDecoder();
    SorString *in = SorStrNewLiteral("Y2FycGUgZGllbQ==");
    SorString *target = SorStrNewLiteral("carpe diem");

    DecodeTest(d, target, in, NULL);

    SorStrDel(in);
    SorStrDel(target);
    SorBase64DelDecoder(d);
}
END_TEST

void TcaseAddSorBase64(Suite *s)
{
    TCase *tc_s;
    tc_s = tcase_create("string");
    tcase_add_test(tc_s, TestBase64Encode);
    tcase_add_test(tc_s, TestBase64Decode);
    tcase_add_test(tc_s, TestBase64UrlEncode);
    tcase_add_test(tc_s, TestBase64UrlDecode);
    suite_add_tcase(s, tc_s);
}
