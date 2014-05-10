#include "mutation.h"

#include <stdlib.h>

/*! Cette macro indique que le job sélectionné aléatoirement doit être affecté au groupe précédent.
 * @see mutate()
 * @see MUTATION_INCREASE_GROUP_NUMBER */
#define MUTATION_DECREASE_GROUP_NUMBER 0
/*! Cette macro indique que le job sélectionné aléatoirement doit être affecté au groupe suivant.
 * @see mutate()
 * @see MUTATION_DECREASE_GROUP_NUMBER */
#define MUTATION_INCREASE_GROUP_NUMBER 1



unsigned int * mutate(unsigned int nb_elements, unsigned int * element_to_group)
{
    unsigned int * result = (unsigned int *) malloc(nb_elements * sizeof(unsigned int)),
                 index = rand() % nb_elements,
                 direction = rand() % 2,
                 loop;

    /* Recopie de 'element_to_group' vers 'result' */
    for(loop = 0; loop < nb_elements; ++loop)
    {
        result[loop] = element_to_group[loop];
    }

    /* Mutation pour le job choisi */
    switch(direction)
    {
        case(MUTATION_DECREASE_GROUP_NUMBER):
            --(result[index]);
        break;

        case(MUTATION_INCREASE_GROUP_NUMBER):
            ++(result[index]);
        break;
    }

    /* Le groupe auquel appartient le job choisi est_il VIDE désormais ? */
    for(loop = 0; (loop < nb_elements) && (result[loop] != element_to_group[index]) ; ++loop);

    /* Si tel est le cas, il faut le supprimer : -1 pour tous les numéros de groupe supérieurs */
    if(loop == nb_elements) // La boucle 'for' précédente a parcouru tout le tableau : \forall loop = 0 .. nb_elements , result[loop] != element_to_group[index]
    {
        for(loop = 0; loop < nb_elements; ++loop)
        {
            if(result[loop] > element_to_group[index]) { --(result[loop]); }
        }
    }

    /* Si (Le job choisi appartenait au groupe 1) ET (direction == MUTATION_DECREASE_GROUP_NUMBER) : +1 pour tous les numéros de groupe */
    if(result[index] == 0)
    {
        for(loop = 0; loop < nb_elements; ++loop)
        {
            ++(result[loop]);
        }
    }

    return result;
}
