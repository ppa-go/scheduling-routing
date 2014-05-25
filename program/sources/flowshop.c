#include "../headers/flowshop.h"

#include <stdlib.h>



/*! Cette macro retourne le maximum entre @c x et @c y. */
#define MAX(x,y) ( (x) >= (y) ? (x) : (y) )



/*! Structure représentant un flowshop
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref flowshop.h.
 * @see flowshop.h
 */
struct flowshop
{
    unsigned int nb_machines; //!< Le nombre de machines dans l'instance à laquelle le flowshop est associé
    unsigned int nb_jobs; //!< Le nombre de jobs dans le groupe à ordonnancer
    unsigned int ** dates; //!< Un tableau dynamique contenant les dates de disponibilité au plus tôt, et les dates de fin de fabrication
    unsigned int current_position; //!< La position courante d'insertion de job
};



flowshop flowshop_new(unsigned int nb_machines, unsigned int nb_jobs)
{
    flowshop new_flowshop = (flowshop) malloc(sizeof(struct flowshop));
    unsigned int id_machine;

    new_flowshop->nb_machines = nb_machines;
    new_flowshop->nb_jobs = nb_jobs;
    new_flowshop->current_position = 1;
    new_flowshop->dates = (unsigned int **) malloc(nb_machines * sizeof(unsigned int *));

    for(id_machine = 0; id_machine < nb_machines; ++id_machine)
    {
        new_flowshop->dates[id_machine] = (unsigned int *) calloc(nb_jobs + 1, sizeof(unsigned int));
    }

    return new_flowshop;
}

void flowshop_delete(flowshop __flowshop)
{
    unsigned int id_machine;

    for(id_machine = 0; id_machine < __flowshop->nb_machines; ++id_machine)
    {
        free(__flowshop->dates[id_machine]);
    }

    free(__flowshop->dates);

    free(__flowshop);
}



unsigned int flowshop_get_nb_machines(flowshop __flowshop)
{
    return __flowshop->nb_machines;
}

unsigned int flowshop_get_nb_jobs(flowshop __flowshop)
{
    return __flowshop->nb_jobs;
}



void flowshop_set_availability_date(flowshop __flowshop, unsigned int id_machine, unsigned int value)
{
    __flowshop->dates[--id_machine][0] = value;
}

unsigned int flowshop_get_availability_date(flowshop __flowshop, unsigned int id_machine)
{
    return __flowshop->dates[--id_machine][0];
}



void flowshop_insert_job(flowshop __flowshop, job job_to_insert)
{
    const unsigned int m = flowshop_get_nb_machines(__flowshop);
    unsigned int i,
                 k = __flowshop->current_position,
                 ** c = __flowshop->dates;

    /* (i = 1 : machine M1)   C(1,k) = C(1,k-1) + p(1,k)
     * (C(1,0) = date de disponibilité au plus tôt de la machine M1)
     */
    i = 1;
    c[i - 1][k] = c[i - 1][k - 1] + job_get_processing_time(job_to_insert, i);

    /* Pour tout i = 2..m :   C(i,k) = max(C(i,k-1), C(i-1,k)) + p(i,k)
     * (C(i,0) = date de disponibilité au plus tôt de la machine Mi)
     */
    for(i = 2; i <= m; ++i)
    {
        c[i - 1][k] = MAX(c[i - 1][k - 1], c[i - 2][k]) + job_get_processing_time(job_to_insert, i);
    }

    /* Incrémentation de la position courante pour l'insertion d'un job */
    ++(__flowshop->current_position);
}



unsigned int flowshop_get_current_position(flowshop __flowshop)
{
    return __flowshop->current_position;
}



unsigned int flowshop_get_duration(flowshop __flowshop)
{
    return __flowshop->dates[__flowshop->nb_machines - 1][__flowshop->nb_jobs] - __flowshop->dates[0][0];
}



unsigned int flowshop_get_date(flowshop __flowshop, unsigned int id_machine, unsigned int position)
{
    return __flowshop->dates[--id_machine][position];
}
