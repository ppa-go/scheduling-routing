#ifndef TEST_H
#define TEST_H

#include "test_conversion_job_void_ptr.h"
#include "test_group.h"

void test(void (* test_function) (), const char * test_name);

#endif // TEST_H
