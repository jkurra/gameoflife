#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "manager.h"
#include "../output/log.h"

/** @brief Allocates new manager from given path.
 *
 *  Allocates space for a new theme manager and initializes it with NULL values.
 *  Path is assigned so that update may be called.
 *  Must be deallocated with config_free.
 *
 * @param path  Path to be used as root directory of the theme.
 * @return      Dynamically allocated theme manager.
 */
Manager *theme_new( const char *path );

/** @brief Returns dynamically allocated theme.
 *
 *  Calls free() for each dynamically allocated variable within configuration.
 *  Checks if variable is NULL before attempting to free it. Because of this it
 *  is recommended to only use config_new to create new configuration-managers
 *  and other function provide by config. This ensures proper memory management
 *  with each context.
 *
 * @param theme dynamically allocated theme to be freed.
 */
void theme_free( Manager *theme );

/** @brief Changes current theme if available.
 *
 *  This function is used for changing the Theme easily and safely. Each
 *  time select() is called, old selection is freed and new allocated. This removes
 *  need for manipulating data in structure directly. If directory named "name"
 *  is not found within manager, old theme is kept.
 *
 * @param conf  Theme object as Manager to be used for the change.
 * @param name  Name of the new theme to find and use.
 */
void theme_select( Manager *theme, char *name );

#endif
