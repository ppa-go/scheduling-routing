/*! @file find_solution.h @brief Fournit une implémentation d'un algorithme de descente locale : @ref find_solution() */

#ifndef FIND_SOLUTION_H
#define FIND_SOLUTION_H

#include "instance.h"
#include "solution.h"

/*! Fonction qui retourne une solution pour une instance donnée, en réalisant une descente locale
 * @param data Une instance
 * @param nb_mutations Le nombre de mutations à réaliser à chaque étape de l'algorithme
 * @note Si @em nb_mutations est égal à 0, le nombre de mutations utilisé dans l'algorithme sera le nombre de jobs dans l'instance
 * @return Une solution pour l'instance @em data
 * @warning Après utilisation, libérer les ressources en appelant : @ref solution_delete()
 * @note L'algorithme utilisé pour construire la solution retournée est le suivant :
 *  <ol>
 *      <li>Recherche d'une solution "mère" initiale (heuristique)</li>
 *      <li>Faire :
 *          <ul>
 *              <li>Générer @em nb_mutations solutions "filles", à partir de la solution "mère" (mutations aléatoires)</li>
 *              <li>Rechercher la meilleure solution parmi les solutions "fille"</li>
 *              <li>Si la meilleure solution "fille" est elle-même meilleure que la solution "mère" actuelle, alors elle devient la prochaine solution "mère".</li>
 *          </ul>
 *          Tant que : L'une des solutions "fille" est meilleure que la solution "mère".</li>
 *  </ol>
 * @note La solution initiale est trouvée grâce à la fonction @ref find_first_group().
 * @note Les mutations sont effectuées sur la répartition des jobs en groupe, avec la fonction @ref mutate().
 * @note L'algorithme génère des solutions "filles" jusqu'à ce qu'elles soient deux à deux distinctes.
 */
solution find_solution(instance data, unsigned int nb_mutations);

#endif // FIND_SOLUTION_H
