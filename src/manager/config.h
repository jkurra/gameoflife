#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "json/file.h"
#include "json/json.h"
#include "manager.h"
#include "../output/log.h"

/** @brief Initialize new configuration from path.
 *
 *  Allocates space for a new configuration and initializes it with NULL values.
 *  Path is assigned so that config_update may be called.
 *  Must be deallocated with config_free.
 *
 * @param path  Path to be used as root directory of the configuration.
 * @return      Fresh dynamically allocated configuration.
 */
Manager *config_new( const char *path );

/** @brief Free current configuration and its parts.
 *
 *  Calls free() for each dynamically allocated variable within configuration.
 *  Checks if variable is NULL before attempting to free it. Because of this it
 *  is recommended to only use config_new to create new configuration-managers
 *  and other function provide by config. This ensures proper memory management
 *  with each context.
 *
 * @param conf  Configuration to be freed.
 */
void config_free( Manager *conf );

/** @brief Select a configuration from current directory.
 *
 *  This function is used for changing the configuration easily and safely. Each
 *  time select() is called, old selection is freed and new allocated. This removes
 *  need for manipulating data in structure directly.
 *
 * @param conf  Configuration to be used for change.
 * @param name  Configuration name to be used.
 */
void config_select( Manager *conf, const char *name );

#endif /* CONFIG_H_INCLUDED */
