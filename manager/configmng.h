#ifndef CONFIGMNG_H_INCLUDED
#define CONFIGMNG_H_INCLUDED

#include <dirent.h>
#include <string.h>

#include "../mvc/view.h"
#include "file.h"

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
 *  Must be deallocated with config_free.
 *
 */
config *config_new( char *path );

/** @brief Free current configuration and its parts.
 *
 */
void config_free( config *c);

/** @brief Select a configuration from current directory.
 *
 */
void config_select( config *c, const char *name );

/** @brief Update file list in current directory.
 *
 *
void config_update( config *c );

/**
 *
 */
char *config_path( config *c );
void config_update( config *c, const char *path );
char *config_list( config *conf );
void config_read( commons_model *model, config *c );

#endif /* CONFIGMNG_H_INCLUDED */
