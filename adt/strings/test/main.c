#include    "strings.h"

int
main(int argc, char *argv[])
{
    char    c;
    String  *xs, *ys;

    xs = string_new(NULL, -1);
    for(c = 'a'; c <= 'z'; c++)
        string_append(xs, c);
    string_append(xs, '\0');
    ys = string_dup(xs, 10, -1);
    printf("%s\n", xs->buf);
    printf("%s\n", ys->buf);
    string_delete(xs);
    string_delete(ys);
    return 0;
}
