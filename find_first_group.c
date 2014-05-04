#include "find_first_group.h"

#include "sort.h"
#include "neh.h"
#include "nearest_neighboor.h"
#include "calculate_tardiness.h"
#include <stdlib.h>



/*! Cette macro retourne le maximum entre @c x et @c y. */
#define MAX(x,y) ( (x) >= (y) ? (x) : (y) )



/*! Un comparateur de jobs
 * @param first_job Un job, casté en <tt>void *</tt>
 * @param second_job Un job, casté en <tt>void *</tt>
 * @return La valeur du booléen : <tt>job_get_due_date((job) first_job) < job_get_due_date((job) second_job)</tt>
 * @note Utilisé dans @ref sort(), ce comparateur permet de trier des jobs par date due croissante (tri @em EDD).
 */
static int job_comparator(void * first_job, void * second_job)
{
    return job_get_due_date((job) first_job) < job_get_due_date((job) second_job);
}



unsigned int * find_first_group(instance data)
{
    const unsigned int nb_jobs = instance_get_nb_jobs(data),
                       nb_machines = instance_get_nb_machines(data);
    unsigned int * job_to_group = (unsigned int *) malloc(nb_jobs * sizeof(unsigned int)),
                 * job_position_to_group = (unsigned int *) malloc(nb_jobs * sizeof(unsigned int)),
                 id_job,
                 job_position,
                 last_group,
                 nb_jobs_in_last_group,
                 first_position_in_last_group;
    job * jobs = (job *) malloc(nb_jobs * sizeof(unsigned int));
    site factory = instance_extract_site(data, SITE_ID_FACTORY),
         first_site_of_new_group;

    flowshop fs_last, fs_insert, fs_create;
    routing r_last, r_insert, r_create;
    unsigned int tardiness_last, tardiness_insert, tardiness_create;
    job * jobs_insert;
    site * sites_insert;
    unsigned int loop;

    /* Extraction des jobs */
    for(id_job = 1; id_job <= nb_jobs; ++id_job)
    {
        jobs[id_job - 1] = instance_extract_job(data, id_job);
    }

    /* 1. Tri EDD des jobs */
    sort(nb_jobs, (void **) jobs, job_comparator);

    /* 2. Création du premier groupe pour le premier job */
    job_position = 1;
    last_group = 1;
    job_position_to_group[job_position - 1] = last_group;
    first_position_in_last_group = job_position;

    fs_last = flowshop_new(nb_machines, 1);
    // for(loop = 1; loop <= nb_machines; ++loop) { flowshop_set_availability_date(fs_last, loop, 0); } // 0 est la valeur par défaut.
    flowshop_insert_job(fs_last, jobs[job_position - 1]);

    first_site_of_new_group = instance_extract_site(data, job_get_id_delivery_site(jobs[job_position - 1]));
    r_last = routing_new(1, factory);
    routing_set_departure_date(r_last, flowshop_get_date(fs_last, nb_machines, 1));
    routing_insert_site(r_last, first_site_of_new_group);

    tardiness_last = calculate_tardiness(fs_last, &(jobs[job_position - 1]), r_last, &first_site_of_new_group);

    /* 3. Simulations pour les autres jobs */
    for(job_position = 2; job_position <= nb_jobs; ++job_position)
    {
        nb_jobs_in_last_group = job_position - 1 - first_position_in_last_group + 1;

        /* 3.a Simulation de l'insertion dans le dernier groupe */
        jobs_insert = (job *) malloc((nb_jobs_in_last_group + 1) * sizeof(job));
        sites_insert = (site *) malloc((nb_jobs_in_last_group + 1) * sizeof(site));

        for(loop = 1; loop <= nb_jobs_in_last_group + 1; ++loop) { jobs_insert[loop - 1] = jobs[first_position_in_last_group - 1 + loop - 1]; }
        fs_insert = flowshop_new(nb_machines, nb_jobs_in_last_group + 1);
        for(loop = 1; loop <= nb_machines; ++loop) { flowshop_set_availability_date(fs_insert, loop, flowshop_get_availability_date(fs_last, loop)); }
        neh(fs_insert, jobs_insert);

        for(loop = 1; loop <= nb_jobs_in_last_group + 1; ++loop) { sites_insert[loop - 1] = instance_extract_site(data, job_get_id_delivery_site(jobs[first_position_in_last_group - 1 + loop - 1])); }
        r_insert = routing_new(nb_jobs_in_last_group, factory);
        routing_set_departure_date(r_insert, MAX(routing_get_departure_date(r_last), flowshop_get_date(fs_insert, nb_machines, nb_jobs_in_last_group + 1)));
        nearest_neighboor(r_insert, sites_insert);

        tardiness_insert = calculate_tardiness(fs_insert, jobs_insert, r_insert, sites_insert);

        free(jobs_insert);
        free(sites_insert);

        /* 3.b Simulation de la création d'un nouveau groupe */
        fs_create = flowshop_new(nb_machines, 1);
        for(loop = 1; loop <= nb_machines; ++loop) { flowshop_set_availability_date(fs_insert, loop, flowshop_get_date(fs_last, loop, flowshop_get_nb_jobs(fs_last))); }
        flowshop_insert_job(fs_create, jobs[job_position - 1]);

        first_site_of_new_group = instance_extract_site(data, job_get_id_delivery_site(jobs[job_position - 1]));
        r_create = routing_new(1, factory);
        routing_set_departure_date(r_insert, MAX(routing_get_arrival_date(r_last), flowshop_get_date(fs_create, nb_machines, 1)));
        routing_insert_site(r_create, first_site_of_new_group);

        tardiness_create = calculate_tardiness(fs_create, &(jobs[job_position - 1]), r_create, &first_site_of_new_group);

        /* 3.c Conservation de la meilleure simulation */
        flowshop_delete(fs_last);
        routing_delete(r_last);

        if(tardiness_insert <= tardiness_last + tardiness_create)
        {
            tardiness_last = tardiness_insert;
            job_position_to_group[job_position - 1] = last_group;

            fs_last = fs_insert;
            flowshop_delete(fs_create);

            r_last = r_insert;
            routing_delete(r_create);
        }
        else
        {
            tardiness_last = tardiness_create;
            job_position_to_group[job_position - 1] = ++last_group;
            first_position_in_last_group = job_position;

            flowshop_delete(fs_insert);
            fs_last = fs_create;

            routing_delete(r_insert);
            r_last = r_create;
        }
    }

    /* Conversion : 'position -> ID, groupe' vers 'ID -> groupe' */
    for(job_position = 1; job_position <= nb_jobs; ++job_position)
    {
        job_to_group[job_get_id(jobs[job_position - 1]) - 1] = job_position_to_group[job_position - 1];
    }

    /* Libération des ressources mémoire */
    free(job_position_to_group);
    free(jobs);
    flowshop_delete(fs_last);
    routing_delete(r_last);

    return job_to_group;
}
