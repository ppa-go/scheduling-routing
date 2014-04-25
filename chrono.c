#include "chrono.h"

#include <stdlib.h>
#include <time.h>



/*! Structure représentant un chronomètre
 * @warning Ne jamais modifier ou accéder à un tel objet directement ! Utiliser les fonctions fournies dans @ref chrono.h.
 * @see chrono.h
 */
struct chrono
{
    clock_t start; //!< Le nombre de coups d'horloge au moment où @ref chrono_start() est appelée
    clock_t stop; //!< Le nombre de coups d'horloge au moment où @ref chrono_stop() est appelée
};



chrono chrono_new()
{
    return (chrono) malloc(sizeof(struct chrono));
}

void chrono_delete(chrono __chrono)
{
    free(__chrono);
}



void chrono_start(chrono __chrono)
{
    __chrono->start = clock();
}

void chrono_stop(chrono __chrono)
{
    __chrono->stop = clock();
}



unsigned int chrono_get_time(chrono __chrono)
{
    return 1000 * (__chrono->stop - __chrono->start) / CLOCKS_PER_SEC;
}
