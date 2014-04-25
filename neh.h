/*! @file neh.h @brief Fournit une implémentation de l'algorithme de NEH : @ref neh() */

#ifndef NEH_H
#define NEH_H

#include "flowshop.h"

/*! Implémentation de l'algorithme de NEH
 * @param[in,out] fs Un flowshop
 * @param[in,out] jobs Un tableau de jobs à ordonnancer
 * @pre Le tableau @em jobs contient exactement <em>flowshop_get_nb_jobs(fs)</em> jobs.
 * @pre Chaque job du tableau @em jobs vérifie : <tt>job_get_nb_machines(__job) == flowshop_get_nb_machines(fs)</tt>
 * @pre @ref flowshop_insert_job() n'a jamais été appelée sur @em fs.
 * @note Si besoin, @em fs a été initialisé avec les dates de disponibilité au plus tôt de chaque machine.
 * @see flowshop_set_availability_date()
 * @post @em fs contient les dates de fin de fabrication de tous les jobs sur toutes les machines.
 * @post @em jobs est trié selon l'ordre de passage défini par l'ordonnancement trouvé.
 * @note @ref neh() insert tous les jobs du tableau @em jobs dans le flowshop @em fs.
 * @see flowshop_get_duration(), flowshop_get_date()
 */
void neh(flowshop fs, job * jobs);

#endif // NEH_H
