/*! @file calculate_tardiness.h @brief Fournit une fonction qui calcule le retard accumulé pour un groupe : @ref calculate_tardiness() */

#ifndef CALCULATE_TARDINESS_H
#define CALCULATE_TARDINESS_H

#include "flowshop.h"
#include "routing.h"

/*! Fonction qui calcule le retard accumulé pour un groupe
 * @pre Tous les paramètres sont associés à un même groupe.
 * @param fs Un flowshop
 * @param jobs Un tableau de jobs
 * @pre @ref neh() a été appelée avec le couple (@em fs, @em jobs).
 * @param r Un routing
 * @param sites Un tableau de sites
 * @pre @ref nearest_neighbor() a été appelée avec le couple (@em r, @em sites).
 * @return Le retard accumulé par ce groupe
 */
unsigned int calculate_tardiness(flowshop fs, job * jobs, routing r, site * sites);

#endif // CALCULATE_TARDINESS_H
