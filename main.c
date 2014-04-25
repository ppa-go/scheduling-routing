#include <stdio.h>
#include <stdlib.h>

#include "Test/test.h"



int main()
{
    test(test_conversion_job_void_ptr, "conversion job void *");
    test(test_group, "group");

    // puts("Hello world !");
    return 0;
}
