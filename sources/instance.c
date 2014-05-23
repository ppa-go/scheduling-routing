#include "../headers/instance.h"

#include <stdlib.h>



/*! Structure représentant une instance
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref instance.h.
 * @see instance.h
 */
struct instance
{
    unsigned int nb_machines; //!< Le nombre de machines de l'instance
    unsigned int nb_jobs; //!< Le nombre de jobs de l'instance
    unsigned int nb_sites; //!< Le nombre de sites de l'instance
    job * jobs; //!< Un tableau dynamique dans lequel sont stockés les jobs
    site * sites; //!< Un tableau dynamique dans lequel sont stockés les sites
};



instance instance_new(unsigned int nb_machines, unsigned int nb_jobs, unsigned int nb_sites)
{
    instance new_instance = (instance) malloc(sizeof(struct instance));
    unsigned int id_job, id_site;

    new_instance->nb_machines = nb_machines;
    new_instance->nb_jobs = nb_jobs;
    new_instance->nb_sites = nb_sites;
    new_instance->jobs = (job *) malloc(nb_jobs * sizeof(job));
    new_instance->sites = (site *) malloc((nb_sites + 1) * sizeof(site));

    for(id_job = 1; id_job <= nb_jobs; ++id_job)
    {
        new_instance->jobs[id_job - 1] = job_new(id_job, nb_machines);
    }
    for(id_site = 0; id_site <= nb_sites; ++id_site)
    {
        new_instance->sites[id_site] = site_new(id_site, nb_sites);
    }

    return new_instance;
}

void instance_delete(instance __instance)
{
    unsigned int id_job, id_site;

    for(id_job = 0; id_job < __instance->nb_jobs; ++id_job)
    {
        job_delete(__instance->jobs[id_job]);
    }
    for(id_site = 0; id_site <= __instance->nb_sites; ++id_site)
    {
        site_delete(__instance->sites[id_site]);
    }

    free(__instance->jobs);
    free(__instance->sites);

    free(__instance);
}



unsigned int instance_get_nb_machines(instance __instance)
{
    return __instance->nb_machines;
}

unsigned int instance_get_nb_jobs(instance __instance)
{
    return __instance->nb_jobs;
}

unsigned int instance_get_nb_sites(instance __instance)
{
    return __instance->nb_sites;
}



job instance_extract_job(instance __instance, unsigned int id_job)
{
    return __instance->jobs[--id_job];
}

site instance_extract_site(instance __instance, unsigned int id_site)
{
    return __instance->sites[id_site];
}



void instance_set_processing_time(instance __instance, unsigned int id_machine, unsigned int id_job, unsigned int value)
{
    job_set_processing_time(__instance->jobs[--id_job], id_machine, value);
}

void instance_set_due_date(instance __instance, unsigned int id_job, unsigned int value)
{
    job_set_due_date(__instance->jobs[--id_job], value);
}

void instance_set_id_delivery_site(instance __instance, unsigned int id_job, unsigned int value)
{
    job_set_id_delivery_site(__instance->jobs[--id_job], value);
}



unsigned int instance_get_processing_time(instance __instance, unsigned int id_machine, unsigned int id_job)
{
    return job_get_processing_time(__instance->jobs[--id_job], id_machine);
}

unsigned int instance_get_sum_processing_times(instance __instance, unsigned int id_job)
{
    return job_get_sum_processing_times(__instance->jobs[--id_job]);
}

unsigned int instance_get_due_date(instance __instance, unsigned int id_job)
{
    return job_get_due_date(__instance->jobs[--id_job]);
}

unsigned int instance_get_id_delivery_site(instance __instance, unsigned int id_job)
{
    return job_get_id_delivery_site(__instance->jobs[--id_job]);
}



void instance_set_travelling_time(instance __instance, unsigned int id_first_site, unsigned int id_second_site, unsigned int value)
{
    site_set_travelling_time(__instance->sites[id_first_site], id_second_site, value);
}



unsigned int instance_get_travelling_time(instance __instance, unsigned int id_first_site, unsigned int id_second_site)
{
    return site_get_travelling_time(__instance->sites[id_first_site], id_second_site);
}
