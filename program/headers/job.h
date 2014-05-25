/*! @file job.h @brief Permet de manipuler des objets de type @ref job */

#ifndef JOB_H
#define JOB_H

/*! Cette macro définit la valeur par défaut de la date due, utilisée par @ref job_new(). */
#define JOB_DEFAULT_VALUE_DUE_DATE 0
/*! Cette macro définit la valeur par défaut de l'ID du site de livraison, utilisée par @ref job_new(). */
#define JOB_DEFAULT_VALUE_ID_DELIVERY_SITE 1

typedef struct job * job;

/*! Fonction qui crée un nouveau job
 * @param id L'ID du job
 * @param nb_machines Le nombre de machines dans l'instance à laquelle le job appartient
 * @return Un nouveau job
 * @warning Après utilisation, libérer les ressources en appelant : @ref job_delete()
 */
job job_new(unsigned int id, unsigned int nb_machines);
/*! Fonction qui libère les ressources utilisées par un job
 * @param __job Le job à supprimer
 * @note Les ressources utilisées par le job sont libérées.
 */
void job_delete(job __job);

/*! Fonction qui retourne l'ID d'un job
 * @param __job Un job
 * @return L'ID du job
 */
unsigned int job_get_id(job __job);
/*! Fonction qui retourne le nombre de machines dans l'instance à laquelle un job appartient
 * @param __job Un job
 * @return Le nombre de machines dans l'instance à laquelle le job appartient
 */
unsigned int job_get_nb_machines(job __job);

/*! Fonction qui permet de modifier une durée de fabrication
 * @param __job Un job
 * @param id_machine L'ID d'une machine
 * @param value La durée de fabrication du job sur la machine
 * @see job_get_processing_time()
 */
void job_set_processing_time(job __job, unsigned int id_machine, unsigned int value);
/*! Fonction qui permet de modifier une date due
 * @param __job Un job
 * @param value La date due du job
 * @see job_get_due_date()
 */
void job_set_due_date(job __job, unsigned int value);
/*! Fonction qui permet de modifier un site de livraison
 * @param __job Un job
 * @param value L'ID du site de livraison du job
 * @see job_get_id_delivery_site()
 */
void job_set_id_delivery_site(job __job, unsigned int value);

/*! Fonction qui retourne une durée de fabrication
 * @param __job Un job
 * @param id_machine L'ID d'une machine
 * @return La durée de fabrication du job sur la machine
 * @see job_set_processing_time()
 */
unsigned int job_get_processing_time(job __job, unsigned int id_machine);
/*! Fonction qui retourne la somme des durées de fabrication
 * @param __job Un job
 * @return La somme des durées de fabrication du job
 * @note La complexité de cette fonction est en @em O(1). (coût constant)
 */
unsigned int job_get_sum_processing_times(job __job);
/*! Fonction qui retourne une date due
 * @param __job Un job
 * @return La date due du job
 * @see job_set_due_date()
 */
unsigned int job_get_due_date(job __job);
/*! Fonction qui retourne un site de livraison
 * @param __job Un job
 * @return L'ID du site de livraison du job
 * @see job_set_id_delivery_site()
 */
unsigned int job_get_id_delivery_site(job __job);

#endif // JOB_H
