#include "configmng.h"

config *config_new( char *path )
{
    /* Allocate space for the configuration structure. */
    config *conf = (config*)malloc(sizeof(config));

    /* Set initial values for configuration */
    conf->path_dir = path;
    conf->path_sel = NULL;
    conf->name_sel = NULL;
    conf->d_size = -1;
    conf->d_list = NULL;

    /* Add all files to configuration file list */
    config_list(conf);
    return conf;
}

void config_free( config *conf )
{
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
}

char *config_path( config *c )
{
    char cwd[1024];
    size_t lenght = strlen(c->path_dir)+strlen("/config/")+strlen(c->name_sel)+2;
    char *result = (char*)malloc(sizeof(char)*lenght);

    strcpy( result, c->path_dir);
    strcat( result, "/" );
    strcat( result, c->name_sel );

    return result;
}

void config_select( config *c, const char *name )
{
    g_print("selecting configuration : %s\n", name);
    int found = 0;
    for(int i=0; i<c->d_size; i++) {
        if(strcmp (c->d_list[i], name) == 0) {
            if(c->name_sel) {
                free(c->name_sel);
            }
            int lenght = strlen(c->d_list[i]);
            c->name_sel = (char*)malloc(sizeof(char)*lenght+1);
            c->name_sel = c->d_list[i];
            c->path_sel = config_path(c);
            found = 1;
            break;
        }
    } if(found == 0) { g_print("Configuration with name : %s was not found.", name); }
}

char *config_list( config *conf )
{
    conf->d_size = file_count(conf->path_dir, 2);
    conf->d_list = (char*)malloc(sizeof(char)*conf->d_size+1);
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
    /*
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

    char *strings[6];
    strings[0] = jsm_keypair("gridRows", rows, 1);
    strings[1] = jsm_keypair("gridCols", cols, 1);
    strings[2] = jsm_keypair("tickInterval", t_time, 1);
    strings[3] = jsm_keypair("gridVisible", vis, 1);
    strings[4] = jsm_keypair("backgroundColor", bgrn, 1);
    strings[5] = jsm_keypair("cellColor", cell, 0);

    free(bgrn);
    free(cell);
    char *json = jsm_jobj(3, 6, strings);

    jsm_fwrite(json, pref_path);
    free(json);
    for(int i=0; i<6; i++) {
        free(strings[i]);
    }*/
}

void config_read( commons_model *model, config *c )
{/*
    char *json = jsm_fread(pref_path);

    free(model->live_a);
    free(model->live_d);

    char *bgCol, *frCol; /* free these */
    /* populate values for model
    model->cols    = jsm_atoi(json, "gridCols");
    model->rows    = jsm_atoi(json, "gridRows");
    model->interval  = jsm_atoi(json, "tickInterval");
    model->visible = jsm_atoi(json, "gridVisible");
    model->theme_path = jsm_jval(json, "defaultTheme", 3);
    /* TODO: static modifiers for now
    model->cell_s = 10.0;
    model->zoom   = 1.0;
    bgCol = jsm_jval(json, "backgroundColor", 3);
    frCol = jsm_jval(json, "cellColor", 3);
    /* parse colors to model
    gdk_rgba_parse(&model->bgrn_col, bgCol);
    gdk_rgba_parse(&model->cell_col, frCol);

    /* Free dynamically allocated values
    int *live_a1 = (int*)calloc(2, sizeof(int));
    int *live_d1 = (int*)calloc(1, sizeof(int));
    live_a1[0] = 3;
    live_a1[1] = 2;
    live_d1[0] = 3;
    model->live_a = live_a1;
    model->live_d = live_d1;

    free(bgCol);
    free(frCol);
    free(json);
    /* Initialize new grid and give random values
    if(model->interval < 100) {
        g_print("WARNING: update value too small setting to : 100ms.\n");
        model->interval = 100;
    }*/
}
