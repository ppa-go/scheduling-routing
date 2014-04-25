/*! @file input.h @brief Permet de lire des objets de type @ref instance à partir d'un fichier texte */

#ifndef INPUT_H
#define INPUT_H

#include "instance.h"

/*! Cette macro indique que la lecture d'une instance a réussi.
 *
 * Lorsque @ref read_instance() renvoie cette valeur, cela signifie que le fichier a été correctement ouvert, et que la syntaxe du fichier est correcte.
 * @see read_instance()
 */
#define INPUT_SUCCESS 0
/*! Cette macro indique que la lecture d'une instance a échoué.
 *
 * Lorsque @ref read_instance() renvoie cette valeur, cela signifie que le fichier n'a pas été correctement ouvert.
 * @see read_instance()
 */
#define INPUT_ERROR_OPEN 1
/*! Cette macro indique que la lecture d'une instance a échoué.
 *
 * Lorsque @ref read_instance() renvoie cette valeur, cela signifie que le fichier a été correctement ouvert, mais que la syntaxe du fichier n'est pas correcte.
 * @see read_instance()
 */
#define INPUT_ERROR_SYNTAX 2

/*! Fonction qui lit les données d'une instance dans un fichier et les écrit dans un objet en mémoire
 * @param[out] __instance L'instance dans laquelle stocker les données
 * @param[in] filename Le nom du fichier contenant l'instance à lire
 * @return @ref INPUT_SUCCESS ou @ref INPUT_ERROR_OPEN ou @ref INPUT_ERROR_SYNTAX
 */
int read_instance(instance * __instance, const char * filename);

#endif // INPUT_H
