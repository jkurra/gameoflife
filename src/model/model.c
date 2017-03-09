#include "model.h"

Model *model_new()
{
    Model *model = (Model*)calloc(1, sizeof(Model));
    /*
        Base model has a type which is used to determine wheter
        it can be cast to another "subclass". Available subcasses
        can be found in "model.h"
    */
    model->type = -1;

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
    //model->live_a = NULL;
    //model->live_d = NULL;
    model->ruleset = (RuleSet*)calloc(1, sizeof(RuleSet));
    model->c_step   = 0;
    model->zoom     = 1;    /* TODO: Read from json file, */
    //model->rows = 0;
    //model->cols = 0;
    model->infinite = 0;
    model->visible  = 0;
    model->cell_s = 0;
    model->spacing = 0.0;
    model->interval = 0;
    model->timerid = -1;

    model->startX = 0;
    model->startY = 0;

    return model;
}

void GameModel_read( GameModel *model, const char *file )
{
    char *json = file_read(file);
    JsonObject *jsn = json_parse(json);
    if(json) {

        JsonKeypair *bg_col = (JsonKeypair*)json_find(jsn, "backgroundColor"); // json_val(json, "backgroundColor", 3);
        JsonKeypair *fr_col = (JsonKeypair*)json_find(jsn, "cellColor");  // json_val(json, "cellColor", 3);
        /* parse colors to model */
        if(bg_col) {
            gdk_rgba_parse(&model->bgrn_col, bg_col->value);
        }else {
            bg_col = NULL;
        }
        if(fr_col) {
            gdk_rgba_parse(&model->cell_col, fr_col->value);
        }else {
            fr_col = NULL;
        }

        JsonKeypair *rows1 = (JsonKeypair*)json_find(jsn, "gridRows");
        JsonKeypair *rows2 = (JsonKeypair*)json_find(jsn, "gridCols");

        int rows = atoi(rows1->value);
        int cols = atoi(rows2->value);

        if(model->grid) {
            Grid_resize(model->grid, rows, cols);
        }
        else {
            model->grid = Grid_new(rows, cols);//grid_new(rows, cols);
        }

        //model->rows = rows;
        //model->cols = cols;

        //model->live_a = (int*)calloc(2, sizeof(int));
        //model->live_d = (int*)calloc(1, sizeof(int));
        model->ruleset->live_a = (int*)calloc(2, sizeof(int));
        model->ruleset->live_s = 2;
        model->ruleset->live_d = (int*)calloc(1, sizeof(int));
        model->ruleset->dead_s =1 ;

        model->ruleset->live_a[0] = 3;
        model->ruleset->live_a[1] = 2;

        model->ruleset->live_d[0] = 3;

        /*
        model->live_a[0] = 3;
        model->live_a[1] = 2;
        model->live_d[0] = 3;
*/
        model->infinite = 0;
        model->spacing = 2.0;
        model->cell_s = 10.0;
        JsonKeypair *zoom= (JsonKeypair*)json_find(jsn, "zoom");
        model->zoom = atoi(zoom->value);

        JsonKeypair *tmpGrid = (JsonKeypair*)json_find(jsn, "gridVisible");
        JsonKeypair *tmpTick = (JsonKeypair*)json_find(jsn, "tickInterval");

        model->visible  = atoi(tmpGrid->value);
        model->interval = atoi(tmpTick->value);

        free(json);
        json_free(jsn);
    }
}

void GameModel_save( GameModel *model )
{
    if(model) {
        char *rows =   (char*) calloc(10, sizeof(char*));
        char *cols =   (char*) calloc(10, sizeof(char*));
        char *t_time = (char*) calloc(10, sizeof(char*));
        char *vis =    (char*) calloc(10, sizeof(char*));

        sprintf(rows, "%d",   model->grid->rows);
        sprintf(cols, "%d",   model->grid->cols);
        sprintf(t_time, "%d", model->interval);
        sprintf(vis, "%d",    model->visible);

        gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
        gchar *cell = gdk_rgba_to_string(&model->cell_col);

		JsonObject *object = json_parse(NULL);

        char *zoom = (char*)calloc(10, sizeof(char*));
        sprintf(zoom, "%f", model->zoom);

		json_add_value(object, json_keypair_create("gridRows", rows));
		json_add_value(object, json_keypair_create("gridCols", cols));
		json_add_value(object, json_keypair_create("tickInterval", t_time));
		json_add_value(object, json_keypair_create("gridVisible", vis));
		json_add_value(object, json_keypair_create("backgroundColor", bgrn));
		json_add_value(object, json_keypair_create("cellColor", cell));
        json_add_value(object, json_keypair_create("defaultTheme", model->themes->sel_name));
        json_add_value(object, json_keypair_create("zoom", zoom));

        free(bgrn);
        free(cell);
        ///printf("Writing object: \n %s\n", object->main_object);
        file_write(object->main_object, model->conf->sel_path);
    }
}

void GameModel_free( GameModel *model )
{
    if(model) {
        //if(model->main_frame) {
            //gtk_widget_destroy(GTK_WIDGET(model->main_frame));
            //model->main_frame = NULL;
        //}
        //if(model->game_frame) {
            //gtk_widget_destroy(GTK_WIDGET(model->game_frame));
            //model->game_frame = NULL;
        //}
        if(model->grid) {
            Grid_free(model->grid);
        }

        //free(model->live_a);
        //free(model->live_d);
        free(model);
        model = NULL;
    }
}

MenuModel *MenuModel_new()
{
    MenuModel *model = (MenuModel*)calloc(1, sizeof(MenuModel));
    model->base.type  = MENU;
    model->main_frame = NULL;
    model->builder = NULL;
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
        //if(model->main_frame) {
            /*free(model->main_frame);
            model->main_frame = NULL;*/
        //}
        free(model);
        model = NULL;
    }
}

PrefModel *PrefModel_new()
{
    PrefModel *model = (PrefModel*)calloc(1, sizeof(PrefModel));
    model->base.type  = PREF;
    model->main_frame = NULL;
    model->builder = NULL;
    return model;
}

void PrefModel_read( PrefModel *model, const char *file )
{
    //char *json = file_read(file);

    //JsonObject *object = json_create(json);
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
        /*if(model->main_frame) {
            free(model->main_frame);
            model->main_frame = NULL;
        }*/
        free(model);
        model = NULL;
    }
}
