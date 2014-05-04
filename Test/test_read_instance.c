#include "test_read_instance.h"

#include "../input.h"
#include <stdio.h>

void test_read_instance()
{
    char filename[1024];
    instance data;
    unsigned int i, j, j1, j2;

    puts("Nom du fichier contenant l'instance de test ?");
    scanf("%s", filename);

    switch(read_instance(&data, filename))
    {
        case(INPUT_ERROR_OPEN):
            puts("Erreur : impossible d'ouvrir le fichier !");
        break;

        case(INPUT_ERROR_SYNTAX):
            puts("Erreur : syntaxe incorrecte");
        break;

        case(INPUT_SUCCESS):
            {
                /* Taille de l'instance */
                printf("%d\t%d", instance_get_nb_machines(data), instance_get_nb_jobs(data));
                if(instance_get_nb_jobs(data) != instance_get_nb_sites(data))
                {
                    printf("\tATTENTION : nombre de sites = %d", instance_get_nb_sites(data));
                }
                puts("");
                /* Durées de fabrication */
                for(i = 1; i <= instance_get_nb_machines(data); ++i)
                {
                    for(j = 1; j <= instance_get_nb_jobs(data); ++j)
                    {
                        printf("%d\t", instance_get_processing_time(data, i, j));
                    }
                    puts("");
                }
                /* Dates dues */
                for(j = 1; j <= instance_get_nb_jobs(data); ++j)
                {
                    printf("%d\t", instance_get_due_date(data, j));
                }
                puts("");
                /* Durées de voyage */
                for(j1 = 0; j1 <= instance_get_nb_sites(data); ++j1)
                {
                    for(j2 = 0; j2 <= instance_get_nb_sites(data); ++j2)
                    {
                        printf("%d\t", instance_get_travelling_time(data, j1, j2));
                    }
                    puts("");
                }

                instance_delete(data);
            }
        break;

        default:
            puts("??? Que pasa ???");
    }
}
