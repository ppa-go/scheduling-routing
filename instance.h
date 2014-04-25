/*! @file instance.h @brief Permet de manipuler des objets de type @ref instance */

#ifndef INSTANCE_H
#define INSTANCE_H

#include "job.h"
#include "site.h"

typedef struct instance * instance;

/*! Fonction qui crée une nouvelle instance
 * @param nb_machines Le nombre de machines dans l'instance à créer
 * @param nb_jobs Le nombre de jobs dans l'instance à créer
 * @param nb_sites Le nombre de sites dans l'instance à créer
 * @return Une nouvelle instance
 * @warning Après utilisation, libérer les ressources en appelant : \ref instance_delete()
 */
instance instance_new(unsigned int nb_machines, unsigned int nb_jobs, unsigned int nb_sites);
/*! Fonction qui libère les ressources utilisées par une instance
 * @param __instance L'instance à supprimer
 * @note Les ressources utilisées par l'instance sont libérées.
 */
void instance_delete(instance __instance);

/*! Fonction qui retourne le nombre de machines dans une instance
 * @param __instance Une instance
 * @return Le nombre de machines dans l'instance
 */
unsigned int instance_get_nb_machines(instance __instance);
/*! Fonction qui retourne le nombre de jobs dans une instance
 * @param __instance Une instance
 * @return Le nombre de jobs dans l'instance
 */
unsigned int instance_get_nb_jobs(instance __instance);
/*! Fonction qui retourne le nombre de sites dans une instance
 * @param __instance Une instance
 * @return Le nombre de sites dans l'instance
 */
unsigned int instance_get_nb_sites(instance __instance);

/*! Fonction qui extrait un job d'une instance
 * @param __instance Une instance
 * @param id_job L'ID du job à extraire
 * @return Le job dont l'ID correspond au paramètre @em id_job.
 * @warning Toute modification sur le job retourné affecte également l'instance.
 */
job instance_extract_job(instance __instance, unsigned int id_job);
/*! Fonction qui extrait un site d'une instance
 * @param __instance Une instance
 * @param id_site L'ID du site à extraire
 * @return Le site dont l'ID correspond au paramètre @em id_site.
 * @warning Toute modification sur le site retourné affecte également l'instance.
 */
site instance_extract_site(instance __instance, unsigned int id_site);

/* Fonctions utiles pour manipuler des jobs, sans avoir à les extraire d'une instance */

/*! Fonction qui permet de modifier une durée de fabrication
 * @param __instance Une instance
 * @param id_machine L'ID d'une machine
 * @param id_job L'ID d'un job
 * @param value La durée de fabrication du job sur la machine
 * @see instance_get_processing_time()
 */
void instance_set_processing_time(instance __instance, unsigned int id_machine, unsigned int id_job, unsigned int value);
/*! Fonction qui permet de modifier une date due
 * @param __instance Une instance
 * @param id_job L'ID d'un job
 * @param value La date due du job
 * @see instance_get_due_date()
 */
void instance_set_due_date(instance __instance, unsigned int id_job, unsigned int value);
/*! Fonction qui permet de modifier un site de livraison
 * @param __instance Une instance
 * @param id_job L'ID d'un job
 * @param value L'ID du site de livraison du job
 * @see instance_get_id_delivery_site()
 */
void instance_set_id_delivery_site(instance __instance, unsigned int id_job, unsigned int value);

/*! Fonction qui retourne une durée de fabrication
 * @param __instance Une instance
 * @param id_machine L'ID d'une machine
 * @param id_job L'ID d'un job
 * @return La durée de fabrication du job sur la machine
 * @see instance_set_processing_time()
 */
unsigned int instance_get_processing_time(instance __instance, unsigned int id_machine, unsigned int id_job);
/*! Fonction qui retourne la somme des durées de fabrication
 * @param __instance Une instance
 * @param id_job L'ID d'un job
 * @return La somme des durées de fabrication du job
 * @note La complexité de cette fonction est en @em O(1). (coût constant)
 */
unsigned int instance_get_sum_processing_times(instance __instance, unsigned int id_job);
/*! Fonction qui retourne une date due
 * @param __instance Une instance
 * @param id_job L'ID d'un job
 * @return La date due du job
 * @see instance_set_due_date()
 */
unsigned int instance_get_due_date(instance __instance, unsigned int id_job);
/*! Fonction qui retourne un site de livraison
 * @param __instance Une instance
 * @param id_job L'ID d'un job
 * @return L'ID du site de livraison du job
 * @see instance_get_id_delivery_site()
 */
unsigned int instance_get_id_delivery_site(instance __instance, unsigned int id_job);

/* Fonctions utiles pour manipuler des sites, sans avoir à les extraire d'une instance */

/*! Fonction qui permet de modifier une durée de voyage
 * @param __instance Une instance
 * @param id_first_site L'ID du site de départ
 * @param id_second_site L'ID du site d'arrivée
 * @param value La durée de voyage du site de départ au site d'arrivée
 * @see instance_get_travelling_time()
 */
void instance_set_travelling_time(instance __instance, unsigned int id_first_site, unsigned int id_second_site, unsigned int value);

/*! Fonction qui retourne une durée de voyage
 * @param __instance Une instance
 * @param id_first_site L'ID du site de départ
 * @param id_second_site L'ID du site d'arrivée
 * @return La durée de voyage du site de départ au site d'arrivée
 * @see instance_set_travelling_time()
 */
unsigned int instance_get_travelling_time(instance __instance, unsigned int id_first_site, unsigned int id_second_site);

#endif // INSTANCE_H
