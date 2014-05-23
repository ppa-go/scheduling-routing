#include "../headers/job.h"

#include <stdlib.h>



/*! Structure représentant un job
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref job.h.
 * @see job.h
 */
struct job
{
    unsigned int id; //!< L'ID du job
    unsigned int nb_machines; //!< Le nombre de machines dans l'instance à laquelle le job appartient
    unsigned int * processing_times; //!< Un tableau dynamique dans lequel sont stockées les durées de fabrication
    unsigned int sum_processing_times; //!< La somme des durées de fabrication, mise à jour à chaque appel de la fonction @ref job_set_processing_time()
    unsigned int due_date; //!< La date due du job
    unsigned int id_delivery_site; //!< L'ID du site de livraison du job
};



job job_new(unsigned int id, unsigned int nb_machines)
{
    job new_job = (job) malloc(sizeof(struct job));

    new_job->id = id;
    new_job->nb_machines = nb_machines;
    new_job->processing_times = (unsigned int *) calloc(nb_machines, sizeof(unsigned int));
    new_job->sum_processing_times = 0;
    new_job->due_date = JOB_DEFAULT_VALUE_DUE_DATE;
    new_job->id_delivery_site = JOB_DEFAULT_VALUE_ID_DELIVERY_SITE;

    return new_job;
}

void job_delete(job __job)
{
    free(__job->processing_times);

    free(__job);
}



unsigned int job_get_id(job __job)
{
    return __job->id;
}

unsigned int job_get_nb_machines(job __job)
{
    return __job->nb_machines;
}



void job_set_processing_time(job __job, unsigned int id_machine, unsigned int value)
{
    --id_machine;
    __job->sum_processing_times -= __job->processing_times[id_machine];
    __job->processing_times[id_machine] = value;
    __job->sum_processing_times += __job->processing_times[id_machine];
}

void job_set_due_date(job __job, unsigned int value)
{
    __job->due_date = value;
}

void job_set_id_delivery_site(job __job, unsigned int value)
{
    __job->id_delivery_site = value;
}



unsigned int job_get_processing_time(job __job, unsigned int id_machine)
{
    return __job->processing_times[--id_machine];
}

unsigned int job_get_sum_processing_times(job __job)
{
    return __job->sum_processing_times;
}

unsigned int job_get_due_date(job __job)
{
    return __job->due_date;
}

unsigned int job_get_id_delivery_site(job __job)
{
    return __job->id_delivery_site;
}
