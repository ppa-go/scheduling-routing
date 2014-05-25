/*! @file find_first_group.h @brief Fournit une fonction qui génère une répartition des jobs d'une instance en groupes : @ref find_first_group() */

#ifndef FIND_FIRST_GROUP_H
#define FIND_FIRST_GROUP_H

#include "instance.h"

/*! Fonction qui génère une répartition des jobs d'une instance en groupes
 * @param data L'instance contenant les jobs à répartir en groupes
 * @return Un tableau dynamique qui indique quel job de l'instance appartient à quel groupe
 * @warning Après utilisation, libérer les ressources en appelant : @b free()
 * @post Le tableau retourné est @b normalisé.
 * @see solution_new()
 * @note L'algorithme utilisé pour constituer les groupes est le suivant :
 *  <ol>
 *      <li>Tri des jobs dans l'ordre croissant des dates dues <em>(EDD = Earlier Due Date first)</em>.<br>
 *          Les jobs sont considérés un à un selon cet ordre.</li>
 *      <li>Création du premier groupe, qui contient uniquement le premier job.</li>
 *      <li>Pour @em j de @em 2 à <em>(nombre de jobs dans l'instance)</em> Faire
 *          <ul>
 *              <li>Simuler l'insertion du job numéro @em j dans le dernier groupe.</li>
 *              <li>Simuler la création d'un nouveau groupe, qui contient uniquement le job numéro @em j, traité après le dernier groupe.</li>
 *              <li>Conserver la simulation pour laquelle le retard accumulé est minimal.<br>
 *                  (En cas d'égalité, la première simulation est retenue.)</li>
 *          </ul>
 *          Fin Pour</li>
 *  </ol>
 * @note Les ordonnancements pour chaque groupe sont trouvés grâce à la fonction @ref neh().
 * @note Les tournées pour chaque groupe sont trouvées grâce à la fonction @ref nearest_neighbor().
 */
unsigned int * find_first_group(instance data);

#endif // FIND_FIRST_GROUP_H
