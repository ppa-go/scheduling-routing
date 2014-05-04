/*! @file build_one_solution.h @brief Fournit une fonction qui génère une solution à partir de groupes : @ref build_one_solution() */

#ifndef BUILD_ONE_SOLUTION_H
#define BUILD_ONE_SOLUTION_H

#include "solution.h"

/*! Fonction qui génère une solution à partir de groupes
 * @param[in,out] sol Une solution
 * @pre @em sol a été créée avec @ref solution_new().
 * @pre Aucune méthode de @ref flowshop.h n'a été appelée sur les floswhops de @em sol
 * @pre Aucune méthode de @ref routing.h n'a été appelée sur les routings de @em sol
 * @post Les tableaux de jobs par groupe sont triés selon l'ordonnancement trouvé par @ref neh() au sein du groupe.
 * @post Les tableaux de flowshops par groupe sont complets : les fonctions mentionnées ci-après sont utilisables.
 * @see flowshop_get_duration(), flowshop_get_date()
 * @post Les tableaux de sites par groupe sont triés selon la tournée trouvée par @ref nearest_neighboor() au sein du groupe.
 * @post Les tableaux de routings par groupe sont complets : les fonctions mentionnées ci-après sont utilisables.
 * @see routing_get_delivery_date(), routing_get_arrival_date()
 * @post La fonction @ref solution_get_tardiness() peut être appelée sur @em sol.
 * @note Les ordonnancements sont trouvés grâce à la fonction @ref neh().
 * @note Les tournées sont trouvées grâce à la fonction @ref nearest_neighboor().
 */
void build_one_solution(solution sol);

#endif // BUILD_ONE_SOLUTION_H
