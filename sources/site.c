#include "../headers/site.h"

#include <stdlib.h>



/*! Structure représentant un site
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref site.h.
 * @see site.h
 */
struct site
{
    unsigned int id; //!< L'ID du site
    unsigned int nb_sites; //!< Le nombre de sites dans l'instance à laquelle le site appartient
    unsigned int * travelling_times; //!< Un tableau dynamique dans lequel sont stockées les durées de voyage
};



site site_new(unsigned int id, unsigned int nb_sites)
{
    site new_site = (site) malloc(sizeof(struct site));

    new_site->id = id;
    new_site->nb_sites = nb_sites;
    new_site->travelling_times = (unsigned int *) calloc(nb_sites + 1, sizeof(unsigned int));

    return new_site;
}

void site_delete(site __site)
{
    free(__site->travelling_times);

    free(__site);
}



unsigned int site_get_id(site __site)
{
    return __site->id;
}

unsigned int site_get_nb_sites(site __site)
{
    return __site->nb_sites;
}



void site_set_travelling_time(site __site, unsigned int id_other_site, unsigned int value)
{
    __site->travelling_times[id_other_site] = value;
}



unsigned int site_get_travelling_time(site __site, unsigned int id_other_site)
{
    return __site->travelling_times[id_other_site];
}
