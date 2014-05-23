#include "../headers/find_solution.h"

#include "../headers/find_first_group.h"
#include "../headers/mutation.h"
#include "../headers/build_one_solution.h"
#include <stdlib.h>



/*! Fonction qui compare le contenu de deux tableaux d'entiers
 * @param length Le nombre d'éléments dans les deux tableaux à comparer
 * @param array1 Un tableau d'entiers
 * @param array2 Un tableau d'entiers
 * @return @b Vrai (valeur non nulle) si <em>array1[index] == array2[index]</em> pour chaque @em index entre @em 0 et <em>length - 1</em>
 * @return @b Faux (valeur nulle) sinon
 */
static int compare_array(unsigned int length, unsigned int * array1, unsigned int * array2)
{
    unsigned int loop;

    for(loop = 0; (loop < length) && (array1[loop] == array2[loop]); ++loop);

    return loop == length;
}



solution find_solution(instance data, unsigned int nb_mutations)
{
    if(nb_mutations == 0) { nb_mutations = instance_get_nb_jobs(data); }
    unsigned int * parent_job_to_group = find_first_group(data);
    solution parent_solution = solution_new(data, parent_job_to_group);
    unsigned int ** children_job_to_group = (unsigned int **) malloc(nb_mutations * sizeof(unsigned int *));
    solution * children_solution = (solution *) malloc(nb_mutations * sizeof(solution));
    unsigned int nb_elements = instance_get_nb_jobs(data),
                 best_tardiness,
                 tardiness,
                 id_child_solution,
                 loop;
    int once_more,
        generated_yet;

    build_one_solution(parent_solution);
    best_tardiness = solution_get_tardiness(parent_solution);
    do
    {
        /* Pour l'instant, aucune solution meilleure que la solution "mère" n'a été trouvée */
        once_more = 0;

        /* Génération de 'nb_mutations' nouvelles répartitions de jobs en groupes, à partir de 'parent_job_to_group' */
        for(id_child_solution = 1; id_child_solution <= nb_mutations; ++id_child_solution)
        {
            /* Génération d'une nouvelle répartition des jobs en groupe par "mutation" */
            children_job_to_group[id_child_solution - 1] = mutate(nb_elements, parent_job_to_group);

            /* Vérification : cette répartition a-t-elle été déjà générée pour cette itération ? (boucle 'while') */
            generated_yet = !compare_array(nb_elements, parent_job_to_group, children_job_to_group[id_child_solution - 1]);
            for(loop = 1; (loop < id_child_solution) && (!generated_yet); ++loop)
            {
                generated_yet = !compare_array(nb_elements, children_job_to_group[loop - 1], children_job_to_group[id_child_solution - 1]);
            }

            /* Si la répartition avait déjà été générée, il faut en générer une autre à la place */
            if(generated_yet)
            {
                free(children_job_to_group[id_child_solution - 1]);
                children_job_to_group[id_child_solution - 1] = NULL;
                --id_child_solution; // A la prochaine itération (boucle 'for'), 'id_child_solution' aura la même valeur qu'à cette itération
            }
        }

        /* Construction des solutions associées à ces répartitions de jobs en groupe */
        for(id_child_solution = 1; id_child_solution <= nb_mutations; ++id_child_solution)
        {
            children_solution[id_child_solution - 1] = solution_new(data, children_job_to_group[id_child_solution - 1]);
            build_one_solution(children_solution[id_child_solution - 1]);
        }

        /* Recherche de la meilleure solution parmi la "mère" et ses "filles" */
        for(id_child_solution = 1; id_child_solution <= nb_mutations; ++id_child_solution)
        {
            tardiness = solution_get_tardiness(children_solution[id_child_solution - 1]);
            if(tardiness < best_tardiness) // La solution 'id_child_solution' est meilleure
            {
                /* Remplacement de la solution "mère" par la solution 'id_child_solution' */
                free(parent_job_to_group);
                parent_job_to_group = children_job_to_group[id_child_solution - 1];
                children_job_to_group[id_child_solution - 1] = NULL;

                solution_delete(parent_solution);
                parent_solution = children_solution[id_child_solution - 1];
                children_solution[id_child_solution - 1] = NULL;

                best_tardiness = tardiness;

                /* Une solution meilleure a été trouvée : il faudra refaire une itération supplémentaire (boucle 'do ... while') */
                once_more = 1;
            }
        }

        /* Libération des ressources allouées à cette itération (boucle 'do ... while') */
        for(id_child_solution = 1; id_child_solution <= nb_mutations; ++id_child_solution)
        {
            free(children_job_to_group[id_child_solution - 1]); // fonctionne aussi avec : NULL
            if(children_solution[id_child_solution - 1] != NULL) { solution_delete(children_solution[id_child_solution - 1]); }
        }
    }
    while(once_more);

    /* Libération des ressources */
    free(parent_job_to_group);
    free(children_job_to_group);
    free(children_solution);

    return parent_solution;
}
