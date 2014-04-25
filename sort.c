#include "sort.h"



/*! Fonction récursive qui transforme un "presque-tas" en "tas"
 * @param[in,out] values Un tableau de valeurs représentant un arbre binaire
 * @param[in] length Le nombre d'éléments à considérer dans @em values
 * @param[in] root La racine de l'arbre @em values (indice)
 * @param[in] __comparator Un comparateur qui définit une relation d'ordre pour les éléments à trier
 * @see comparator
 * @pre Le sous-arbre de racine @em root dans @em values est un "presque-tas".
 * @note Un "presque-tas" est un arbre binaire dont les fils gauche et droit de la racine sont des "tas".
 * @post Le sous-arbre de racine @em root dans @em values est un "tas".
 * @note Un "tas" est un arbre binaire tel que : pour tout noeud N, pour tout descendant D de N, étiquette(D) <= étiquette(N)
 */
static void reheap(void ** values, const unsigned int length, const unsigned int root, comparator __comparator)
{
    const unsigned int left  = 2 * root + 1, //  (left + 1) == 2 * (root + 1)
                       right = 2 * root + 2; // (right + 1) == 2 * (root + 1) + 1

    if(right < length) // Le fils gauche et le fils droit existent.
    {
        if(__comparator(values[left], values[right])) // values[left] < values[right]
        {
            if(__comparator(values[root], values[right])) // values[root] < values[right]
            {
                swap(values, root, right);
                reheap(values, length, right, __comparator);
            }
        }
        else // values[right] <= values[left]
        {
            if(__comparator(values[root], values[left])) // values[root] < values[left]
            {
                swap(values, root, left);
                reheap(values, length, left, __comparator);
            }
        }
    }
    else if(left < length) // Seul le fils gauche existe.
    {
        if(__comparator(values[root], values[left])) // values[root] < values[left]
        {
            swap(values, root, left);
            reheap(values, length, left, __comparator);
        }
    }
}



/*! Fonction récursive qui transforme un arbre binaire en "tas"
 * @param[in,out] values Un tableau de valeurs représentant un arbre binaire
 * @param[in] length Le nombre d'éléments à considérer dans @em values
 * @param[in] root La racine de l'arbre @em values (indice)
 * @param[in] __comparator Un comparateur qui définit une relation d'ordre pour les éléments à trier
 * @see comparator
 * @post Le sous-arbre de racine @em root dans @em values est un "tas".
 * @note Un "tas" est un arbre binaire tel que : pour tout noeud N, pour tout descendant D de N, étiquette(D) <= étiquette(N)
 */
static void heap(void ** values, const unsigned int length, const unsigned int root, comparator __comparator)
{
    const unsigned int left  = 2 * root + 1, //  (left + 1) == 2 * (root + 1)
                       right = 2 * root + 2; // (right + 1) == 2 * (root + 1) + 1

    /* L'arbre binaire 'values' de racine 'root' est quelconque. */
    if(left < length) // Le fils gauche existe.
    {
        heap(values, length, left, __comparator);
    }
    if(right < length) // Le fils droit existe.
    {
        heap(values, length, right, __comparator);
    }
    /* L'arbre binaire 'values' de racine 'root' est un "presque-tas". */
    reheap(values, length, root, __comparator);
    /* L'arbre binaire 'values' de racine 'root' est un "tas". */
}



void sort(unsigned int nb_values, void ** values, comparator __comparator)
{
    /* Etape 1 : Tasser, échanger la première valeur (à la racine) et la dernière valeur, décrémenter 'nb_values'. */
    heap(values, nb_values, 0, __comparator);
    swap(values, 0, --nb_values);

    /* Etape 2 : Retasser et extraire les valeurs, jusqu'à ce qu'il y ait un seul élément. ('nb_values' == 1) */
    while(nb_values > 1)
    {
        reheap(values, nb_values, 0, __comparator);
        swap(values, 0, --nb_values);
    }
}



void swap(void ** values, const unsigned int index1, const unsigned int index2)
{
    void * value = values[index1];
    values[index1] = values[index2];
    values[index2] = value;
}
