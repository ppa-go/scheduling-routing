#include "test_nearest_neighboor.h"

#include "../nearest_neighboor.h"
#include "../solution.h"
#include "../input.h"
#include <stdlib.h>
#include <stdio.h>



void test_nearest_neighboor()
{
    char filename[1024];
    instance data;
    solution sol;
    unsigned int n, * job_to_group, boucle, nb_groups, id_group, index, date;

    puts("Nom du fichier contenant l'instance de test ?");
    scanf("%s", filename);
    if(read_instance(&data, filename) != INPUT_SUCCESS)
    {
        puts("Erreur lors de la lecture du fichier");
    }
    else
    {
        n = instance_get_nb_jobs(data);
        job_to_group = (unsigned int *) calloc(n, sizeof(unsigned int));
        for(boucle = 0; boucle < n; ++boucle)
        {
            printf("Groupe du job numéro %d ?\t", boucle + 1);
            scanf("%d", &(job_to_group[boucle]));
        };
        sol = solution_new(data, job_to_group);

        nb_groups = solution_get_nb_groups(sol);
        date = 0;
        for(id_group = 1; id_group <= nb_groups; ++id_group)
        {
            printf("Groupe %d : ", id_group);

            routing_set_departure_date(solution_get_routing_for_group(sol, id_group), date);
            printf("Usine (%d) -> ", routing_get_departure_date(solution_get_routing_for_group(sol, id_group)));

            nearest_neighboor(solution_get_routing_for_group(sol, id_group), solution_get_sites_in_group(sol, id_group));
            for(index = 1; index <= solution_get_nb_elements_in_group(sol, id_group); ++index)
            {
                printf("Site %d (%d) -> ", site_get_id(solution_get_sites_in_group(sol, id_group)[index - 1]), routing_get_delivery_date(solution_get_routing_for_group(sol, id_group), index));
            }
            printf("Usine (%d)\n", routing_get_arrival_date(solution_get_routing_for_group(sol, id_group)));

            date = routing_get_arrival_date(solution_get_routing_for_group(sol, id_group));
        }

        solution_delete(sol);
        instance_delete(data);
        free(job_to_group);
    }
}
