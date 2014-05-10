#include "test_mutation.h"

#include "../mutation.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



void test_mutation()
{
    const unsigned int size = 10;
    unsigned int * element_to_group = (unsigned int *) malloc(size * sizeof(unsigned int)),
                 * mutated_element_to_group,
                 loop;
    char input[1024];

    srand(time(NULL));

    for(loop = 0; loop < size; ++loop)
    {
        element_to_group[loop] = loop + 1;
    }

    for(loop = 0; loop < size; ++loop)
    {
        printf("%d\t", element_to_group[loop]);
    }
    printf("Continuer ? [\"y\" = oui, (autre) = non]\t");
    scanf("%s", input);

    while(strcasecmp(input, "y") == 0)
    {
        mutated_element_to_group = mutate(size, element_to_group);

        for(loop = 0; loop < size; ++loop)
        {
            if(mutated_element_to_group[loop] == element_to_group[loop])
            {
                printf("%d\t", mutated_element_to_group[loop]);
            }
            else
            {
                printf("#%d#\t", mutated_element_to_group[loop]);
            }
        }

        free(element_to_group);
        element_to_group = mutated_element_to_group;

        printf("Continuer ? [\"y\" = oui, (autre) = non]\t");
        scanf("%s", input);
    }

    free(element_to_group);
}
