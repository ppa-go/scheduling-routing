#include "test.h"

#include <stdlib.h>
#include <stdio.h>

#include "test_conversion_job_void_ptr.h"
#include "test_group.h"
#include "test_read_instance.h"
#include "test_nearest_neighboor.h"
#include "test_neh.h"
#include "test_find_first_group.h"
#include "test_mutation.h"



static void test(void (* test_function) (), const char * test_name)
{
    printf("\n********** Debut du test : %s **********\n", test_name);
    test_function();
    printf("**********  Fin du test : %s  **********\n\n", test_name);
}



void main_test()
{
    // test(test_conversion_job_void_ptr, "conversion job void *");
    // test(test_group, "group");
    // test(test_read_instance, "read instance");
    // test(test_nearest_neighboor, "nearest neighboor");
    // test(test_neh, "NEH");
    // test(test_find_first_group, "find first group");
    test(test_mutation, "mutation");

    exit(EXIT_SUCCESS);
}
