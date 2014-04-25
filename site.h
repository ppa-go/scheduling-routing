/*! @file site.h @brief Permet de manipuler des objets de type @ref site */

#ifndef SITE_H
#define SITE_H

/*! Cette macro fournit un ID valide pour représenter l'usine. */
#define SITE_ID_FACTORY 0

typedef struct site * site;

/*! Fonction qui crée un nouveau site
 * @param id L'ID du site à créer
 * @param nb_sites Le nombre de sites dans l'instance à laquelle le site appartient
 * @return Un nouveau site
 * @warning Après utilisation, libérer les ressources en appelant : \ref site_delete()
 */
site site_new(unsigned int id, unsigned int nb_sites);
/*! Fonction qui libère les ressources utilisées par un site
 * @param __site Le site à supprimer
 * @note Les ressources utilisées par le site sont libérées.
 */
void site_delete(site __site);

/*! Fonction qui retourne l'ID d'un site
 * @param __site Un site
 * @return L'ID du site
 */
unsigned int site_get_id(site __site);
/*! Fonction qui retourne le nombre de sites dans l'instance à laquelle un site appartient
 * @param __site Un site
 * @return Le nombre de sites dans l'instance à laquelle le site appartient
 */
unsigned int site_get_nb_sites(site __site);

/*! Fonction qui permet de modifier une durée de voyage
 * @param __site Le site de départ
 * @param id_other_site L'ID du site d'arrivée
 * @param value La durée de voyage du site à l'autre site
 * @see site_get_travelling_time()
 */
void site_set_travelling_time(site __site, unsigned int id_other_site, unsigned int value);

/*! Fonction qui retourne une durée de voyage
 * @param __site Le site de départ
 * @param id_other_site L'ID du site d'arrivée
 * @return La durée de voyage du site à l'autre site
 * @see site_set_travelling_time()
 */
unsigned int site_get_travelling_time(site __site, unsigned int id_other_site);

#endif // SITE_H
