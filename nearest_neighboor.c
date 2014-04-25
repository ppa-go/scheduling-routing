#include "nearest_neighboor.h"

#include "sort.h"



void nearest_neighboor(routing r, site * sites)
{
    const unsigned int n = routing_get_nb_sites(r);
    unsigned int position,
                 index, distance,
                 best_index, min_distance;
    site previous_site;

    /* Pour chaque position */
    for(position = 0; position < n; ++position)
    {
        /* Recherche du site le plus proche du site précédemment visité */
        previous_site = routing_get_previous_site(r);

        best_index = position;
        min_distance = site_get_travelling_time(previous_site, site_get_id(sites[best_index]));

        for(index = position + 1; index < n; ++index)
        {
            distance = site_get_travelling_time(previous_site, site_get_id(sites[best_index]));

            if(distance < min_distance)
            {
                best_index = index;
                min_distance = distance;
            }
        }

        /* Insertion du site trouvé à la position actuelle */
        routing_insert_site(r, sites[best_index]);

        /* Mise à jour de 'sites' */
        swap((void **) sites, position, best_index);
    }
}
