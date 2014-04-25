/*! @file nearest_neighboor.h @brief Fournit une implémentation de l'algorithme du plus proche voisin : @ref nearest_neighboor() */

#ifndef NEAREST_NEIGHBOOR_H
#define NEAREST_NEIGHBOOR_H

#include "routing.h"

/*! Implémentation de l'algorithme du plus proche voisin
 * @param[in,out] r Un routing
 * @param[in,out] sites Un tableau de sites dont il faut planifier la tournée
 * @pre Le tableau @em sites contient exactement <em>routing_get_nb_sites(r)</em> sites.
 * @pre @ref routing_insert_site() n'a jamais été appelée sur @em r.
 * @note Si besoin, @em r a été initialisé avec la date de début de tournée.
 * @see routing_set_departure_date()
 * @post @em r contient les dates d'arrivée pour tous les sites.
 * @post @em sites est trié selon l'ordre de visite défini par la tournée trouvée.
 * @note @ref nearest_neighboor() insert tous les sites du tableau @em sites dans le routing @em r.
 * @see routing_get_arrival_date(), routing_get_delivery_date()
 */
void nearest_neighboor(routing r, site * sites);

#endif // NEAREST_NEIGHBOOR_H
