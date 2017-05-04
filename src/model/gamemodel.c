#include "gamemodel.h"

GameModel *GameModel_new()
{
    /* Allocate space for the new GameModel. */
    GameModel *model = (GameModel*)calloc(1, sizeof(GameModel));
    /* Set base type to GAME, can be read from GameModel cast to Model */
    model->base.type  = GAME;
    model->is_playing = 0;
    /* Initialize member values */
    model->main_frame = NULL;
    model->game_frame = NULL;
    model->grid = NULL;
    model->ruleset = (RuleSet*)calloc(1, sizeof(RuleSet));
    model->c_step   = 0;
    model->zoom     = 1;    /* TODO: Read from json file, */

    model->infinite = 0;
    model->visible  = 0;
    model->cell_s = 0;
    model->spacing = 0.0;
    model->interval = 0;
    model->timerid = -1;
    model->updated = 0;
    model->startX = 0;
    model->startY = 0;

    return model;
}

void GameModel_read( GameModel *model, const char *file )
{
    /*
     *  Read raw json data from text file.
     */
    char *json = file_read(file);

    if( json && model ) {
        /* Parse data got from file. */
        JsonObject *jsn = json_parse(json);
        /* Retrieve needed keypairs from json object and cast to JsonKeypair. */
        JsonKeypair *bg_col  = (JsonKeypair*)json_find(jsn, "backgroundColor");
        JsonKeypair *fr_col  = (JsonKeypair*)json_find(jsn, "cellColor");
        JsonKeypair *rows1   = (JsonKeypair*)json_find(jsn, "gridRows");
        JsonKeypair *rows2   = (JsonKeypair*)json_find(jsn, "gridCols");
        JsonKeypair *zoom    = (JsonKeypair*)json_find(jsn, "zoom");
        JsonKeypair *tmpGrid = (JsonKeypair*)json_find(jsn, "gridVisible");
        JsonKeypair *tmpTick = (JsonKeypair*)json_find(jsn, "tickInterval");
        /* parse colors to model */
        if(bg_col) { gdk_rgba_parse(&model->bgrn_col, bg_col->value); }
        if(fr_col) { gdk_rgba_parse(&model->cell_col, fr_col->value); }
        /* Convert necessary values to integer. */
        int rows = atoi(rows1->value);
        int cols = atoi(rows2->value);
        model->zoom     = atoi(zoom->value);
        model->visible  = atoi(tmpGrid->value);
        model->interval = atoi(tmpTick->value);
        /* Initialize grid using found rows/cols values. */
        if(model->grid) {
            Grid_free(model->grid);
        }
        model->grid = Grid_new(rows, cols);
        /* Initialize ruleset values. */
        model->ruleset->live_a = (int*)calloc(2, sizeof(int));
        model->ruleset->live_s = 2;
        model->ruleset->live_d = (int*)calloc(1, sizeof(int));
        model->ruleset->dead_s = 1;
        /* TODO: Rules will be read from json file, for now we use static "classic" rules. */
        model->ruleset->live_a[0] = 3;
        model->ruleset->live_a[1] = 2;
        model->ruleset->live_d[0] = 3;
        /* TODO: add dynamic modification to these values. */
        model->infinite = 0;
        model->spacing  = 2.0;
        model->cell_s   = 10.0;
        /* Free dynamically allocated values. */
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

        sprintf(rows, "%d",   model->grid->gArray->rows);
        sprintf(cols, "%d",   model->grid->gArray->cols);
        sprintf(t_time, "%d", model->interval);
        sprintf(vis, "%d",    model->visible);

        gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
        gchar *cell = gdk_rgba_to_string(&model->cell_col);

        printf("saving bgrn: %s\n", bgrn);
        printf("saving cell: %s\n", cell);

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

        model->infinite = -1;
        model->visible= -1;

        model->cell_s = -1;
        model->zoom = -1;
        model->spacing = -1;
        model->interval= -1;
        model->c_step = -1;
        model->timerid= -1;
        model->startX = -1;
        model->startY = -1;

        if(model->themes) {
            theme_free(model->themes);
        }
        if(model->conf) {
            config_free(model->conf);
        }
        if(model->grid) {
            Grid_free(model->grid);
        }
        free(model->ruleset->live_a);
        free(model->ruleset->live_d);
        free(model->ruleset);
        model->ruleset = NULL;
        //free(model->live_a);
        //free(model->live_d);
        free(model);
        model = NULL;
    }
}
