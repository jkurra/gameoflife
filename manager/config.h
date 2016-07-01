#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "../mvc/view.h"
#include "file.h"
#include "json/json.h"

/** @brief Configuration structure for manipulating configurations.
 *
 */
typedef struct
{
    /** @brief Location of the configuration directory.
     *
     */
    char *path_dir;

    /** @brief path to currently selected configuration.
     *
     */
    char *path_sel;

    /** @brief Name of the currently selected configuration.
     *
     */
    char *name_sel;

    /** @brief List of filenames within current directory.
     *
     */
    char **d_list;

    /** @brief Size of filename d_list.
     *
     */
    int    d_size;

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


void config_write( commons_model *model, config *c);

/**
 *
 */
char *config_path( config *c );
void config_update( config *c, const char *path );
void config_list( config *conf );
void config_read( commons_model *model, config *c );

#endif /* CONFIG_H_INCLUDED */
