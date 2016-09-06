#include "config.h"

config *config_new( char *path )
{
    /* Allocate space for the configuration structure. */
    config *conf = (config*)calloc(1, sizeof(config));

    if(path) {
        int plen = strlen(path); /* Get excact length of the path parameter */
        /*
         *  Set initial values for configuration, path is dynamically allocated
         *  at this point so that user doesn't have to worry about freeing it.
         */
        conf->dir_path = (char*)calloc(plen+1,sizeof(char));
        strncpy(conf->dir_path, path, plen);
        /*
         *  Selection may or may not be found, depending on the root folder.
         *  If it has files, first json file is selected as default
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

    } else { printf("[%s] NULL path provided for configuration \n", log_timestamp()); }

    return conf;
}

void config_free( config *conf )
{
    if(conf) {
        /* Free members */
        if(conf->dir_path) {
            free(conf->dir_path);
        }
        if(conf->sel_path) {
            free(conf->sel_path);
        }
        if(conf->sel_name) {
            free(conf->sel_name);
        }
        /* Free saved filenames */
        for(int i=0; i<conf->dir_size; i++) {
            printf("free: %s\n", conf->dir_list[i]);
            free(conf->dir_list[i]);
        }
        free(conf->dir_list);
    } else {}
}

char *config_path( config *c )
{
    /* Configurations are located at /config/ directory root. */
    size_t lenght = strlen(c->dir_path)+strlen("/config/")+strlen(c->sel_name)+2;
    char *result = (char*)malloc(sizeof(char)*lenght);
    /*  */
    strcpy( result, c->dir_path);
    strcat( result, "/" );
    strcat( result, c->sel_name );

    return result;
}

void config_select( config *conf, const char *name )
{
    if(conf) {
        int found = 0;
        for(int i=0; i<conf->dir_size; i++) {
            if(strcmp(conf->dir_list[i], name) == 0) {
                //printf("found name :%s\n", name);
                if(conf->sel_path) {
                    free(conf->sel_path);
                    conf->sel_path = NULL;
                }
                if(conf->sel_name) {
                    free(conf->sel_name);
                    conf->sel_name = NULL;
                }

                int nlen = strlen(conf->dir_list[i]);
                int plen = strlen(conf->dir_list[i])+strlen(conf->dir_path)+1;

                conf->sel_name = (char*)calloc(nlen+1, sizeof(char));
                conf->sel_path = (char*)calloc(plen+1, sizeof(char));

                //conf->sel_name = conf->dir_list[i];
                strncpy(conf->sel_name, conf->dir_list[i], nlen+1);
                //conf->sel_path = config_path(conf);
                strncpy(conf->sel_path, conf->dir_path, plen+1);
                strcat( conf->sel_path, "/" );
                strcat( conf->sel_path, conf->sel_name );

                found = 1;
                break;
            }
        } if(found == 0) { printf("[CONFIG] Configuration with name : %s was not found.\n", name); }

        printf("[%s] Config selected : %s\n", log_timestamp(), conf->sel_name);

    } else { printf("[%s] Config Received NULL pointer.\n", log_timestamp());}
}

void d_list_free(config *conf)
{
    if(conf->dir_list) {
        for(int i=0; i<conf->dir_size; i++) {
            free(conf->dir_list[i]);
        } free(conf->dir_list);
    }
}

void config_list( config *conf )
{
    if(conf->dir_list) {
        d_list_free(conf);
    }

    conf->dir_size = file_count(conf->dir_path, 2);
    conf->dir_list = (char**)calloc(conf->dir_size, sizeof(char*));
    //conf->dir_list = (char**)malloc(sizeof(char*)*conf->dir_size+1);
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(conf->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                int len = strlen(ent->d_name);

                conf->dir_list[i] = (char*)calloc(len+1, sizeof(char));
                char *arr = conf->dir_list[i] ;
                strncpy(arr, ent->d_name, len+1);

                arr[len] = '\0';
                i++;
            }
        }
        closedir (dir);
    }
}
