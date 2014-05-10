#include "group.h"

#include <stdlib.h>



/*! Structure représentant des groupes
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref group.h.
 * @see group.h
 */
struct group
{
    unsigned int nb_elements; //!< Le nombre d'éléments dans le @ref group
    unsigned int * element_to_group; //!< Un tableau dynamique @b normalisé (voir @ref group_new()) qui indique quel élément appartient à quel groupe
    unsigned int nb_groups; //!< Le nombre de groupes
    unsigned int * nb_elements_per_group; //!< Un tableau dynamique répertoriant le nombre d'éléments par groupe
    unsigned int ** elements_per_group; //!< Un tableau dynamique répertoriant l'ensemble des éléments appartenant à un même groupe
};



group group_new(unsigned int nb_elements, unsigned int * element_to_group)
{
    group new_group = (group) malloc(sizeof(struct group));
    unsigned int nb_groups = 1,
                 id_group,
                 loop,
                 ** indexes;

    /* Recherche du nombre de groupes == numéro de groupe maximal */
    for(loop = 0; loop < nb_elements; ++loop)
    {
        if(element_to_group[loop] > nb_groups) { nb_groups = element_to_group[loop]; }
    }

    /* Initialisation de 'group_new' : element -> quel est son groupe ? (Recopie de 'nb_elements' et 'element_to_group') */
    new_group->nb_elements = nb_elements;
    new_group->element_to_group = (unsigned int *) malloc(nb_elements * sizeof(unsigned int));
    for(loop = 0; loop < nb_elements; ++loop)
    {
        new_group->element_to_group[loop] = element_to_group[loop];
    }

    /* Initialisation de 'group_new' : groupe -> quels sont les éléments dans ce groupe ? */
    new_group->nb_groups = nb_groups;
    /* Comptage du nombre d'éléments par groupe */
    new_group->nb_elements_per_group = (unsigned int *) calloc(nb_groups, sizeof(unsigned int));
    for(loop = 0; loop < nb_elements; ++loop)
    {
        ++(new_group->nb_elements_per_group[element_to_group[loop] - 1]);
    }
    /* Insertion de chaque élément dans son groupe */
    new_group->elements_per_group = (unsigned **) malloc(nb_groups * sizeof(unsigned int *));
    indexes = (unsigned **) malloc(nb_groups * sizeof(unsigned int *));
    for(id_group = 1; id_group <= nb_groups; ++id_group)
    {
        new_group->elements_per_group[id_group - 1] = (unsigned int *) malloc(new_group->nb_elements_per_group[id_group - 1] * sizeof(unsigned int));
        indexes[id_group - 1] = &(new_group->elements_per_group[id_group - 1][0]);
    }
    for(loop = 0; loop < nb_elements; ++loop)
    {
        *((indexes[element_to_group[loop] - 1])++) = loop + 1;
    }
    free(indexes);

    return new_group;
}

void group_delete(group __group)
{
    unsigned int id_group;

    for(id_group = 0; id_group < __group->nb_groups; ++id_group)
    {
        free(__group->elements_per_group[id_group]);
    }

    free(__group->element_to_group);
    free(__group->nb_elements_per_group);
    free(__group->elements_per_group);

    free(__group);
}



unsigned int group_get_nb_elements(group __group)
{
    return __group->nb_elements;
}

unsigned int group_get_group_of_element(group __group, unsigned int id_element)
{
    return __group->element_to_group[--id_element];
}



unsigned int group_get_nb_groups(group __group)
{
    return __group->nb_groups;
}

unsigned int group_get_nb_elements_in_group(group __group, unsigned int id_group)
{
    return __group->nb_elements_per_group[--id_group];
}

unsigned int group_get_element_in_group(group __group, unsigned int id_group, unsigned int index)
{
    return __group->elements_per_group[--id_group][--index];
}
