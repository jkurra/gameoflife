#include "theme.h"

/** @brief Updates list of available themes.
 *
 */
void theme_list( Manager *th );

Manager *theme_new( const char *path )
{
    /* Allocate space for the configuration structure. */
    Manager *th = (Manager*)calloc(1, sizeof(Manager));
    th->dir_path = NULL;
    if(path) {
        int plen = strlen(path); /* Get excact length of the path parameter */
        /*
         *  Assing initial values for theme member variables. Path is copied from
         *  parameter so we can safely free it in theme_free().
         */
        th->dir_path = (char*)calloc(plen+1,sizeof(char));
        strncpy(th->dir_path, path, plen);
    }
    /*
     *  Selection may or may not be found, depending on the root folder.
     *  If it has folders, first theme is selected as default.
     */
    th->sel_path = NULL;
    th->sel_name = NULL;
    /*
     *  Size and directory list are linked and should NEVER be changed individually.
     *  Only appropriate functions may be used to change or access their values.
     */
    th->dir_list = NULL;
    th->dir_size = -1;
    /* Add all themes to list, folders must contain at least one css file. */
    theme_list(th);
    printf("[%s] Theme initialized, found %d valid themes.\n", log_timestamp(), th->dir_size);

    return th;
}

void theme_select( Manager *manager, char *name )
{
    if(manager && name) {
        theme_list(manager);
        /* Free existing path & name variables from structure if found. */
        if(manager->sel_path) {
            free(manager->sel_path);
            manager->sel_path = NULL;
        }
        if(manager->sel_name) {
            free(manager->sel_name);
            manager->sel_name = NULL;
        }

        int found = 0;
        for(int i=0; i<manager->dir_size; i++) {
            //printf("%s : %s\n", c->dir_list[i], name);
            if(strcmp (manager->dir_list[i], name) == 0) {
                //printf("%s : %s\n", c->dir_list[i], name);
                int nlen = strlen(manager->dir_list[i]);
                int plen = (strlen(manager->dir_list[i])*2)+strlen(manager->dir_path)+6;

                manager->sel_name = (char*)calloc(nlen+1, sizeof(char));
                manager->sel_path = (char*)calloc(plen+1, sizeof(char));

                strncpy(manager->sel_name, manager->dir_list[i], nlen+1);
                strncpy(manager->sel_path, manager->dir_path, plen+1);
                //strcpy(manager->sel_path, manager->dir_path);
                strcat(manager->sel_path, "/");
                strcat(manager->sel_path, manager->sel_name);
                strcat(manager->sel_path, "/");
                strcat(manager->sel_path, manager->sel_name);
                strcat(manager->sel_path, ".css");

                found = 1;
                break;
            }
        } if(found == 0) { printf("[%s] Theme directory with name \"%s\" \n", log_timestamp(), name); }
        printf("[%s] Selected theme named \"%s\" \n", log_timestamp(),manager->sel_name);
    } else {  printf("[%s] Theme selection received NULL pointer. \n", log_timestamp());}
}

void theme_free(Manager * manager) {
    if(manager) {
        /*
         * Free saved filenames and members, paranoia checks in case internal
         * variables have been messed with.
         */
        if(manager->dir_list) {
            for(int i=0; i<manager->dir_size; i++) {
                free(manager->dir_list[i]);
                manager->dir_list[i] = NULL;
            }
            free(manager->dir_list);
            manager->dir_list = NULL;
            manager->dir_size = -1;
        }
        /* Free members */
        if(manager->dir_path) {
            free(manager->dir_path);
            manager->dir_path = NULL;
        }
        if(manager->sel_path) {
            free(manager->sel_path);
            manager->sel_path = NULL;
        }
        if(manager->sel_name) {
            free(manager->sel_name);
            manager->sel_name = NULL;
        }
        free(manager);
        manager = NULL;
    } else { printf("[%s] Attempted theme_free() for a NULL pointer. \n", log_timestamp()); }
}

void dir_list_free( char **dir_list, int size )
{
    if(dir_list) {
        for(int i=0; i<size; i++) {
            free(dir_list[i]);
            dir_list[i] = NULL;
        }
        free(dir_list);
        dir_list = NULL;
    }
}

void theme_list( Manager *manager )
{
    /* Free existing directory list if found. */
    if(manager->dir_list) {
        dir_list_free(manager->dir_list, manager->dir_size);
    }
    /* Get directory count and allocate space for the file list. */
    manager->dir_size = file_count(manager->dir_path, 1);
    manager->dir_list = (char**)calloc(manager->dir_size, sizeof(char*));
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(manager->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            /* Check that directory is regular directory and add to list. */
            if (strcmp (ent->d_name, "..") != 0 && strcmp (ent->d_name, ".") != 0 && ent->d_type == DT_DIR) {
                int len = strlen(ent->d_name);
                manager->dir_list[i] = (char*)calloc(len+1, sizeof(char));
                char *arr = manager->dir_list[i] ;
                strncpy(arr, ent->d_name, len+1);
                i++;
            }
        }
        closedir (dir);
    }
}
