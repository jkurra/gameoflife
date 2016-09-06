#include "config.h"

#include "../mvc/view.h"

config *config_new( char *path )
{
    /* Allocate space for the configuration structure. */
    config *conf = (config*)malloc(sizeof(config));

    if(path) {
        /* Set initial values for configuration */
        conf->dir_path = path;
        conf->sel_path = NULL;
        conf->sel_name = NULL;
        /*  Size and directory list are linked
         *  and should not be changed individually.
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
            if(strcmp (conf->dir_list[i], name) == 0) {
                if(conf->sel_path) {
                    free(conf->sel_path);
                }
                if(conf->sel_path) {
                    free(conf->sel_name);
                }
                int lenght = strlen(conf->dir_list[i]);

                conf->sel_name = (char*)malloc(sizeof(char)*lenght+1);
                conf->sel_path = (char*)malloc(sizeof(char)*lenght+1);
                conf->sel_name = conf->dir_list[i];
                conf->sel_path = config_path(conf);

                found = 1;
                break;
            }
        } if(found == 0) { g_print("[CONFIG] Configuration with name : %s was not found.\n", name); }

        printf("[%s] Config selected : %s\n", log_timestamp(), conf->sel_name);
        //printf("[CONFIG] selected configuration : %s\n", c->sel_name);
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
    conf->dir_size = file_count(conf->dir_path, 2);
    conf->dir_list = (char**)malloc(sizeof(char*)*conf->dir_size+1);
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(conf->dir_path)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                int len = strlen(ent->d_name);
                conf->dir_list[i] = (char*)malloc(sizeof(char)*len+1);
                conf->dir_list[i] = strdup(ent->d_name);
                i++;
            }
        }
        closedir (dir);
    }
}


void config_write( commons_model *model, config *c)
{
    if(model) {
        char *rows =   (char*) calloc(10, sizeof(char*));
        char *cols =   (char*) calloc(10, sizeof(char*));
        char *t_time = (char*) calloc(10, sizeof(char*));
        char *vis =    (char*) calloc(10, sizeof(char*));

        sprintf(rows, "%d",   model->rows);
        sprintf(cols, "%d",   model->cols);
        sprintf(t_time, "%d", model->interval);
        sprintf(vis, "%d",    model->visible);

        gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
        gchar *cell = gdk_rgba_to_string(&model->cell_col);

        char *strings[7];

        strings[0] = json_keypair("gridRows", rows, 1);
        strings[1] = json_keypair("gridCols", cols, 1);
        strings[2] = json_keypair("tickInterval", t_time, 1);
        strings[3] = json_keypair("gridVisible", vis, 1);
        strings[4] = json_keypair("backgroundColor", bgrn, 1);
        strings[5] = json_keypair("cellColor", cell, 1);
        strings[6] = json_keypair("defaultTheme", model->themes->sel_name, 0);

        free(bgrn);
        free(cell);

        char *json = json_obj(3, 7, strings);

        file_write(json, model->conf->sel_path);
        free(json);
        for(int i=0; i<6; i++) {
            free(strings[i]);
        }
    } else { printf("NULL model \n"); }
}

void config_read( commons_model *model, config *c )
{
    char *json = file_read(model->conf->sel_path);

    free(model->live_a);
    free(model->live_d);

    /* populate values for model*/
    model->cols     = json_atoi(json, "gridCols");
    model->rows     = json_atoi(json, "gridRows");
    model->interval = json_atoi(json, "tickInterval");
    model->visible  = json_atoi(json, "gridVisible");

    if(model->themes) {
        /* Only change theme if different from before */
        if(strcmp (json_val(json, "defaultTheme", 3), model->themes->sel_name) != 0) {
            theme_select(model->themes, json_val(json, "defaultTheme", 3));
        }
    }

    /* TODO: static modifiers for now */
    model->cell_s = 10.0;
    model->zoom   = 1.0;
    model->spacing = 3.0;
    char *bg_col = json_val(json, "backgroundColor", 3);
    char *fr_col = json_val(json, "cellColor", 3);

    /* parse colors to model */
    gdk_rgba_parse(&model->bgrn_col, bg_col);
    gdk_rgba_parse(&model->cell_col, fr_col);

    /* Free dynamically allocated values */
    int *live_a1 = (int*)calloc(2, sizeof(int));
    int *live_d1 = (int*)calloc(1, sizeof(int));

    live_a1[0] = 3;
    live_a1[1] = 2;
    live_d1[0] = 3;

    model->live_a = live_a1;
    model->live_d = live_d1;

    free(bg_col);
    free(fr_col);
    free(json);

    /* Initialize new grid and give random values */
    if(model->interval < 100) {
        g_print("WARNING: update value too small setting to : 100ms.\n");
        model->interval = 100;
    }
}
