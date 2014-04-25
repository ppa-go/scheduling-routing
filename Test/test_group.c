#include "test_group.h"

#include "../group.h"
#include <stdio.h>

void test_group()
{
    unsigned int nombre_elements = 5,
                 tableau_groupes[] = {4,1,3,4,3};

    group group_var = group_new(nombre_elements, tableau_groupes);
    unsigned int id_group, index_element, id_element;

    for(id_group = 1; id_group <= group_get_nb_groups(group_var); ++id_group)
    {
        printf("Groupe %d :", id_group);
        for(index_element = 1; index_element <= group_get_nb_elements_in_group(group_var, id_group); ++index_element)
        {
            id_element = group_get_element_in_group(group_var, id_group, index_element);
            printf(" %d(%d)", id_element, group_get_group_of_element(group_var, id_element));
        }
        puts("");
    }

    group_delete(group_var);
}
