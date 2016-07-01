#include "config.h"

config *config_new( char *path )
{
    /* Allocate space for the configuration structure. */
    config *conf = (config*)malloc(sizeof(config));

    if(path) {
        /* Set initial values for configuration */
        conf->path_dir = path;
        conf->path_sel = NULL;
        conf->name_sel = NULL;
        /*  Size and directory list are linked
         *  and should not be changed individually.
         */
        conf->d_size = -1;
        conf->d_list = NULL;
        /* Add all files to configuration file list */
        config_list(conf);
        printf("[CONFIG] initialized configuration : %s\n", conf->path_dir );

    } else { printf("NULL path requested for configuration \n"); }

    return conf;
}

void config_free( config *conf )
{
    if(conf) {
        /* Free members */
        if(conf->path_dir) {
            free(conf->path_dir);
        }
        if(conf->path_sel) {
            //free(conf->path_sel);
        }
        if(conf->name_sel) {
            //free(conf->name_sel);
        }
        /* Free saved filenames */
        for(int i=0; i<conf->d_size; i++) {
            free(conf->d_list[i]);
        }
        free(conf->d_list);
    } else {}
}

char *config_path( config *c )
{
    /* Configurations are located at /config/ directory root. */
    size_t lenght = strlen(c->path_dir)+strlen("/config/")+strlen(c->name_sel)+2;
    char *result = (char*)malloc(sizeof(char)*lenght);
    /*  */
    strcpy( result, c->path_dir);
    strcat( result, "/" );
    strcat( result, c->name_sel );

    return result;
}

void config_select( config *c, const char *name )
{
    int found = 0;
    for(int i=0; i<c->d_size; i++) {
        if(strcmp (c->d_list[i], name) == 0) {
            if(c->name_sel) {
                printf("freeing %s\n", c->name_sel);
                free(c->name_sel);
            }
            if(c->path_sel) {
                printf("freeing %s\n", c->path_sel );
                free(c->path_sel);
            }
            int lenght = strlen(c->d_list[i]);
            int p_len = strlen(c->d_list[i])+strlen(c->path_dir)+1;
            c->name_sel = (char*)malloc(sizeof(char)*lenght+1);
            c->path_sel = (char*)malloc(sizeof(char)*lenght+1);

            c->name_sel = c->d_list[i];
            c->path_sel = config_path(c);
            found = 1;
            break;
        }
    } if(found == 0) { g_print("Configuration with name : %s was not found.", name); }

    g_print("[CONFIG] selected configuration : %s\n", c->name_sel);
}

void d_list_free(config *conf)
{
    if(conf->d_list) {
        for(int i=0; i<conf->d_size; i++) {
            free(conf->d_list[i]);
        } free(conf->d_list);
    }   
}

void config_list( config *conf )
{
    conf->d_size = file_count(conf->path_dir, 2);
    conf->d_list = (char**)malloc(sizeof(char*)*conf->d_size+1);
    /* Add all files to configuration file list */
    DIR *dir = NULL;
    int i=0;
    if((dir = opendir(conf->path_dir)) != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                int len = strlen(ent->d_name);
                conf->d_list[i] = (char*)malloc(sizeof(char)*len+1);
                conf->d_list[i] = strdup(ent->d_name);
                i++;
            }
        }
        closedir (dir);
    }
}


void config_write( commons_model *model, config *c)
{
    if(model) {
        char *rows  = (char*)calloc(10, sizeof(char*));
        char *cols = (char*)calloc(10, sizeof(char*));
        char *t_time = (char*)calloc(10, sizeof(char*));
        char *vis = (char*)calloc(10, sizeof(char*));

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
        strings[6] = json_keypair("defaultTheme", model->theme_path, 0);

        free(bgrn);
        free(cell);
        char *json = json_obj(3, 7, strings);

        file_write(json, model->config_path);
        free(json);
        for(int i=0; i<6; i++) {
            free(strings[i]);
        }
    } else { printf("NULL model \n"); }
}

void config_read( commons_model *model, config *c )
{
    char *json = file_read(model->config_path);

    free(model->live_a);
    free(model->live_d);

    char *bg_col, *fr_col; /* free these */
    /* populate values for model*/
    model->cols     = jsm_atoi(json, "gridCols");
    model->rows     = jsm_atoi(json, "gridRows");
    model->interval = jsm_atoi(json, "tickInterval");
    model->visible  = jsm_atoi(json, "gridVisible");
    model->theme_path = json_val(json, "defaultTheme", 3);
    /* TODO: static modifiers for now*/
    model->cell_s = 10.0;
    model->zoom   = 1.0;
    bg_col = json_val(json, "backgroundColor", 3);
    fr_col = json_val(json, "cellColor", 3);
    /* parse colors to model*/
    gdk_rgba_parse(&model->bgrn_col, bg_col);
    gdk_rgba_parse(&model->cell_col, fr_col);

    /* Free dynamically allocated values*/
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
