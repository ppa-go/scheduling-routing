/*! @file sort.h @brief Fournit une implémentation d'un algorithme de tri par tas : @ref sort() */

#ifndef SORT_H
#define SORT_H

/*! Ce type de données représente les fonctions qui comparent des éléments deux à deux.
 *
 * Un comparateur définit une <b>relation d'ordre</b> entre éléments de même type, "castés" en : <tt>void *</tt>
 *
 * <tt>comparator(first_value, second_value)</tt> doit renvoyer "vrai"   <em>si et seulement si</em>   <tt>first_value < second_value</tt>.
 *
 * Le <b>sens</b> donné à la comparaison <em>dépend de l'interprétation de l'utilisateur</em>.
 */
typedef int (* comparator) (void *, void *);

/*! Implémentation d'un algorithme de tri par tas
 * @param[in] nb_values Le nombre d'éléments à trier
 * @param[in,out] values Un tableau de @em nb_values éléments à trier
 * @param[in] __comparator Un comparateur qui définit une relation d'ordre pour les éléments à trier
 * @post Le tableau est trié par ordre <b>croissant</b> selon l'ordre défini par le comparateur.
 * @see comparator
 */
void sort(unsigned int nb_values, void ** values, comparator __comparator);

/*! Fonction qui permet d'échanger des éléments dans un tableau
 * @param values Un tableau
 * @param index1 Une position valide pour le tableau @em values
 * @param index2 Une position valide pour le tableau @em values
 * @post Les contenus des cases mémoire en positions @em index1 et @em index2 dans le tableau @em values sont intervertis.
 */
void swap(void ** values, const unsigned int index1, const unsigned int index2);

#endif // SORT_H
