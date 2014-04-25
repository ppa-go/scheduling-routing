#include "test_conversion_job_void_ptr.h"

#include "../job.h"
#include <stdio.h>

void test_conversion_job_void_ptr()
{
    const unsigned int m = 3, n = 5;
    job vect[n];
    unsigned int j, i;
    job * job_ptr;
    void ** void_ptr;
    int result = 1;

    for(j = 0; j < n; ++j)
    {
        vect[j] = job_new(j, m);
        for(i = 1; i <= m; ++i) job_set_processing_time(vect[j], i, j);
        job_set_due_date(vect[j], j);
        job_set_id_delivery_site(vect[j], j);
    }
    puts("Affectation OK");

    job_ptr = vect;
    void_ptr = (void **) vect;
    for(j = 0; j < n; ++j)
    {
        result = (job_ptr == (job *) void_ptr); if(!result) { printf("Bug 1 : j = %d\n", j); break; }
        result = (*job_ptr == (job) *void_ptr); if(!result) { printf("Bug 2 : j = %d\n", j); break; }
        result = (job_get_id(*job_ptr) == job_get_id((job) *void_ptr)); if(!result) { printf("Bug 3 : j = %d\n", j); break; }
        result = (job_get_due_date(*job_ptr) == job_get_due_date((job) *void_ptr)); if(!result) { printf("Bug 4 : j = %d\n", j); break; }
        result = (job_get_id_delivery_site(*job_ptr) == job_get_id_delivery_site((job) *void_ptr)); if(!result) { printf("Bug 5 : j = %d\n", j); break; }
        for(i = 1; i <= m; ++i)
        {
            result = (job_get_processing_time(*job_ptr, i) == job_get_processing_time((job) *void_ptr, i)); if(!result) { printf("Bug 6 : j = %d, i = %d\n", j, i); break; }
        }
        if(!result) break;
        ++job_ptr;
        ++void_ptr;
    }
    if(result) puts ("Youpi ! :-)");

    for(j = 0; j < n; ++j)
    {
        job_delete(vect[j]);
    }
}
