#include "model.h"
#include "view.h"

/* @brief Get new view model.
 *
 */
game_model *model_game_new();

/* @brief Get new view model.
 *
 */
menu_model *model_menu_new();

/* @brief Get new view model.
 *
 */
pref_model *model_pref_new();

/* @brief Get new view model.
 *
 */
commons_model *model_commons_new();

/* @brief Get new view model.
 *
 */
void model_game_free( game_model *model );

/* @brief Get new view model.
 *
 */
void model_menu_free( menu_model *model );

/* @brief Get new view model.
 *
 */
void model_pref_free( pref_model *model );

/* @brief Free given view model.
 *
 */
void model_commons_free( commons_model *model );


view_model *model_view_new( int type, Manager *conf )
{
	/* Allocate space for new view_model and add base values */
	view_model *model = (view_model*)malloc(sizeof(view_model));
	model->type = type;
	/* Initialize views_included in model */
	model->menu = model_menu_new();
	model->game = model_game_new();
	model->pref = model_pref_new();

	/* Prepare commonly used values and assign them to models */
	commons_model *commons = model_commons_new(); /* Initialize common values  */
	model->commons = commons;
	model->game->commons = commons;
	model->pref->commons = commons;
	model->commons->conf = conf;
	/* Read values from file to commons */
	model_read(commons, NULL);

	return model;
}

menu_model *model_menu_new()
{
	menu_model *model = (menu_model*)malloc(sizeof(menu_model));

	return model;
}

game_model *model_game_new()
{
	/* Allocate space for the model */
	game_model *game = (game_model*)malloc(sizeof(game_model));
	/* Initialize null values for all variables */
	game->startAtCellX = 0; /* From which column to start drawing */
	game->startAtCellY = 0; /* From which row to start drawing */
	game->c_step = 0;
	game->grid 	  = NULL;
	game->commons = NULL;	/* common values must be externally set, otherwise
							   they are always NULL. */
	return game;
}

pref_model *model_pref_new()
{
	pref_model *pref = (pref_model*)malloc(sizeof(pref_model));
	pref->commons = NULL;

	return pref;
}

commons_model *model_commons_new()
{
	commons_model *commons = (commons_model*)malloc(sizeof(commons_model));

	commons->rows = -1;
	commons->cols = -1;
	commons->timerid  = -1;
	commons->infinite = -1;
	commons->visible  = -1;
	commons->cell_s   = -1;		/* Size of each cell in the screen. */
	commons->zoom     = -1; 	/* How big or small cells appear on the screen.	*/
	commons->interval = -1;
	commons->timerid  = -1;		/* Id of the widget containing update timer. */
	commons->spacing  = -1;
	commons->live_a = NULL;
	commons->live_d = NULL;

	commons->themes = NULL;
	commons->conf   = NULL;

	return commons;
}

void model_view_free( view_model *model )
{
	if(model) {
		g_object_unref(G_OBJECT(model->builder));

		model_menu_free(model->menu);
		model_game_free(model->game);
		model_pref_free(model->pref);
		model_commons_free(model->game->commons);
		//free(model->game->commons->config_path);
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_commons_free( commons_model *model )
{
	if(model) {
		//printf("Model view free called, NULL model. \n");
		if(model->live_a) {
			free(model->live_a);
		}
		if(model->live_d) {
			free(model->live_d);
		}
		free(model);
	}
}

void model_menu_free( menu_model *model )
{
	if(model) {//printf("Model menu free called, NULL model. \n");
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_game_free( game_model *model )
{
	if(model) {//printf("Model game free called. \n");
		grid_free(model->commons->rows, model->grid);
		free(model);
	} else { printf("ERROR: Unable to free game_model, NULL model. \n"); }
}

void model_pref_free( pref_model *model)
{
	if(model) {//printf("Model pref free called, NULL model. \n");
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_update( view_model *model, int type )
{
	if(model) {
		switch(type) {
			case MENU:
				break;
			case GAME:
				model_game_setup(model->game, "");
				break;
			case PREF:
				model_pref_setup(model->pref, "");
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}

void model_game_setup( game_model *model, const char *pref_path )
{
	if(model) {
		model_read(model->commons, NULL);
		if(model->grid) { /* Free current grid if allocated */
			grid_free(model->c_rows, model->grid);
		}
		model->grid = grid_new(model->commons->rows, model->commons->cols);
		model->c_rows = model->commons->rows;
		model->c_cols = model->commons->cols;
	} else { printf("MODEL [SETUP] : ERROR! Received null pointer to model\n"); }
}

void model_pref_setup( pref_model *model, const char *pref_path )
{
	if(model) {
		model_read(model->commons, NULL);
	} else { printf("MODEL [SETUP] : ERROR! Received null pointer to model\n"); }
}

void model_attach_timer(view_model *model, int interval )
{
	switch(model->type) {
		case GAME:
			model->game->commons->timerid = g_timeout_add(model->game->commons->interval, (GSourceFunc) view_timer_update, model->game);
			printf("[%s] Attached timer, id:%d, interval: %d \n", log_timestamp(), model->game->commons->timerid, model->game->commons->interval );
			break;
		default:
			break;
	}
}

void model_remove_timer( view_model *model, int timer_id )
{
	if(timer_id != -1) {
		g_source_remove(timer_id);
		model->game->commons->timerid = -1;
	}
}


void model_write( commons_model *model, Manager *c)
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

void model_read( commons_model *model, Manager *c )
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
