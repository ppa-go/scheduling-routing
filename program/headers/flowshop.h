/*! @file flowshop.h @brief Permet de manipuler des objets de type @ref flowshop pour gérer les problématiques d'ordonnancement */

#ifndef FLOWSHOP_H
#define FLOWSHOP_H

#include "job.h"

typedef struct flowshop * flowshop;

/*! Fonction qui crée un nouveau flowshop
 * @param nb_machines Le nombre de machines dans l'instance à laquelle le flowshop est associé
 * @param nb_jobs Le nombre de jobs dans le groupe à ordonnancer
 * @return Un nouveau flowshop
 * @warning Après utilisation, libérer les ressources en appelant : @ref flowshop_delete()
 * @note La date de disponibilité au plus tôt pour chaque machine est : <em>t = 0</em>
 * @see flowshop_set_availability_date()
 * @post La position courante d'insertion de jobs est égale à 1. (aucun job inséré)
 * @see flowshop_get_current_position()
 */
flowshop flowshop_new(unsigned int nb_machines, unsigned int nb_jobs);
/*! Fonction qui libère les ressources utilisées par un flowshop
 * @param __flowshop Le flowshop à supprimer
 * @note Les ressources utilisées par le flowshop sont libérées.
 */
void flowshop_delete(flowshop __flowshop);

/*! Fonction qui retourne le nombre de machines dans l'instance à laquelle le flowshop est associé
 * @param __flowshop Un flowshop
 * @return Le nombre de machines dans l'instance à laquelle le flowshop est associé
 */
unsigned int flowshop_get_nb_machines(flowshop __flowshop);
/*! Fonction qui retourne le nombre de jobs dans le groupe à ordonnancer
 * @param __flowshop Un flowshop
 * @return Le nombre de jobs dans le groupe à ordonnancer
 */
unsigned int flowshop_get_nb_jobs(flowshop __flowshop);

/*! Fonction qui permet de modifier une date de disponibilité au plus tôt
 * @param __flowshop Un flowshop
 * @param id_machine L'ID d'une machine
 * @param value La date de disponibilité au plus tôt de la machine
 * @warning Cette fonction ne doit jamais être appelée après avoir inséré un job avec @ref flowshop_insert_job() !
 * @see flowshop_get_availability_date()
 */
void flowshop_set_availability_date(flowshop __flowshop, unsigned int id_machine, unsigned int value);
/*! Fonction qui retourne une date de disponibilité au plus tôt
 * @param __flowshop Un flowshop
 * @param id_machine L'ID d'une machine
 * @return La date de disponibilité au plus tôt de la machine
 * @see flowshop_set_availability_date()
 */
unsigned int flowshop_get_availability_date(flowshop __flowshop, unsigned int id_machine);

/*! Fonction qui permet d'insérer un job à la position courante dans un ordonnancement
 * @param __flowshop Un flowshop
 * @param job_to_insert Le job à placer à la position courante dans l'ordonnancement
 * @post Les dates de fin de fabrication du job inséré à la position courante sont calculées pour toutes les machines.
 * @post La position courante d'insertion de job est augmentée de 1.
 * @note Pour spécifier les dates de disponibilité au plus tôt d'une ou plusieurs machines, utiliser au préalable : @ref flowshop_set_availability_date()
 * @warning Cette fonction doit être appelée exactement <em>flowshop_get_nb_jobs(__flowshop)</em> fois !
 * @warning Pas de retour en arrière : l'insertion d'un job est définitive ! (Ne peut pas être annulée)
 * @see flowshop_get_current_position()
 */
void flowshop_insert_job(flowshop __flowshop, job job_to_insert);

/*! Fonction qui retourne la position courante pour l'insertion d'un job
 * @param __flowshop Un flowshop
 * @return La position courante pour l'insertion d'un job, utilisée par @ref flowshop_insert_job()
 */
unsigned int flowshop_get_current_position(flowshop __flowshop);

/*! Fonction qui retourne la durée totale d'un flowshop
 * @param __flowshop Un flowshop
 * @return La durée totale du flowshop : de la date de disponibilité au plus tôt de la première machine, jusqu'à la date de fin de fabrication du dernier job sur la dernière machine.
 * @warning Pour pouvoir utiliser cette fonction, tous les jobs doivent avoir été insérés au préalable : <tt> @ref flowshop_get_current_position (__flowshop) > @ref flowshop_get_nb_jobs (__flowshop)</tt>
 * @see flowshop_insert_job()
 */
unsigned int flowshop_get_duration(flowshop __flowshop);

/*! Fonction qui retourne une date de fin de fabrication
 * @param __flowshop Un flowshop
 * @param id_machine L'ID d'une machine
 * @param position Une position dans l'ordonnancement
 * @return La date de fin de fabrication du job (identifié par sa position) sur la machine (identifiée par son ID).
 * @warning Pour pouvoir utiliser cette fonction, tous les jobs doivent avoir été insérés au préalable : <tt> @ref flowshop_get_current_position (__flowshop) > @ref flowshop_get_nb_jobs (__flowshop)</tt>
 * @see flowshop_insert_job()
 */
unsigned int flowshop_get_date(flowshop __flowshop, unsigned int id_machine, unsigned int position);

#endif // FLOWSHOP_H
