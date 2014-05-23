/*! @file group.h @brief Permet de manipuler des objets de type @ref group */

#ifndef GROUP_H
#define GROUP_H

typedef struct group * group;

/*! Fonction qui crée un nouveau @ref group
 * @param nb_elements Le nombre d'éléments répartis en différents groupes
 * @param element_to_group Le tableau des éléments répartis en différents groupes
 * @pre @em element_to_group doit être @b normalisé : voir @b Note !!!
 * @return Un nouveau @ref group
 * @warning Après utilisation, libérer les ressources en appelant : @ref group_delete()
 *
 * @note Un tableau de répartition d'éléments en groupes est @b normalisé si :
 *      @li le numéro associé au premier groupe non vide est @b 1 ;
 *      @li la numérotation des groupes est @b continue, c'est-à-dire "sans trou". (pas de groupe intermédiaire vide)
 *
 * @par Exemple
 *  Soit 5 éléments répartis dans les groupes suivants :
 *  @li <tt> unsigned int @b tab1[] = {5, 2, 4, 5, 2}; </tt> <br>
 *      @b tab1 n'est pas normalisé, car aucun job n'appartient au groupe 1. <br>
 *  @li <tt> unsigned int @b tab2[] = {4, 1, 3, 4, 3}; </tt> <br>
 *      @b tab2 n'est pas normalisé : les groupes 3 et 4 ne sont pas vides alors que le groupe 2 est vide. <br>
 *  @li <tt> unsigned int @b tab3[] = {3, 1, 2, 3, 2}; </tt> <br>
 *      @b tab3 est @em normalisé.
 *
 *  On peut remarquer que les configurations représentées par @b tab1, @b tab2 et @b tab3 sont équivalentes :
 *      @li Nombre de groupes <em>non vides</em> = 3
 *      @li Répartition des jobs :
 *          <ol>
 *              <li>Jobs dans le premier groupe <em>non vide</em> : job 2</li>
 *              <li>Jobs dans le deuxième groupe <em>non vide</em> : job 3, job 5</li>
 *              <li>Jobs dans le troisième groupe <em>non vide</em> : job 1, job 4</li>
 *          </ol>
 */
group group_new(unsigned int nb_elements, unsigned int * element_to_group);
/*! Fonction qui libère les ressources utilisées par un @ref group
 * @param __group Le @ref group à supprimer
 * @note Les ressources utilisées par le @ref group sont libérées.
 */
void group_delete(group __group);

/*! Fonction qui retourne le nombre d'éléments dans un @ref group
 * @param __group Un objet de type @ref group
 * @return Le nombre d'éléments dans le @ref group
 */
unsigned int group_get_nb_elements(group __group);
/*! Fonction qui retourne le groupe auquel un élément appartient dans un @ref group
 * @param __group Un objet de type @ref group
 * @param id_element L'ID d'un élément du @ref group
 * @return L'ID normalisé du groupe auquel l'élément (identifié par son ID) appartient dans un @ref group
 */
unsigned int group_get_group_of_element(group __group, unsigned int id_element);

/*! Fonction qui retourne le nombre de groupes dans un @ref group
 * @param __group Un objet de type @ref group
 * @return Le nombre de groupes dans le @ref group
 */
unsigned int group_get_nb_groups(group __group);
/*! Fonction qui retourne le nombre d'éléments dans un groupe donnée au sein d'un @ref group
 * @param __group Un objet de type @ref group
 * @param id_group L'ID normalisé d'un groupe au sein du @ref group
 * @return Le nombre d'éléments dans le groupe (identifié par son ID) au sein du @ref group
 */
unsigned int group_get_nb_elements_in_group(group __group, unsigned int id_group);
/*! Fonction qui retourne l'un des éléments dans un groupe donnée au sein d'un @ref group
 * @param __group Un objet de type @ref group
 * @param id_group L'ID normalisé d'un groupe au sein du @ref group
 * @param index Une position unique associée à un élément du groupe dont l'ID normalisé vaut @em id_group.
 * @return Un élément appartenant au groupe (identifié par son ID) au sein du @ref group
 * @note Aucun tri particulier n'est effectué sur les éléments d'un groupe : les valeurs d'index servent seulement à accéder aux différents éléments.
 */
unsigned int group_get_element_in_group(group __group, unsigned int id_group, unsigned int index);

#endif // GROUP_H
