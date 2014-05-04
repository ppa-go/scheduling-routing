/*! @file routing.h @brief Permet de manipuler des objets de type @ref routing pour gérer les problématiques de tournée */

#ifndef ROUTING_H
#define ROUTING_H

#include "site.h"

typedef struct routing * routing;

/*! Fonction qui crée un nouveau routing
 * @param nb_sites Le nombre de sites dans le groupe auquel le routing est associé
 * @param factory Le site correspondant à l'usine dans l'instance à laquelle le routing est associé
 * @return Un nouveau routing
 * @warning Après utilisation, libérer les ressources en appelant : @ref routing_delete()
 * @note La date de début de tournée par défaut est : <em>t = 0</em>
 * @see routing_set_departure_date()
 * @post La position courante d'insertion de sites est égale à 1. (aucun site inséré)
 * @see routing_get_current_position()
 */
routing routing_new(unsigned int nb_sites, site factory);
/*! Fonction qui libère les ressources utilisées par un routing
 * @param __routing Le routing à supprimer
 * @note Les ressources utilisées par le routing sont libérées.
 */
void routing_delete(routing __routing);

/*! Fonction qui retourne le nombre de sites dans la tournée à planifier
 * @param __routing Un routing
 * @return Le nombre de sites dans le routing à planifier
 */
unsigned int routing_get_nb_sites(routing __routing);

/*! Fonction qui permet de modifier une date de début de tournée
 * @param __routing Un routing
 * @param value La date de début du routing (départ de l'usine)
 * @warning Cette fonction ne doit jamais être appelée après avoir inséré un site avec @ref routing_insert_site() !
 * @see routing_get_departure_date()
 */
void routing_set_departure_date(routing __routing, unsigned int value);
/*! Fonction qui retourne une date de début de tournée
 * @param __routing Un routing
 * @return La date de début du routing (départ de l'usine)
 * @see routing_set_departure_date()
 */
unsigned int routing_get_departure_date(routing __routing);

/*! Fonction qui permet d'insérer un site à la position courante dans une tournée
 * @param __routing Un routing
 * @param site_to_insert Le site à placer à la position courante dans la tournée
 * @post La date d'arrivée au site inséré à la position courante est calculée.
 * @post La position courante d'insertion de job est augmentée de 1.
 * @note Pour spécifier la date de début de tournée, utiliser au préalable : @ref routing_set_departure_date()
 * @warning Cette fonction doit être appelée exactement <em>routing_get_nb_sites(__routing)</em> fois !
 * @warning Pas de retour en arrière : l'insertion d'un site est définitive ! (Ne peut pas être annulée)
 * @see routing_get_current_position()
 */
void routing_insert_site(routing __routing, site site_to_insert);

/*! Fonction qui retourne la position courante pour l'insertion d'un site
 * @param __routing Un routing
 * @return La position courante pour l'insertion d'un site, utilisée par @ref routing_insert_site()
 */
unsigned int routing_get_current_position(routing __routing);

/*! Fonction qui retourne le site visité à l'étape précédente lors d'une tournée
 * @param __routing Un routing
 * @return Le site visité à l'étape précédente lors de la tournée
 * @note Si la tournée n'a pas encore commencé ( <tt> @ref routing_get_current_position (__routing) == 1</tt> ), le site retourné est celui qui correspond à l'usine dans l'instance à laquelle le routing est associé.
 * @warning Si la tournée est terminée ( <tt> @ref routing_get_current_position (__routing) > @ref routing_get_nb_sites (__routing)</tt> ), la fonction renvoie <tt>NULL</tt> .
 */
site routing_get_previous_site(routing __routing);

/*! Fonction qui retourne une date de fin de tournée
 * @param __routing Un routing
 * @return La date de fin du routing (arrivée à l'usine)
 * @warning Pour pouvoir utiliser cette fonction, tous les sites doivent avoir été insérés au préalable : <tt> @ref routing_get_current_position (__routing) > @ref routing_get_nb_sites (__routing)</tt>
 * @see flowshop_insert_job()
 */
unsigned int routing_get_arrival_date(routing __routing);

/*! Fonction qui retourne une date d'arrivée à un site
 * @param __routing Un routing
 * @param position Une position dans la tournée
 * @return La date d'arrivée au site (identifié par sa position) au cours de la tournée
 * @warning Pour pouvoir utiliser cette fonction, tous les sites doivent avoir été insérés au préalable : <tt> @ref routing_get_current_position (__routing) > @ref routing_get_nb_sites (__routing)</tt>
 * @see flowshop_insert_job()
 */
unsigned int routing_get_delivery_date(routing __routing, unsigned int position);

#endif // ROUTING_H
