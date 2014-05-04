/*! @file mutation.h @brief Fournit une fonction qui génère des mutations de groupes aléatoires : @ref mutate() */

#ifndef MUTATION_H
#define MUTATION_H

/*! Fonction qui génère des mutations de groupes aléatoires
 * @param nb_elements Le nombre d'éléments répartis en différents groupes
 * @param element_to_group Le tableau des éléments répartis en différents groupes
 * @see group_new()
 * @return Un tableau dynamique, obtenu par "mutation" à partir de @em element_to_group.
 * @post La "mutation" respecte les conditions suivantes :
 *  <ul>
 *      <li> @b Un élément est choisi @b aléatoirement. Désormais, il appartient :
 *          <ul>
 *              <li> @em Soit au groupe qui @b précède celui auquel il appartenait. <br>
 *                  Si l'élément appartenait au @em premier groupe, un nouveau groupe est inséré @em avant tous les autres.</li>
 *              <li> @em Soit au groupe qui @b suit celui auquel il appartenait. <br>
 *                  Si l'élément appartenait au @em dernier groupe, un nouveau groupe est inséré @em après tous les autres.</li>
 *          </ul>
 *          Ce changement de groupe est également @b aléatoire. <br>
 *          Si l'élément était seul dans son @em ancien groupe, ce dernier est supprimé.</li>
 *      <li> @b Tout autre élément @b reste dans le groupe auquel il appartenait.</li>
 *  </ul>
 */
unsigned int * mutate(unsigned int nb_elements, unsigned int * element_to_group);

#endif // MUTATION_H
