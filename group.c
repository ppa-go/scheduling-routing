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

    /* 1. Déclaration et initialisation des ressources temporaires */
    unsigned int * nb_elements_per_group = (unsigned int *) calloc(nb_elements, sizeof(unsigned int)),
                 nb_groups = 0,
                 id_element,
                 group_index,
                 element_index,
                 id_group;
    /* 2. Compter le nombre d'éléments par groupe (il y en a au plus 'nb_elements') */
    for(id_element = 0; id_element < nb_elements; ++id_element)
    {
        ++(nb_elements_per_group[element_to_group[id_element] - 1]);
    }
    /* 3. Copier 'nb_elements' et 'element_to_group' dans 'new_group' en normalisant la numérotation des groupes */
    new_group->nb_elements = nb_elements;
    new_group->element_to_group = (unsigned int *) malloc(nb_elements * sizeof(unsigned int));
    for(id_element = 0; id_element < nb_elements; ++id_element)
    {
        id_group = element_to_group[id_element];
        for(group_index = 0; group_index < element_to_group[id_element]; ++group_index)
        {
            if(nb_elements_per_group[group_index] == 0) { --id_group; }
        }

        new_group->element_to_group[id_element] = id_group;
    }
    /* 4. Compter le nombre de groupes non vides (avec au moins un élément) */
    for(group_index = 0; group_index < nb_elements; ++group_index)
    {
        if(nb_elements_per_group[group_index] > 0) { ++nb_groups; }
    }
    /* 5. Construire les groupes, en ignorant les éventuels groupes vides */
    new_group->nb_groups = nb_groups;
    new_group->nb_elements_per_group = (unsigned int *) malloc(nb_groups * sizeof(unsigned int));
    new_group->elements_per_group = (unsigned int **) malloc(nb_groups * sizeof(unsigned int *));

    group_index = 0;
    for(id_group = 0; id_group < nb_groups; ++id_group)
    {
        /* Recherche d'un groupe non vide */
        while(nb_elements_per_group[group_index] == 0) { ++group_index; }

        new_group->nb_elements_per_group[id_group] = nb_elements_per_group[group_index];
        new_group->elements_per_group[id_group] = (unsigned int *) malloc(nb_elements_per_group[group_index] * sizeof(unsigned int));

        id_element = 0;
        for(element_index = 0; element_index < nb_elements_per_group[group_index]; ++element_index)
        {
            /* Recherche d'un élément dans le groupe */
            while(element_to_group[id_element] != group_index + 1) { ++id_element; }

            new_group->elements_per_group[id_group][element_index] = id_element + 1;

            ++id_element;
        }

        ++group_index;
    }
    /* 6. Libération des ressources temporaires */
    free(nb_elements_per_group);

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
