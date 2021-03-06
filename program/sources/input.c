#include "../headers/input.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*! Fonction auxiliaire qui lit un entier au début d'une chaîne de caractères et décale le début de cette chaîne de caractères
 * @param[in,out] line Un pointeur vers la chaîne de caractères à parser
 * @param[out] result Un pointeur vers un entier où stocker la valeur positive entière contenue au début de @em *line
 * @pre @em line ne doit pas être @em NULL.
 * @pre @em result ne doit pas être @em NULL.
 * @return @b true <em>(valeur non nulle)</em> si la chaîne de caractères commence par un chiffre (la lecture a réussi), @b false <em>(valeur nulle)</em> sinon (la lecture a échoué)
 * @post Si la fonction retourne @b true, alors :
 *      @li @em *line pointe sur la prochaine valeur (si elle existe) dans la chaîne, en sautant un (ou plusieurs) caractère(s) de séparation.
 *      @li @em *result est égal à la valeur positive entière contenue au début de la chaîne ;
 * @post Si la fonction retourne @b false, alors :
 *      @li @em *line reste inchangé.
 *      @li @em *result reste inchangé ;
 * @note Un caractère de séparation est un caractère non nul (@tt '\0') qui n'est pas un chiffre.
 */
int get_first_number(const char ** line, unsigned int * result);

/*! Fonction auxiliaire qui lit une ligne dans un fichier
 * @param[in,out] line Un pointeur vers une chaîne de caractères
 * @pre @em line ne doit pas être @em NULL.
 * @pre Lors du premier appel à cette fonction (lecture de la première ligne de @em file), utiliser un pointeur vers une chaîne @em NULL.
 * @param[in] file Un fichier dont le contenu est à extraire ligne par ligne
 * @return @b true <em>(valeur non nulle)</em> si une ligne de @em file a pu être lue (la lecture a réussi), @b false <em>(valeur nulle)</em> sinon (la lecture a échoué)
 * @post @em line pointe vers une chaîne de caractères représentant une ligne de @em file.
 * @note Plusieurs appels successifs à cette fonction permettent de lire successivement les lignes de @em file.
 * @warning Après avoir fini de lire le fichier @em file, libérer les ressources utilisées par @em *line en appelant : @b free()
 * @note Le comportement de cette fonction est analogue à celui de la fonction : @b getline()
 */
int read_one_line(char ** line, FILE * file);



int read_instance(instance * __instance, const char * filename)
{
    char * read_one_line_ptr = NULL;
    const char * line;
    unsigned int nb_machines, nb_jobs_sites, id_machine, id_job, id_first_site, id_second_site, value;
    instance data;

    /* Ouverture du fichier */
    FILE * file = fopen(filename, "r");
    if(file == NULL) { return INPUT_ERROR_OPEN; }

    /* Lecture de la première ligne de l'instance : nombre de machines, nombre de jobs == nombre de sites */
    if(!read_one_line(&read_one_line_ptr, file)) { free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
    line = read_one_line_ptr;
    if(!get_first_number(&line, &nb_machines)) { free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
    if(!get_first_number(&line, &nb_jobs_sites)) { free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }

    /* Initialisation de l'instance */
    data = instance_new(nb_machines, nb_jobs_sites, nb_jobs_sites);
    for(id_job = 1; id_job <= nb_jobs_sites; ++id_job)
    {
        instance_set_id_delivery_site(data, id_job, id_job); // 1 job == 1 site
    }

    /* Lecture des durées de fabrication */
    for(id_machine = 1; id_machine <= nb_machines; ++id_machine)
    {
        if(!read_one_line(&read_one_line_ptr, file)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
        line = read_one_line_ptr;
        for(id_job = 1; id_job <= nb_jobs_sites; ++id_job)
        {
            if(!get_first_number(&line, &value)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
            instance_set_processing_time(data, id_machine, id_job, value);
        }
    }

    /* Lecture des dates dues */
    if(!read_one_line(&read_one_line_ptr, file)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
    line = read_one_line_ptr;
    for(id_job = 1; id_job <= nb_jobs_sites; ++id_job)
    {
        if(!get_first_number(&line, &value)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
        instance_set_due_date(data, id_job, value);
    }

    /* Lecture des durées de voyage */
    for(id_first_site = 0; id_first_site <= nb_jobs_sites; ++id_first_site)
    {
        if(!read_one_line(&read_one_line_ptr, file)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
        line = read_one_line_ptr;
        for(id_second_site = 0; id_second_site <= nb_jobs_sites; ++id_second_site)
        {
            if(!get_first_number(&line, &value)) { instance_delete(data); free(read_one_line_ptr); fclose(file); return INPUT_ERROR_SYNTAX; }
            instance_set_travelling_time(data, id_first_site, id_second_site, value);
        }
    }

    /* Finalisation de la lecture */
    *__instance = data;
    free(read_one_line_ptr);
    fclose(file);

    return INPUT_SUCCESS;
}

int get_first_number(const char ** line, unsigned int * result)
{
    const char * current_char_ptr;

    /* La chaîne de caractère doit commencer par un chiffre. */
    if(!(('0' <= **line) && (**line <= '9'))) { return 0; }

    /* La chaine est parsée, jusqu'à ce qu'un séparateur (un caractère qui n'est pas un chiffre) soit trouvé. */
    *result = 0;
    for(current_char_ptr = *line; ('0' <= *current_char_ptr) && (*current_char_ptr <= '9'); ++current_char_ptr)
    {
        *result = *result * 10 + (unsigned int) (*current_char_ptr - '0');
    }

    /* On fait en sorte que *line pointe sur la prochaine valeur, si elle existe. */
    while((*current_char_ptr != '\0') && (!(('0' <= *current_char_ptr) && (*current_char_ptr <= '9')))) { ++current_char_ptr; }
    *line = current_char_ptr;

    return 1;
}

/*! Cette macro définit la taille du buffer utilisé par la fonction @ref read_one_line() */
#define READ_ONE_LINE_BUFFER_LEN 1024

int read_one_line(char ** line, FILE * file)
{
    char buffer[READ_ONE_LINE_BUFFER_LEN],
         * temp;

    free(*line);
    *line = strdup("");
    do
    {
        if(fgets(buffer, READ_ONE_LINE_BUFFER_LEN, file) == NULL) { free(*line); return 0; }
        if((temp = (char *) realloc(*line, (strlen(*line) + READ_ONE_LINE_BUFFER_LEN) * sizeof(char))) == NULL) { free(*line); return 0; }
        *line = strcat(temp, buffer);
    }
    while(buffer[strlen(buffer) - 1] != '\n');

    return 1;
}
