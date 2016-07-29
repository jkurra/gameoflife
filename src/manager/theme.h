#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "json/file.h"
#include "log.h"

/** @brief
 *
 */
typedef struct
{
    /** @brief path to currently selected configuration.
     *
     */
    char *sel_path;

    /** @brief path to currently selected configuration.
     *
     */
    char *sel_name;

    /** @brief path to currently selected configuration.
     *
     */
    char *dir_path;

    /** @brief path to currently selected configuration.
     *
     */
    char **dir_list;

    /** @brief path to currently selected configuration.
     *
     */
    int    dir_size;

} theme;

/** @brief path to currently selected configuration.
 *
 */
theme *theme_new( char *path );

/** @brief path to currently selected configuration.
 *
 */
void theme_free( theme *t );

/** @brief path to currently selected configuration.
 *
 */
void theme_update( theme *t );

/** @brief path to currently selected configuration.
 *
 */
void theme_select( theme *t, char *name );
/** @brief path to currently selected configuration.
 *
 */
void theme_list( theme *t );


#endif
