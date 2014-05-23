#include "../headers/routing.h"

#include <stdlib.h>



/*! Structure représentant un routing
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref routing.h.
 * @see routing.h
 */
struct routing
{
    unsigned int nb_sites; //!< Le nombre de sites dans le groupe associé à la tournée
    unsigned int * dates; //!< Un tableau dynamique contenant la date de départ de l'usine, les dates d'arrivée sur les sites, et la date de retour à l'usine
    site previous_site; //!< Le dernier site inséré
    unsigned int current_position; //!< La position courante d'insertion de site
};



routing routing_new(unsigned int nb_sites, site factory)
{
    routing new_routing = (routing) malloc(sizeof(struct routing));

    new_routing->nb_sites = nb_sites;
    new_routing->dates = (unsigned int *) calloc(nb_sites + 2, sizeof(unsigned int));
    new_routing->previous_site = factory;
    new_routing->current_position = 1;

    return new_routing;
}

void routing_delete(routing __routing)
{
    free(__routing->dates);

    free(__routing);
}



unsigned int routing_get_nb_sites(routing __routing)
{
    return __routing->nb_sites;
}



void routing_set_departure_date(routing __routing, unsigned int value)
{
    __routing->dates[0] = value;
}

unsigned int routing_get_departure_date(routing __routing)
{
    return __routing->dates[0];
}



void routing_insert_site(routing __routing, site site_to_insert)
{
    __routing->dates[__routing->current_position] = __routing->dates[__routing->current_position - 1] + site_get_travelling_time(__routing->previous_site, site_get_id(site_to_insert));
    ++(__routing->current_position);
    if(__routing->current_position <= __routing->nb_sites) // Tous les sites n'ont pas encore été visités
    {
        __routing->previous_site = site_to_insert;
    }
    else // Tous les sites ont été visités : il faut revenir à l'usine
    {
        __routing->dates[__routing->current_position] = __routing->dates[__routing->current_position - 1] + site_get_travelling_time(site_to_insert, SITE_ID_FACTORY);
        __routing->previous_site = NULL;
    }
}



unsigned int routing_get_current_position(routing __routing)
{
    return __routing->current_position;
}



site routing_get_previous_site(routing __routing)
{
    return __routing->previous_site;
}



unsigned int routing_get_arrival_date(routing __routing)
{
    return __routing->dates[__routing->nb_sites + 1];
}



unsigned int routing_get_delivery_date(routing __routing, unsigned int position)
{
    return __routing->dates[position];
}
