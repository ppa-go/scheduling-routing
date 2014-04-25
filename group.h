/*! @file group.h @brief Permet de manipuler des objets de type @ref group */

#ifndef GROUP_H
#define GROUP_H

typedef struct group * group;

/*! Fonction qui crée un nouveau @ref group
 * @param nb_elements Le nombre d'éléments répartis en différents groupes
 * @param element_to_group Le tableau des éléments répartis en différents groupes
 * @return Un nouveau @ref group
 * @warning Après utilisation, libérer les ressources en appelant : \ref group_delete()
 *
 * @note La numérotation des groupes est @b normalisée :
 *      @li Aucun groupe n'est vide.
 *      @li Il n'y a aucun trou dans la numérotation.
 * @par
 *
 * @em Exemple : Soit 5 éléments répartis dans les groupes suivants :
 *
 * <tt> const unsigned int <b>element_to_group</b>[] = {4, 1, 3, 4, 3}; </tt>
 *
 * La @b normalisation des groupes donne le résultat suivant :
 *      @li Nombre de groupes = 3
 *      @li Eléments du groupe 1 : 2
 *      @li Eléments du groupe 2 : 3, 5
 *      @li Eléments du groupe 3 : 1, 4
 *
 * Puisque les groupes 2 et 5 sont vides, ils n'apparaissent plus. La nouvelle numérotation est sans trou.
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
