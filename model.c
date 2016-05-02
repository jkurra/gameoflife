#include "model.h"

view_model *model_view_new( int type, char *pref_path )
{
	/* Allocate space for new view_model and add base values */
	view_model *model = (view_model*)malloc(sizeof(view_model));
	model->type = type;
	model->pref_path = pref_path;
	/* Initialize model variables and GTK parts initialization*/
	/* TODO: refactor this to be part of view */
	gtk_init(NULL, NULL);
	model->builder = gtk_builder_new();

	/* Initialize views_included in model */
	model->menu = model_menu_new();
	model->game = model_game_new();
	model->pref = model_pref_new();

	commons_model *commons = model_commons_new(); /* Initialize common values  */
	if(model->pref_path) {
		jsm_read_commons(commons, pref_path); /* Read common values from file. */
		model->game->commons = commons;
		model->pref->commons = commons;
	} else { printf("No Settings file provided. \n" ); }

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
	commons->timerid = -1;
	commons->infinite = -1;
	commons->visible  = -1;
	commons->cell_s   = -1;		/* Size of each cell in the screen. */
	commons->zoom     = -1; 	/* How big or small cells appear on the screen.	*/
	commons->interval = -1;
	commons->timerid  = -1;		/* Id of the widget containing update timer. */
	commons->live_a = NULL;
	commons->live_d = NULL;

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
		free(model->pref_path);
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_commons_free( commons_model *model )
{
	if(model) {
		printf("Model view free called, NULL model. \n");

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
	if(model) {printf("Model menu free called, NULL model. \n");
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_game_free( game_model *model )
{
	if(model) {printf("Model game free called. \n");
		grid_free(model->commons->rows, model->grid);
		free(model);
	} else { printf("ERROR: Unable to free game_model, NULL model. \n"); }
}

void model_pref_free( pref_model *model)
{
	if(model) {printf("Model pref free called, NULL model. \n");
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_attach_timer(view_model *model, GSourceFunc update_function, int interval )
{
	switch(model->type) {
		case GAME:
			model->game->commons->timerid = g_timeout_add(model->game->commons->interval, (GSourceFunc) view_timer_update, model);
			break;
		default:
			break;
	}
}

void model_remove_timer( view_model *model, int timer_id )
{
	g_source_remove(timer_id);
	model->game->commons->timerid = -1;
}

void model_init_view( view_model *model, int type )
{	/* TODO: refactor this to be part of view */
	model->type = type; /* Change current view type. */
	if(model) {
		switch(model->type) {
			case MENU:
				printf("MODEL [INIT] : menu\n");
				view_menu_init(model->menu, model->builder);
				gtk_builder_connect_signals(model->builder, model);
				break;
			case GAME:
				printf("MODEL [INIT] : game\n");
				model_game_setup(model->game, model->pref_path);
				view_game_init(model->game, model->builder);
				gtk_builder_connect_signals(model->builder, model);
				break;
			case PREF:
				printf("MODEL [INIT] : pref\n");
				model_pref_setup(model->pref, model->pref_path);
				view_pref_init(model->pref, model->builder);
				gtk_builder_connect_signals(model->builder, model);
				break;
			default:
				break;
		}
		gtk_main();
	} else { printf("MODEL [INIT] : ERROR! Received null pointer to model\n"); }
}

void model_draw_view( view_model *model )
{	/* TODO: refactor this to be part of view */
	if(model) {
		switch(model->type) {
			case MENU:
				gtk_widget_queue_draw(model->menu->main_frame);
				break;
			case GAME:
				gtk_widget_queue_draw(model->game->main_frame);
				break;
			case PREF:
				gtk_widget_queue_draw(model->pref->main_frame);
				break;
			default:
				break;
		}
	} else { printf("MODEL [DRAW] : ERROR! Received null pointer to model\n"); }
}

void model_close_view( view_model *model )
{	/* TODO: refactor this to be part of view */
	if(model) {
		gtk_main_quit();
		switch(model->type) {
			case MENU:
				printf("MODEL [CLOSE] : menu\n");
				view_menu_close(model->menu);
				break;
			case GAME:
				printf("MODEL [CLOSE] : game\n");
				view_game_close(model->game);
				break;
			case PREF:
				printf("MODEL [CLOSE] : pref\n");
				view_pref_close(model->pref);
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}

void model_update( view_model *model, int type )
{	//TODO this should read current view values
	if(model) {
		switch(type) {
			case MENU:
				printf("MODEL [UPDATE] : menu\n");
				break;
			case GAME:
				printf("MODEL [UPDATE] : game\n");
				model_game_setup(model->game, model->pref_path);
				break;
			case PREF:
				printf("MODEL [UPDATE] : pref\n");
				model_pref_setup(model->pref, model->pref_path);
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}



void model_game_setup( game_model *model, const char *pref_path )
{
	if(model) {
		jsm_read_commons(model->commons, pref_path);
		if(model->grid) { /* Free current grid if allocated */
			grid_free(model->c_rows, model->grid);
		}
		model->grid = grid_new(model->commons->rows, model->commons->cols);
		grid_rand(model->commons->rows, model->commons->cols, model->grid);
		model->c_rows = model->commons->rows;
		model->c_cols = model->commons->cols;
	} else { printf("MODEL [SETUP] : ERROR! Received null pointer to model\n"); }
}

void model_pref_setup( pref_model *model, const char *pref_path )
{
	if(model) {
		jsm_read_commons(model->commons, pref_path);
	} else { printf("MODEL [SETUP] : ERROR! Received null pointer to model\n"); }
}
