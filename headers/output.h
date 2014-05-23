/*! @file output.h @brief Permet d'écrire des objets de type @ref solution dans un fichier texte */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "solution.h"

/*! Cette macro indique que l'écriture d'une solution a réussi.
 *
 * Lorsque @ref write_solution() renvoie cette valeur, cela signifie que le fichier a bien été écrit.
 * @see write_solution()
 */
#define OUTPUT_SUCCESS 0
/*! Cette macro indique que l'écriture d'une solution a échoué.
 *
 * Lorsque @ref write_solution() renvoie cette valeur, cela signifie que le fichier n'a pas pas pu être ouvert ou créé.
 * @see write_solution()
 */
#define OUTPUT_ERROR 1

/*! Fonction qui écrit les données d'une solution en mémoire dans un fichier
 * @param[in] __solution La solution contenant les données à écrire
 * @param[out] filename Le nom du fichier dans lequel écrire la solution
 * @return @ref OUTPUT_SUCCESS ou @ref OUTPUT_ERROR
 */
int write_solution(solution * __solution, const char * filename);

#endif // OUTPUT_H
