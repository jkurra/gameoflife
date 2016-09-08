#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "manager.h"
#include "json/file.h"
#include "log.h"

/** @brief Creates newly allocated theme.
 *
 */
Manager *theme_new( const char *path );

/** @brief Returns dynamically allocated theme.
 *
 */
void theme_free( Manager *th );

/** @brief Updates current values in theme.
 *
 */
void theme_update( Manager *th );

/** @brief Changes current theme if available.
 *
 */
void theme_select( Manager *th, char *name );

#endif
