#include "test_neh.h"

#include "../neh.h"
#include "../solution.h"
#include "../input.h"
#include <stdlib.h>
#include <stdio.h>



void test_neh()
{
    char filename[1024];
    instance data;
    solution sol;
    unsigned int m, n, * job_to_group, boucle, nb_groups, id_group, index, * date;

    puts("Nom du fichier contenant l'instance de test ?");
    scanf("%s", filename);
    if(read_instance(&data, filename) != INPUT_SUCCESS)
    {
        puts("Erreur lors de la lecture du fichier");
    }
    else
    {
        m = instance_get_nb_machines(data);
        n = instance_get_nb_jobs(data);
        job_to_group = (unsigned int *) calloc(n, sizeof(unsigned int));
        for(boucle = 0; boucle < n; ++boucle)
        {
            printf("Groupe du job numéro %d ?\t", boucle + 1);
            scanf("%d", &(job_to_group[boucle]));
        }
        sol = solution_new(data, job_to_group);

        nb_groups = solution_get_nb_groups(sol);
        date = (unsigned int *) calloc(m, sizeof(unsigned int));
        for(id_group = 1; id_group <= nb_groups; ++id_group)
        {
            for(boucle = 1; boucle <= m; ++boucle)
            {
                flowshop_set_availability_date(solution_get_flowshop_for_group(sol, id_group), boucle, date[boucle - 1]);
            }
            neh(solution_get_flowshop_for_group(sol, id_group), solution_get_jobs_in_group(sol, id_group));
            for(boucle = 1; boucle <= m; ++boucle)
            {
                date[boucle - 1] = flowshop_get_date(solution_get_flowshop_for_group(sol, id_group), boucle, solution_get_nb_elements_in_group(sol, id_group));
            }
        }
        for(id_group = 1; id_group <= nb_groups; ++id_group)
        {
            printf("Groupe %d : ", id_group);
            for(index = 1; index <= solution_get_nb_elements_in_group(sol, id_group); ++index)
            {
                printf("%d, ", job_get_id(solution_get_jobs_in_group(sol, id_group)[index - 1]));
            }
            printf("durée de fabrication = %d\n", flowshop_get_duration(solution_get_flowshop_for_group(sol, id_group)));
        }
        for(boucle = 1; boucle <= m; ++boucle)
        {
            printf("Machine %d :", boucle);
            for(id_group = 1; id_group <= nb_groups; ++id_group)
            {
                printf("\t(%d)", flowshop_get_availability_date(solution_get_flowshop_for_group(sol, id_group), boucle));
                for(index = 1; index <= solution_get_nb_elements_in_group(sol, id_group); ++index)
                {
                    printf("\t%d", flowshop_get_date(solution_get_flowshop_for_group(sol, id_group), boucle, index));
                }
                printf("\t;");
            }
            puts("");
        }

        solution_delete(sol);
        instance_delete(data);
        free(job_to_group);
        free(date);
    }
}
