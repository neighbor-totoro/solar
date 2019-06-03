#include    <stdlib.h>
#include    "unit_test/adt/test_adt.h"
#include    "unit_test/encoding/test_sor_encoding.h"

int
main(int argc, char *argv[])
{
    if(test_adt())
        goto err;
    if(TestSorEncoding())
        goto err;
    return EXIT_SUCCESS;
err:
    return EXIT_FAILURE;
}
