#include "unit_test/adt/test_adt.h"
#include <stdlib.h>

int main()
{
    if (test_adt())
        goto err;

    return EXIT_SUCCESS;
err:
    return EXIT_FAILURE;
}
