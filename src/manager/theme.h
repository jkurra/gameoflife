#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "json/file.h"

/** @brief
 *
 */
typedef struct
{
    char *sel_path;
    char *sel_name;
    char *dir_path;

    char **dir_list;
    int    dir_size;

} theme;

theme *theme_new( char *path );

void theme_free( theme *t );

void theme_update( theme *t );

void theme_select( theme *t, char *name );
void theme_list( theme *t );

void thememng_select( const char * name );

void thememng_list( const char *path );

#endif
