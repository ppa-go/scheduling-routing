#include "solution.h"

#include "group.h"
#include <stdlib.h>



/*! Structure représentant une solution
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref solution.h.
 * @see solution.h
 */
struct solution
{
    instance data; //!< L'instance à laquelle la solution est associée
    group groups; //!< Un objet de type @ref group qui indique quel job appartient à quel groupe
    job ** jobs_per_group; //!< Un tableau dynamique contenant des tableaux dynamiques de jobs (un tableau de jobs par groupe)
    flowshop * flowshops; //!< Un tableau dynamique de flowshops (un flowshop par groupe)
    site ** sites_per_group; //!< Un tableau dynamique contenant des tableaux dynamiques de sites (un tableau de sites par groupe)
    routing * routings; //!< Un tableau dynamique de routings (un routing par groupe)
};



solution solution_new(instance data, unsigned int * job_to_group)
{
    solution new_solution = (solution) malloc(sizeof(struct solution));
    const unsigned int nb_machines = instance_get_nb_machines(data),
                       nb_jobs = instance_get_nb_jobs(data);
    site factory = instance_extract_site(data, SITE_ID_FACTORY);
    group groups = group_new(nb_jobs, job_to_group);
    const unsigned int nb_groups = group_get_nb_groups(groups);
    unsigned int id_group, nb_elements_in_group, index, id_element;

    new_solution->data = data;
    new_solution->groups = groups;
    new_solution->jobs_per_group = (job **) malloc(nb_groups * sizeof(job *));
    new_solution->flowshops = (flowshop *) malloc(nb_groups * sizeof(flowshop));
    new_solution->sites_per_group = (site **) malloc(nb_groups * sizeof(site *));
    new_solution->routings = (routing *) malloc(nb_groups * sizeof(routing));

    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = group_get_nb_elements_in_group(groups, id_group);

        new_solution->jobs_per_group[id_group - 1] = (job *) malloc(nb_elements_in_group * sizeof(job));
        new_solution->sites_per_group[id_group - 1] = (site *) malloc(nb_elements_in_group * sizeof(site));
        new_solution->flowshops[id_group - 1] = flowshop_new(nb_machines, nb_elements_in_group);
        new_solution->routings[id_group - 1] = routing_new(nb_elements_in_group, factory);

        for(index = 1; index <= nb_elements_in_group; ++index)
        {
            id_element = group_get_element_in_group(groups, id_group, index);
            new_solution->jobs_per_group[id_group - 1][index - 1] = instance_extract_job(data, id_element);
            new_solution->sites_per_group[id_group - 1][index - 1] = instance_extract_site(data, id_element);
        }
    }

    return new_solution;
}

void solution_delete(solution __solution)
{
    const unsigned int nb_groups = group_get_nb_groups(__solution->groups);
    unsigned int id_group;

    for(id_group = 0; id_group < nb_groups; ++id_group)
    {
        free(__solution->jobs_per_group[id_group]);
        free(__solution->sites_per_group[id_group]);
        flowshop_delete(__solution->flowshops[id_group]);
        routing_delete(__solution->routings[id_group]);
    }

    group_delete(__solution->groups);
    free(__solution->jobs_per_group);
    free(__solution->flowshops);
    free(__solution->sites_per_group);
    free(__solution->routings);

    free(__solution);
}



instance solution_get_data(solution __solution)
{
    return __solution->data;
}



unsigned int solution_get_nb_groups(solution __solution)
{
    return group_get_nb_groups(__solution->groups);
}

unsigned int solution_get_nb_elements_in_group(solution __solution, unsigned int id_group)
{
    return group_get_nb_elements_in_group(__solution->groups, id_group);
}



job * solution_get_jobs_in_group(solution __solution, unsigned int id_group)
{
    return __solution->jobs_per_group[--id_group];
}

flowshop solution_get_flowshop_for_group(solution __solution, unsigned int id_group)
{
    return __solution->flowshops[--id_group];
}



site * solution_get_sites_in_group(solution __solution, unsigned int id_group)
{
    return __solution->sites_per_group[--id_group];
}

routing solution_get_routing_for_group(solution __solution, unsigned int id_group)
{
    return __solution->routings[--id_group];
}



unsigned int solution_get_tardiness(solution __solution)
{
    const unsigned int nb_groups = group_get_nb_groups(__solution->groups);
    unsigned int nb_elements_in_group,
                 id_group,
                 job_position,
                 site_position,
                 due_date,
                 delivery_date,
                 tardiness = 0;

    /* Pour chaque groupe */
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = group_get_nb_elements_in_group(__solution->groups, id_group);
        /* Pour chaque job dans le groupe */
        for(job_position = 1; job_position <= nb_elements_in_group; ++job_position)
        {
            /* Retrouver la position du site de livraison pour le routing */
            for(site_position = 1; site_position <= nb_elements_in_group; ++site_position)
            {
                if(site_get_id(__solution->sites_per_group[id_group - 1][site_position - 1]) == job_get_id_delivery_site(__solution->jobs_per_group[id_group - 1][job_position - 1]))
                {
                    break;
                }
            }
            /* Mettre à jour la somme des retards */
            due_date = job_get_due_date(__solution->jobs_per_group[id_group - 1][job_position - 1]);
            delivery_date = routing_get_delivery_date(__solution->routings[id_group - 1], site_position);
            if(delivery_date > due_date)
            {
                tardiness += delivery_date - due_date;
            }
        }
    }

    return tardiness;
}
