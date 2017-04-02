#include "config.h"

/** @brief Updates configuration file list.
 *
 *  Uses variables in configuration to update currently existing files within
 *  /config file.
 *
 * @param conf Configuration to be updated.
 */
void config_list( Manager *conf );

Manager *config_new( const char *path )
{
    /* Allocate space for the configuration structure. */
    Manager *conf = (Manager*)calloc(1, sizeof(Manager));
    conf->dir_path = NULL;
    if(path) {
        int plen = strlen(path); /* Get excact length of the path parameter */
        /*
         *  Set initial values for configuration, path is dynamically allocated
         *  at this point so that user doesn't have to worry about freeing it.
         */
        conf->dir_path = (char*)calloc(plen+1,sizeof(char));
        strncpy(conf->dir_path, path, plen);
    }
    /*
     *  Selection may or may not be found, depending on the root folder.
     *  If it has files, first json file is selected as default.
     */
    conf->sel_path = NULL;
    conf->sel_name = NULL;
    /*
     *  Size and directory list are linked and should NEVER be changed individually.
     *  Only appropriate functions may be used to change or access their values.
     */
    conf->dir_size = -1;
    conf->dir_list = NULL;
    /* Add all files to configuration file list */
    config_list(conf);
    printf("[%s] Config intialized, %d files found.\n", log_timestamp(), conf->dir_size);

    return conf;
}

void config_free( Manager *conf )
{
    if(conf) {
        /*
         * Free saved filenames and members, paranoia checks in case internal
         * variables have been messed with.
         */
        if(conf->dir_list) {
            for(int i=0; i<conf->dir_size; i++) {
                free(conf->dir_list[i]);
                conf->dir_list[i] = NULL;
            }
            conf->dir_size = -1;
            free(conf->dir_list);
            conf ->dir_list = NULL;
        }
        /* Free structure members. */
        if(conf->dir_path) {
            free(conf->dir_path);
            conf->dir_path = NULL;
        }
        if(conf->sel_path) {
            free(conf->sel_path);
            conf->sel_path = NULL;
        }
        if(conf->sel_name) {
            free(conf->sel_name);
            conf->sel_name = NULL;
        }
        free(conf);
        conf = NULL;
    } else { printf("[%s] Attempted config_free() for a NULL pointer. \n", log_timestamp()); }
}

void config_select( Manager *conf, const char *name )
{
    if(conf && name) {
        config_list(conf); /* Update file listing to make sure we are up to date */
        /* Free existing path & name variables from structure if found. */
        if(conf->sel_path) {
            free(conf->sel_path);
            conf->sel_path = NULL;
        }
        if(conf->sel_name) {
            free(conf->sel_name);
            conf->sel_name = NULL;
        }
        int found = 0; /* Variable to tell user if given name was found or not. */
        for(int i=0; i<conf->dir_size; i++) {
            if(strcmp(conf->dir_list[i], name) == 0) {
                /*
                 * Get lenght for found filename and path, and allocate memory.
                 */
                int nlen = strlen(conf->dir_list[i]);
                int plen = strlen(conf->dir_list[i])+strlen(conf->dir_path)+1;

                conf->sel_name = (char*)calloc(nlen+1, sizeof(char));
                conf->sel_path = (char*)calloc(plen+1, sizeof(char));
                /*
                 * Copy filename and path to "currently selected", values of the
                 * structure.
                 */
                strncpy(conf->sel_name, conf->dir_list[i], nlen+1);
                strncpy(conf->sel_path, conf->dir_path, plen+1);
                strcat( conf->sel_path, "/" );
                strcat( conf->sel_path, conf->sel_name );

                found = 1; /* Set found flag for debug message */
                break;
            }
        }
        if(found == 0) { printf("[%s] Configuration with name : %s was not found.\n", log_timestamp(), conf->sel_name); }
        printf("[%s] Configuration selected : %s\n", log_timestamp(), conf->sel_name);

    } else { printf("[%s] config_select Received NULL pointer.\n", log_timestamp());}

}

void d_list_free(Manager *conf)
{
    if(conf->dir_list) {
        for(int i=0; i<conf->dir_size; i++) {
            free(conf->dir_list[i]);
            conf->dir_list[i] = NULL;
        } free(conf->dir_list);
        conf->dir_list = NULL;
    }
}

void config_list( Manager *conf )
{
    /* Free existing list if found. */
    if(conf->dir_list) {
        d_list_free(conf);
    }
    /* Get file count and allocate space for the file list. */
    conf->dir_size = file_count(conf->dir_path, 2);
    conf->dir_list = (char**)calloc(conf->dir_size, sizeof(char*));
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(conf->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            /* Check if file is regular file and add to list. */
            if (ent->d_type == DT_REG) {
                int len = strlen(ent->d_name);
                conf->dir_list[i] = (char*)calloc(len+1, sizeof(char));
                char *arr = conf->dir_list[i] ;
                strncpy(arr, ent->d_name, len+1);
                i++;
            }
        }
        closedir (dir);
    }
}
