#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "json/json.h"
#include "json/file.h"
#include "log.h"

/** @brief Configuration structure for manipulating configurations.
 *
 */
typedef struct
{

    /** @brief path to currently selected configuration.
     *
     */
    char *sel_path;

    /** @brief Name of the currently selected configuration.
     *
     */
    char *sel_name;

    /** @brief Location of the configuration directory.
     *
     */
    char *dir_path;

    /** @brief List of filenames within current directory.
     *
     */
    char **dir_list;

    /** @brief Size of filename d_list.
     *
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
 */
void config_free( config *c );

/** @brief Free current configuration and its parts.
 *
 */
void config_list( config *conf );

/** @brief Select a configuration from current directory.
 *
 *  This function is used for changing the configuration easily and safely. Each
 *  time select() is called, old selection is freed and new allocated. This removes
 *  need for manipulating data in structure directly.
 *
 * @param c     configuration to be used for change.
 * @param name  Configuration name to be used.
 */
void config_select( config *c, const char *name );

/**
 *
 */
char *config_path( config *c );

#endif /* CONFIG_H_INCLUDED */
