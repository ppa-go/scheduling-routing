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

    /* Ligne 1 : Somme des retards */
    fprintf(file, "%d%c## Somme des retards%s", solution_get_tardiness(*__solution), OUTPUT_SEPARATOR, OUTPUT_NEW_LINE);
    /* Ligne 2 : Temps CPU (millisecondes) */
    fprintf(file, "%d%c## Temps CPU (millisecondes)%s", solution_get_cpu_time(*__solution), OUTPUT_SEPARATOR, OUTPUT_NEW_LINE);
    /* Ligne 3 : Séquence d'ordonnancement (tous les groupes à la suite) */
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = solution_get_nb_elements_in_group(*__solution, id_group);
        jobs = solution_get_jobs_in_group(*__solution, id_group);
        for(index = 0; index < nb_elements_in_group; ++index)
        {
            fprintf(file, "%d%c", job_get_id(jobs[index]), OUTPUT_SEPARATOR);
        }
    }
    fprintf(file, "## Ordonnancement%s", OUTPUT_NEW_LINE);
    /* Ligne 4 : Nombre de tournées == nombre de groupes */
    fprintf(file, "%d%c## Nombre de tournées%s", nb_groups, OUTPUT_SEPARATOR, OUTPUT_NEW_LINE);
    /* Ligne 5 : Nombre de sites par tournées */
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        fprintf(file, "%d%c", solution_get_nb_elements_in_group(*__solution, id_group), OUTPUT_SEPARATOR);
    }
    fprintf(file, "## Nombre de sites par tournée%s", OUTPUT_NEW_LINE);
    /* Lignes suivantes : 1 ligne == 1 tournée */
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        nb_elements_in_group = solution_get_nb_elements_in_group(*__solution, id_group);
        sites = solution_get_sites_in_group(*__solution, id_group);
        for(index = 0; index < nb_elements_in_group; ++index)
        {
            fprintf(file, "%d%c", site_get_id(sites[index]), OUTPUT_SEPARATOR);
        }
        fprintf(file, "## Tournée %d%s", id_group, OUTPUT_NEW_LINE);
    }

    fclose(file);

    return OUTPUT_SUCCESS;
}
