#include "model.h"

Model *model_new()
{
    Model *model = (Model*)calloc(1, sizeof(Model));
    /*
        Base model has a type which is used to determine wheter
        it can be cast to another "subclass". Available subcasses
        can be found in "model.h"
    */
    model->type     = -1;
    model->provider = NULL; /* TODO: remove */

    return model;
}

void model_free( Model *model )
{
    if(model) {
        free(model);
        model = NULL;
    }
}

GameModel *GameModel_new()
{
    GameModel *model = (GameModel*)calloc(1, sizeof(GameModel));
    /* Set base type to GAME, can be read from GameModel cast to Model */
    model->base.type  = GAME;
    /* Initialize member values */
    model->main_frame = NULL;
    //model->game_frame = NULL;
    model->grid = NULL;
    model->live_a = NULL;
    model->live_d = NULL;

    model->c_step   = 0;
    model->zoom     = 2;    /* TODO: Read from json file, */
    model->rows = 0;
    model->cols = 0;
    model->infinite = 0;
    model->visible  = 0;
    model->cell_s = 0;
    model->spacing = 0.0;
    model->interval = 0;
    model->timerid = -1;

    return model;
}

void GameModel_read( GameModel *model, const char *file )
{
    char *json = file_read(file);
    json_ob *jsn = json_create(json);
    if(json) {
        //char *bg_col = json_get(jsn, "backgroundColor");
        //char *fr_col = json_get(jsn, "cellColor");

        char *bg_col = json_val(json, "backgroundColor", 3);
        char *fr_col = json_val(json, "cellColor", 3);
        
        /* parse colors to model */
        if(bg_col) {
            gdk_rgba_parse(&model->bgrn_col, bg_col);
        }else {
            bg_col = NULL;
        }
        if(fr_col) {
            gdk_rgba_parse(&model->cell_col, fr_col);
        }else {
            fr_col = NULL;
        }

        free(bg_col);
        free(fr_col);
        char* rows1 = json_val(json, "gridRows", 3);
        char *cols1 = json_val(json, "gridCols", 3);

        int rows = atoi(rows1);
        int cols = atoi(cols1);

        free(rows1);
        free(cols1);

        if(model->grid) {
            grid_resize(model->grid, model->rows, model->cols, rows, cols);
        }
        else {
            model->grid = grid_new(rows, cols);
        }

        model->rows = rows;
        model->cols = cols;


        model->live_a = (int*)calloc(2, sizeof(int));
        model->live_d = (int*)calloc(1, sizeof(int));

        model->live_a[0] = 3;
        model->live_a[1] = 2;
        model->live_d[0] = 3;

        //model->grid = grid_new(model->rows, model->cols);
        model->infinite = 0;
        model->spacing = 2.0;
        model->cell_s = 10.0;
        char *tmpGrid = json_val(json, "gridVisible", 3);
        char *tmpTick = json_val(json, "tickInterval", 3);
        model->visible  = atoi(tmpGrid);
        model->interval = atoi(tmpTick);
        free(tmpTick);
        free(tmpGrid);
        free(json);
    }
}

void GameModel_save( GameModel *model )
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
		json_ob *object = json_create(NULL);
		//printf("keypair : %s\n", json_keypair("gridRows", rows, 1));
        strings[0] = json_keypair("gridRows", rows, 1);
        strings[1] = json_keypair("gridCols", cols, 1);
        strings[2] = json_keypair("tickInterval", t_time, 1);
        strings[3] = json_keypair("gridVisible", vis, 1);
        strings[4] = json_keypair("backgroundColor", bgrn, 1);
        strings[5] = json_keypair("cellColor", cell, 1);
        strings[6] = json_keypair("defaultTheme", model->themes->sel_name, 0);

		json_add_value(object, strings[0]);
		json_add_value(object, strings[1]);
		json_add_value(object, strings[2]);
		json_add_value(object, strings[3]);
		json_add_value(object, strings[4]);
		json_add_value(object, strings[5]);
		//json_add_value(object, strings[6]);

        free(bgrn);
        free(cell);

        char *json = json_to_string(object);//json_obj(3, 7, strings);

        file_write(json, model->conf->sel_path);
        free(json);
        for(int i=0; i<6; i++) {
            free(strings[i]);
        }
    }
}

void GameModel_free( GameModel *model )
{
    if(model) {
        if(model->main_frame) {
            //gtk_widget_destroy(GTK_WIDGET(model->main_frame));
            //model->main_frame = NULL;
        }
        if(model->game_frame) {
            //gtk_widget_destroy(GTK_WIDGET(model->game_frame));
            //model->game_frame = NULL;
        }
        if(model->grid) {
            grid_free(model->rows, model->grid);
        }

        free(model->live_a);
        free(model->live_d);
        free(model);
        model = NULL;
    }
}

MenuModel *MenuModel_new()
{
    MenuModel *model = (MenuModel*)calloc(1, sizeof(MenuModel));
    model->base.type  = MENU;
    model->main_frame = NULL;

    return model;
}

void MenuModel_read( MenuModel *model, const char *file )
{
    //char *json = file_read(file);
/*
    char *bg_col = json_val(json, "backgroundColor", 3);
    char *fr_col = json_val(json, "cellColor", 3);

    gdk_rgba_parse(&model->bgrn_col, bg_col);
    gdk_rgba_parse(&model->cell_col, fr_col);

    model->rows = atoi(json_val(json, "gridRows", 3));
    model->cols = atoi(json_val(json, "gridCols", 3));

    model->infinite;
    model->visible = atoi(json_val(json, "gridVisible", 3));
    model->interval = atoi(json_val(json, "tickInterval", 3));*/
}

void MenuModel_free( MenuModel *model )
{
    if(model) {
        if(model->main_frame) {
            free(model->main_frame);
            model->main_frame = NULL;
        }
        free(model);
        model = NULL;
    }
}

PrefModel *PrefModel_new()
{
    PrefModel *model = (PrefModel*)calloc(1, sizeof(PrefModel));
    model->base.type  = GAME;
    model->main_frame = NULL;

    return model;
}

void PrefModel_read( PrefModel *model, const char *file )
{
    //char *json = file_read(file);

    //json_ob *object = json_create(json);
    //printf("json \n%s\n", json);
/*
    char *bg_col = json_val(json, "backgroundColor", 3);
    char *fr_col = json_val(json, "cellColor", 3);

    gdk_rgba_parse(&model->bgrn_col, bg_col);
    gdk_rgba_parse(&model->cell_col, fr_col);

    model->rows = atoi(json_val(json, "gridRows", 3));
    model->cols = atoi(json_val(json, "gridCols", 3));

    model->infinite;
    model->visible = atoi(json_val(json, "gridVisible", 3));
    model->interval = atoi(json_val(json, "tickInterval", 3));*/

}

void PrefModel_free( PrefModel *model )
{
    if(model) {
        if(model->main_frame) {
            free(model->main_frame);
            model->main_frame = NULL;
        }
        free(model);
        model = NULL;
    }
}
