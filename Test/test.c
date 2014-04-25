#include "test.h"

#include <stdio.h>

void test(void (* test_function) (), const char * test_name)
{
    printf("\n********** Debut du test : %s **********\n", test_name);
    test_function();
    printf("*********** Fin du test : %s ***********\n\n", test_name);
}
