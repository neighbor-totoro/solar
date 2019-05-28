#include    <stdlib.h>
#include    "unit_test/adt/test_adt.h"

int
main(int argc, char *argv[])
{
    if(test_adt())
        goto err;
    return EXIT_SUCCESS;
err:
    return EXIT_FAILURE;
}
