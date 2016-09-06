#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "json/file.h"
#include "json/json.h"
#include "log.h"

/** @brief Configuration structure for manipulating configurations.
 *
 */
typedef struct
{

    /** @brief path to currently selected configuration.
     *
     *  Points to currently selected configuration path. Path presents
     *  physical location of the file containing json configuration for
     *  the program. Name of the file is also considered name of the
     *  configuration, for example "test.conf" would be called "test" when
     *  selecting the file.
     */
    char *sel_path;

    /** @brief Name of the currently selected configuration.
     *
     *  Points to name of the currently selected configuration. Name is
     *  the filename without extension and filepath. This is separated
     *  from sel_path since it is often necessary to know the name of the
     *  configuration.
     */
    char *sel_name;

    /** @brief Location of the configuration directory.
     *
     *  Points to the location of the file that may contain many configuration
     *  files. Basically root-directory of the configuration. If updated,
     *  invalidates all other variables.
     */
    char *dir_path;

    /** @brief List of filenames within current directory.
     *
     *  Contains all files that can be found within directory pointed by dir_path.
     *  Used to search filenames within root-directory. Only contains files,
     *  directories are ignored since config doesn't support recursive
     *  directories.
     */
    char **dir_list;

    /** @brief Size of filename dir_list.
     *
     *  Count of files within directory. Used to quickly determine size of dir_list
     *  since it is not possible in c. Must be updated each time dir_list is
     *  updated.
     */
    int    dir_size;

} config;

/** @brief Initialize new configuration from path.
 *
 *  Allocates space for a new configuration and initializes it with NULL values.
 *  Path is assigned so that config_update may be called.
 *  Must be deallocated with config_free.
 *
 * @param path  Path to be used as root directory of the configuration.
 * @return      Fresh dynamically allocated configuration.
 */
config *config_new( char *path );

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
void config_free( config *conf );

/** @brief Select a configuration from current directory.
 *
 *  This function is used for changing the configuration easily and safely. Each
 *  time select() is called, old selection is freed and new allocated. This removes
 *  need for manipulating data in structure directly.
 *
 * @param conf  Configuration to be used for change.
 * @param name  Configuration name to be used.
 */
void config_select( config *conf, const char *name );

/** @brief Updates configuration file list.
 *
 *  Uses variables in configuration to update currently existing files within
 *  /config file.
 *
 * @param conf Configuration to be updated.
 */
void config_list( config *conf );

/**
 *
 */
char *config_path( config *c );

#endif /* CONFIG_H_INCLUDED */
