/*! @file solution.h @brief Permet de manipuler des objets de type @ref solution */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "instance.h"
#include "flowshop.h"
#include "routing.h"

typedef struct solution * solution;

/*! Fonction qui crée une nouvelle solution
 * @param data L'instance associée à la solution à créer
 * @param job_to_group Un tableau associant un groupe à chaque job de @em data.
 * @see group_new()
 * @return Une nouvelle solution
 * @warning Après utilisation, libérer les ressources en appelant : \ref solution_delete()
 */
solution solution_new(instance data, unsigned int * job_to_group);
/*! Fonction qui libère les ressources utilisées par une solution
 * @param __solution La solution à supprimer
 * @note Les ressources utilisées par la solution sont libérées.
 */
void solution_delete(solution __solution);

/*! Fonction qui retourne l'instance à laquelle une solution est associée
 * @param __solution Une solution
 * @return L'instance à laquelle la solution est associée
 */
instance solution_get_data(solution __solution);

/*! Fonction qui retourne le nombre de groupes dans une solution
 * @param __solution Une solution
 * @return Le nombre de groupes de jobs (et de sites) dans la solution
 * @see group_get_nb_groups()
 */
unsigned int solution_get_nb_groups(solution __solution);
/*! Fonction qui retourne le nombre de jobs (et de sites) dans un groupe au sein d'une solution
 * @param __solution Une solution
 * @param id_group L'ID d'un groupe de jobs (ou de sites)
 * @return Le nombre jobs (et de sites) dans le groupe (identifié par son ID) dans la solution
 * @see group_get_nb_elements_in_groups()
 */
unsigned int solution_get_nb_elements_in_group(solution __solution, unsigned int id_group);

/*! Fonction qui retourne les jobs d'un groupe au sein d'une solution
 * @param __solution Une solution
 * @param id_group L'ID d'un groupe de jobs (ou de sites)
 * @return Un tableau contenant les jobs du groupe (identifié par son ID) dans la solution
 * @warning Toute modification sur le tableau de jobs retourné affecte également la solution.
 */
job * solution_get_jobs_in_group(solution __solution, unsigned int id_group);
/*! Fonction qui retourne un flowshop vide associé à un groupe au sein d'une solution
 * @param __solution Une solution
 * @param id_group L'ID d'un groupe de jobs
 * @return Un flowshop vide (aucun job inséré) associé au groupe (identifié par son ID) dans la solution
 * @warning Toute modification sur le flowshop retourné affecte également la solution.
 */
flowshop solution_get_flowshop_for_group(solution __solution, unsigned int id_group);

/*! Fonction qui retourne les sites d'un groupe au sein d'une solution
 * @param __solution Une solution
 * @param id_group L'ID d'un groupe de sites
 * @return Un tableau contenant les sites du groupe (identifié par son ID) dans la solution
 * @warning Toute modification sur le tableau de sites retourné affecte également la solution.
 */
site * solution_get_sites_in_group(solution __solution, unsigned int id_group);
/*! Fonction qui retourne un routing vide associé à un groupe au sein d'une solution
 * @param __solution Une solution
 * @param id_group L'ID d'un groupe de sites
 * @return Un routing vide (aucun site inséré) associé au groupe (identifié par son ID) dans la solution
 * @warning Toute modification sur le routing retourné affecte également la solution.
 */
routing solution_get_routing_for_group(solution __solution, unsigned int id_group);

/*! Fonction qui retourne la somme des retards d'une solution
 * @param __solution Une solution
 * @return La somme des retards de la solution
 * @warning Tous les flowshops et tous les routings (pour chaque groupe de la solution) doivent avoir été remplis au préalable !
 * @see flowshop_insert_job(), routing_insert_site()
 */
unsigned int solution_get_tardiness(solution __solution);

#endif // SOLUTION_H
