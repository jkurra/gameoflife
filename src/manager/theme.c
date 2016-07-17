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
        printf("[THEME] initialized theme : %s\n", th->dir_path );
        for(int i=0; i<th->dir_size; i++) {
            printf("[THEME] %d: %s\n",i, th->dir_list[i] );
        }
        printf("+------------------------------------+\n" );
    }
    return th;
}

char *theme_path( theme *c )
{
    size_t lenght = strlen(c->dir_path)+strlen(c->sel_name)+strlen(c->sel_name)+3+4;
    char *result = (char*)malloc(sizeof(char)*lenght);

    strcpy( result, c->dir_path);
    strcat( result, "/" );
    strcat( result, c->sel_name );
    strcat( result, "/" );
    strcat( result, c->sel_name );
    strcat( result, ".css");
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
        printf("[THEME] trying to select theme: %d\n", c->dir_size);
    for(int i=0; i<c->dir_size; i++) {
        printf("%s : %s\n", c->dir_list[i], name);
        if(strcmp (c->dir_list[i], name) == 0) {
            printf("%s : %s\n", c->dir_list[i], name);
            if(c->sel_path) {
                free(c->sel_path);
            }
            int lenght = strlen(c->dir_list[i]);
            c->sel_name = (char*)malloc(sizeof(char)*lenght+1);
            c->sel_name = c->dir_list[i];
            c->sel_path = theme_path(c);
            found = 1;
            break;
        }
    } if(found == 0) { printf("[THEME] theme directory with name : %s was not found. \n", name); }
    printf("[THEME] selected theme : %s\n", c->sel_path);
}

void theme_list( theme *t )
{
    t->dir_size = file_count(t->dir_path, 1);
    t->dir_list = (char**)malloc(sizeof(char*)*t->dir_size);
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(t->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if(strcmp (ent->d_name, "..") == 0||strcmp (ent->d_name, ".") == 0) {
                // skip
            }
            else if (ent->d_type == DT_DIR) {
                int len = strlen(ent->d_name);
                t->dir_list[i] = (char*)malloc(sizeof(char)*len+1);
                t->dir_list[i] = strdup(ent->d_name);
            //    printf("dir: %s\n", t->dir_list[i]);
                i++;
            }
        }
        closedir (dir);
    }
}
