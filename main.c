#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "output.h"
#include "find_solution.h"
#include "chrono.h"



/*! Fonction capable de trouver le nom du fichier exécutable correspondant au programme
 * @param program_long_name La première chaîne de caractères contenue dans les paramètres : <tt>argv[0]</tt>
 * @return Le nom du fichier exécutable correspondant au programme
 * @note La chaîne retournée est un pointeur sur la chaîne : <tt>argv[0]</tt>
 */
static const char * get_program_short_name(const char * program_long_name)
{
    const char * program_short_name = program_long_name;

    /* On se déplace à la fin de la chaîne */
    while(*program_short_name != '\0') { ++program_short_name; }

    /* On lit la chaîne à l'envers, jusqu'à trouver un slash ou un anti-slash, ou revenir au début de la chaîne */
    while((program_short_name != program_long_name) && (*program_short_name != '/') && (*program_short_name != '\\')) { --program_short_name; }

    return program_short_name;
}



/*! Fonction capable de lire correctement le paramètre optionnel "nb_mutations" pour la fonction @ref main()
 * @pre La fonction @ref main() a été appelée avec 3 arguments : <tt>argc == 4</tt>
 * @param str La chaîne de caractères associée au paramètre optionnel "nb_mutations" (le troisième : <tt>argv[3]</tt>)
 * @return Un entier positif
 * @post Si l'entier retourné est strictement positif : la valeur du paramètre est exploitable.
 * @warning Si l'entier retourné est nul : la valeur du paramètre n'est @b PAS exploitable !
 *      @li Soit la chaîne @em str représente la valeur 0 ;
 *      @li Soit la chaîne @em str ne représente pas un nombre (elle ne contient pas uniquement des chiffres).
 */
static unsigned int read_nb_mutations(const char * str)
{
    unsigned int nb_mutations = 0;

    /* Tant qu'il y a des chiffres, on lit la chaîne. */
    while(('0' <= *str) && (*str <= '9'))
    {
        nb_mutations = nb_mutations * 10 + (unsigned int) (*(str++) - '0');
    }

    /* Si 'str' n'a pas été totalement parcourue, au moins un caractère n'est pas un chiffre : la fonction doit renvoyer 0. */
    if(*str != '\0')
    {
        nb_mutations = 0;
    }

    return nb_mutations;
}



int main(const int argc, const char * argv[])
{
    const char * program_short_name,
               * input_name,
               * output_name;
    unsigned int nb_mutations;
    instance data;
    solution sol;
    chrono timer;
    int read_status,
        write_status;

    program_short_name = get_program_short_name(argv[0]);

    if((argc != 3) && (argc != 4))
    {
        printf("Syntaxe pour utiliser ce programme :\t");
        printf("%s  input_name  output_name  nb_mutations\n", program_short_name);
        puts("\tinput_name  \tnom du ficher contenant l'instance (obligatoire)");
        puts("\toutput_name \tnom du ficher dans lequel écrire la solution (obligatoire)");
        puts("\tnb_mutations\tnombre de mutations à chaque iteration de l'algorithme (optionnel ; valeur par defaut = nombre de jobs dans l'instance)");
        return EXIT_FAILURE;
    }

    input_name = argv[1];
    output_name = argv[2];
    switch(argc)
    {
        case(3):
            nb_mutations = 0;
        break;

        case(4):
            nb_mutations = read_nb_mutations(argv[3]);
            if(nb_mutations == 0)
            {
                printf("Erreur : nombre de mutations incorrect (\"%s\")\n", argv[3]);
                return EXIT_FAILURE;
            }
        break;
    }

    read_status = read_instance(&data, input_name);

    switch(read_status)
    {
        case(INPUT_ERROR_OPEN):
            printf("Erreur : impossible d'ouvrir le fichier \"%s\"\n", input_name);
        return EXIT_FAILURE;

        case(INPUT_ERROR_SYNTAX):
            printf("Erreur : la syntaxe du fichier \"%s\" est incorrecte.\n", input_name);
        return EXIT_FAILURE;

        case(INPUT_SUCCESS):
            puts("Lecture de l'instance : OK");

            timer = chrono_new();
            srand(time(NULL));

            puts("Algorithme : START");
            chrono_start(timer);
            sol = find_solution(data, nb_mutations);
            chrono_stop(timer);
            puts("Algorithme : STOP");

            solution_set_cpu_time(sol, chrono_get_time(timer));
            write_status = write_solution(&sol, output_name);

            solution_delete(sol);
            instance_delete(data);
            chrono_delete(timer);

            switch(write_status)
            {
                case(OUTPUT_ERROR):
                    printf("Erreur : impossible d'ouvrir ou de creer le fichier \"%s\"\n", output_name);
                return EXIT_FAILURE;

                case(OUTPUT_SUCCESS):
                    puts("Ecriture de la solution : OK");
                break; // return EXIT_SUCCESS;
            }
    }

    return EXIT_SUCCESS;
}
