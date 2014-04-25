#include "output.h"

#include <stdio.h>



/*! Cette macro définit le caractère de séparation utilisé pour écrire le fichier de sortie. */
#define OUTPUT_SEPARATOR '\t' // tabulation
/*! Cette macro définit la chaîne de caractères utilisée pour écrire un saut de ligne dans le fichier de sortie. */
#define OUTPUT_NEW_LINE "\r\n" // pour fonctionner sous Windows, Mac, Unix



int write_solution(solution * __solution, const char * filename)
{
    /* Ouverture ou création du fichier */
    FILE * file = fopen(filename, "w+");
    if(file == NULL) { return OUTPUT_ERROR; }

    // TO DO

    return OUTPUT_SUCCESS;
}
