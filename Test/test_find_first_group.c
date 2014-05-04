#include "test_find_first_group.h"

#include "../find_first_group.h"
#include "../input.h"
#include <stdlib.h>
#include <stdio.h>



void test_find_first_group()
{
    char filename[1024];
    instance data;
    unsigned int * job_to_group;
    unsigned int loop;

    puts("Nom du fichier contenant l'instance de test ?");
    scanf("%s", filename);
    if(read_instance(&data, filename) != INPUT_SUCCESS)
    {
        puts("Erreur lors de la lecture du fichier");
    }
    else
    {
        job_to_group = find_first_group(data);

        for(loop = 1; loop <= instance_get_nb_jobs(data); ++loop)
        {
            printf("Numéro de groupe du job %d :\t%d\n", loop, job_to_group[loop - 1]);
        }

        instance_delete(data);
        free(job_to_group);
    }
}
