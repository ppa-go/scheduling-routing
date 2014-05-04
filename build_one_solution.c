#include "build_one_solution.h"

#include "neh.h"
#include "nearest_neighboor.h"
#include <stdlib.h>



/*! Cette macro retourne le maximum entre @c x et @c y. */
#define MAX(x,y) ( (x) >= (y) ? (x) : (y) )



void build_one_solution(solution sol)
{
    const unsigned int nb_groups = solution_get_nb_groups(sol),
                       nb_machines = instance_get_nb_machines(solution_get_data(sol));
    unsigned int * processing_dates = (unsigned int *) calloc(nb_machines, sizeof(unsigned int)),
                 travelling_date = 0,
                 id_group,
                 id_machine;
    flowshop fs;
    job * jobs;
    routing r;
    site * sites;

    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        fs = solution_get_flowshop_for_group(sol, id_group);
        jobs = solution_get_jobs_in_group(sol, id_group);
        r = solution_get_routing_for_group(sol, id_group);
        sites = solution_get_sites_in_group(sol, id_group);

        /* Construction du flowshop, avec prise en compte des dates de fin du flowshop précédent */
        for(id_machine = 1; id_machine <= nb_machines; ++id_machine)
        {
            flowshop_set_availability_date(fs, id_machine, processing_dates[id_machine - 1]);
        }
        neh(fs, jobs);

        /* Construction du routing, avec prise en compte des dates de fin du flowshop et de la date de fin du routing précédent */
        routing_set_departure_date(r, MAX(flowshop_get_date(fs, nb_machines, flowshop_get_nb_jobs(fs)), travelling_date));
        nearest_neighboor(r, sites);

        /* Mise à jour des dates de fin pour le groupe suivant */
        for(id_machine = 1; id_machine <= nb_machines; ++id_machine)
        {
            processing_dates[id_machine - 1] = flowshop_get_availability_date(fs, id_machine);
        }
        travelling_date = routing_get_arrival_date(r);
    }
    free(processing_dates);
}
