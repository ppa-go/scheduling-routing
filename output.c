#include "output.h"

#include <stdio.h>



/*! Cette macro définit le caractère de séparation utilisé pour écrire le fichier de sortie. */
#define OUTPUT_SEPARATOR '\t' // tabulation
/*! Cette macro définit la chaîne de caractères utilisée pour écrire un saut de ligne dans le fichier de sortie. */
#define OUTPUT_NEW_LINE "\r\n" // pour fonctionner sous Windows, Mac, Unix



int write_solution(solution * __solution, const char * filename)
{
    const unsigned int nb_groups = solution_get_nb_groups(*__solution);
    unsigned int id_group, nb_elements_in_group, index;
    job * jobs;
    site * sites;

    FILE * file = fopen(filename, "w+");
    if(file == NULL) { return OUTPUT_ERROR; }

    fprintf(file, "%d%c## Somme des retards%s", solution_get_tardiness(*__solution), OUTPUT_SEPARATOR, OUTPUT_NEW_LINE);
    fprintf(file, "%d%c## Nombre de groupes dans la solution%s", nb_groups, OUTPUT_SEPARATOR, OUTPUT_NEW_LINE);
    fprintf(file, "### Ordonnancement ###%s", OUTPUT_NEW_LINE);
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = solution_get_nb_elements_in_group(*__solution, id_group);
        jobs = solution_get_jobs_in_group(*__solution, id_group);
        for(index = 1; index <= nb_elements_in_group; ++index)
        {
            fprintf(file, "%d%c", job_get_id(jobs[index]), OUTPUT_SEPARATOR);
        }
        fprintf(file, "## Groupe %d%s", id_group, OUTPUT_NEW_LINE);
    }
    fprintf(file, "### Tournées ###%s", OUTPUT_NEW_LINE);
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = solution_get_nb_elements_in_group(*__solution, id_group);
        sites = solution_get_sites_in_group(*__solution, id_group);
        for(index = 1; index <= nb_elements_in_group; ++index)
        {
            fprintf(file, "%d%c", site_get_id(sites[index]), OUTPUT_SEPARATOR);
        }
        fprintf(file, "## Groupe %d%s", id_group, OUTPUT_NEW_LINE);
    }

    fclose(file);

    return OUTPUT_SUCCESS;
}
