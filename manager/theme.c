#include "theme.h"

theme *theme_new( char *path )
{
    /* Allocate space for the configuration structure. */
    theme *th = (theme*)malloc(sizeof(theme));

    if(path) {
        /* Asign initial values for theme member variables */
        th->dir_path = path;
        th->sel_path = NULL;
        th->sel_name = NULL;

        th->dir_list = NULL;
        th->dir_size = -1;
        theme_list(th);
    }
    return th;
}

char *theme_path( theme *c )
{
    size_t lenght = strlen(c->dir_path)+strlen(c->sel_name)+2;
    char *result = (char*)malloc(sizeof(char)*lenght);

    strcpy( result, c->dir_path);
    strcat( result, "/" );
    strcat( result, c->sel_name );

    return result;
}

void theme_select( theme *c, char *name )
{
    /* TODO: theme must be retrieved from a directory named like the css file.
     * For example directory named default would contain file named default.css
     * which is used as theme file.
     */
    //g_print("selected configuration : %s\n", c->dir_path);
    int found = 0;
    for(int i=0; i<c->dir_size; i++) {
        if(strcmp (c->dir_list[i], name) == 0) {
            g_print("%s : %s\n", c->dir_list[i], name);
            if(c->sel_name) {
                free(c->sel_name);
            }
            int lenght = strlen(c->dir_list[i]);
            c->sel_name = (char*)malloc(sizeof(char)*lenght+1);
            c->sel_name = c->dir_list[i];
            c->sel_path = theme_path(c);
            found = 1;
            break;
        }
    } if(found == 0) { g_print("Configuration with name : %s was not found.", name); }

    //g_print("selected configuration : %s\n", c->sel_name);
}

void theme_list( theme *t )
{
    t->dir_size = file_count(t->dir_path, 2);
    t->dir_list = (char**)malloc(sizeof(char*)*t->dir_size+1);
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(t->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                int len = strlen(ent->d_name);
                t->dir_list[i] = (char*)malloc(sizeof(char)*len+1);
                t->dir_list[i] = strdup(ent->d_name);
                g_print("dir: %s\n", t->dir_list[i]);
                i++;
            }
        }
        closedir (dir);
    }
}
