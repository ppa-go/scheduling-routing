#include "../headers/neh.h"

#include "../headers/sort.h"



/*! Un comparateur de jobs
 * @param first_job Un job, casté en <tt>void *</tt>
 * @param second_job Un job, casté en <tt>void *</tt>
 * @return La valeur du booléen : <tt>job_get_sum_processing_times((job) first_job) > job_get_sum_processing_times((job) second_job)</tt>
 * @note Utilisé dans @ref sort(), ce comparateur permet de trier des jobs par somme des durées d'exécution décroissante.
 */
static int job_comparator(void * first_job, void * second_job)
{
    return job_get_sum_processing_times((job) first_job) > job_get_sum_processing_times((job) second_job);
}



static unsigned int calculate_duration(flowshop fs, job * jobs, job job_to_insert, const unsigned int insertion_position)
{
    const unsigned int n = flowshop_get_nb_jobs(fs) - 1;
    unsigned int position;

    for(position = 0; (position < insertion_position) && (position < n); ++position)
    {
        flowshop_insert_job(fs, jobs[position]);
    }
    flowshop_insert_job(fs, job_to_insert);
    for(/* position = insertion_position */; position < n; ++position)
    {
        flowshop_insert_job(fs, jobs[position]);
    }

    return flowshop_get_duration(fs);
}



void neh(flowshop fs, job * jobs)
{
    const unsigned int m = flowshop_get_nb_machines(fs),
                       n = flowshop_get_nb_jobs(fs);
    unsigned int id_machine,
                 sequence_length,
                 position, duration,
                 best_position, shortest_duration;
    job job_to_insert;
    flowshop temp;

    /* Etape 1 : Tri des jobs par sommes des durées de fabrication décroissantes */
    sort(n, (void **) jobs, job_comparator);

    /* Etape 2 : Constitution de la séquence */
    for(sequence_length = 2; sequence_length <= n; ++sequence_length)
    {
        job_to_insert = jobs[sequence_length - 1];

        /* Etape 2a : recherche de la meilleure position d'insertion */
        best_position = 0;

        temp = flowshop_new(m, sequence_length);
        for(id_machine = 1; id_machine <= m; ++id_machine)
        {
            flowshop_set_availability_date(temp, id_machine, flowshop_get_availability_date(fs, id_machine));
        }
        shortest_duration = calculate_duration(temp, jobs, job_to_insert, best_position);
        flowshop_delete(temp);

        for(position = 1; position < sequence_length; ++position)
        {
            temp = flowshop_new(m, sequence_length);
            for(id_machine = 1; id_machine <= m; ++id_machine)
            {
                flowshop_set_availability_date(temp, id_machine, flowshop_get_availability_date(fs, id_machine));
            }
            duration = calculate_duration(temp, jobs, job_to_insert, position);
            flowshop_delete(temp);

            if(duration < shortest_duration)
            {
                best_position = position;
                shortest_duration = duration;
            }
        }

        /* Etape 2b : insertion du job à la meilleure position */
        for(position = sequence_length - 1; position > best_position; --position)
        {
            swap((void **) jobs, position, position - 1);
        }

        ++sequence_length;
    }

    /* Etape 3 : Ecriture des dates de fin de fabrication "définitives" dans 'fs' */
    for(position = 0; position < n; ++position)
    {
        flowshop_insert_job(fs, jobs[position]);
    }
}
