/*! @file chrono.h @brief Permet de manipuler des objets de type @ref chrono */

#ifndef CHRONO_H
#define CHRONO_H

typedef struct chrono * chrono;

/*! Fonction qui crée un nouveau chronomètre
 * @return Un nouveau chronomètre
 * @warning Après utilisation, libérer les ressources en appelant : @ref chrono_delete()
 */
chrono chrono_new();
/*! Fonction qui libère les ressources utilisées par un chronomètre
 * @param __chrono Le chronomètre à supprimer
 * @note Les ressources utilisées par le chronomètre sont libérées.
 */
void chrono_delete(chrono __chrono);

/*! Fonction qui démarre un chronomètre
 * @param __chrono Un chronomètre
 * @post Le chronomètre est démarré.
 */
void chrono_start(chrono __chrono);
/*! Fonction qui arrête un chronomètre
 * @param __chrono Un chronomètre
 * @pre Le chronomètre a été préalablement démarré en appelant : @ref chrono_start()
 * @post Le chronomètre est arrêté.
 * @note Le chronomètre qui vient d'être arrêté peut être réutilisé en appelant de nouveau : @ref chrono_start()
 */
void chrono_stop(chrono __chrono);

/*! Fonction qui retourne le temps mesuré par un chronomètre
 * @param __chrono Un chronomètre
 * @pre Le chronomètre a d'abord été démarré en appelant : @ref chrono_start()
 * @pre Le chronomètre a ensuite été arrêté en appelant : @ref chrono_stop()
 * @return Le temps mesuré par le chronomètre, en millisecondes (ms).
 */
unsigned int chrono_get_time(chrono __chrono);

#endif // CHRONO_H
