#include "../headers/calculate_tardiness.h"



/*! Cette macro retourne la valeur suivante : MAX(0, @em x - @em y). */
#define POSITIVE_DIFFERENCE(x,y) ( (x) <= (y) ? 0 : (x) - (y) )



unsigned int calculate_tardiness(flowshop fs, job * jobs, routing r, site * sites)
{
    const unsigned int nb_jobs = flowshop_get_nb_jobs(fs);
    unsigned int job_position,
                 site_position,
                 tardiness = 0;

    /* Pour chaque job dans le groupe */
    for(job_position = 1; job_position <= nb_jobs; ++job_position)
    {
        /* Retrouver la position du site de livraison pour le routing */
        for(site_position = 1; site_get_id(sites[site_position - 1]) != job_get_id_delivery_site(jobs[job_position - 1]); ++site_position);

        /* Mettre à jour la somme des retards */
        tardiness += POSITIVE_DIFFERENCE(routing_get_delivery_date(r, site_position), job_get_due_date(jobs[job_position - 1]));
    }

    return tardiness;
}
