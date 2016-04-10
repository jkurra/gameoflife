#include "model.h"

view_model *model_view_new( int type, const char *pref_path )
{
	/* Allocate space for new view_model */
	view_model *model = (view_model*)malloc(sizeof(view_model));
	model->type = type;
	model->pref_path = pref_path;
	/* Initialize model variables and GTK parts initialization*/
	gtk_init(NULL, NULL);
	model->builder = gtk_builder_new();
	/* Initialize views_included in model */
	model->menu = model_menu_new();
	model->game = model_game_new();
	model->pref = model_game_new();

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
	game->grid 	 = NULL;
	game->live_a = NULL;
	game->live_d = NULL;
	/*
		Most integer values must be > 0 so they are set to -1
		This way it is easy to check if values are usable later.
	*/
	game->timerid = -1;
	game->max_x   = -1;
	game->max_y   = -1;

	game->infinite = -1;
	game->visible  = -1;
	game->cell_s 	= -1;		/* Size of each cell in the screen. */
	game->zoom   	= -1; 	/* How big or small cells appear on the screen.	*/
	game->tick_t  	= -1;
	game->timerid 	= -1;	/* Id of the widget containing update timer. */
	game->startAtCellX = -1; /* From which column to start drawing */
	game->startAtCellY = -1; /* From which row to start drawing */

	return game;
}

pref_model *model_pref_new()
{
	pref_model *pref = (pref_model*)malloc(sizeof(pref_model));
	return pref;
}

void model_view_free( view_model *model )
{
	if(model) {
		g_object_unref(G_OBJECT(model->builder));
		model_menu_free(model->menu);
		model_game_free(model->game);
		model_pref_free(model->pref);
		free(model->pref_path);
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n", time(NULL)); }
}

void model_menu_free( menu_model *model )
{
	if(model) {
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_game_free( game_model *model )
{
	if(model) {
		grid_free(model->max_y, model->grid);
		free(model->live_a);
		free(model->live_d);
		free(model);
	} else { printf("ERROR: Unable to free game_model, NULL model. \n"); }
}

void model_pref_free( pref_model *model)
{
	if(model) {
		free(model);
	} else { printf("ERROR: Unable to free view_model, NULL model. \n"); }
}

void model_init_view( view_model *model )
{
	if(model) {
		switch(model->type) {
			case MENU:
				printf("MODEL [INIT] : menu\n");
				view_menu_init(model->menu, model->builder);
				gtk_builder_connect_signals(model->builder, model);
				break;
			case GAME:
				printf("MODEL [INIT] : game\n");
				view_game_init(model->game, model->builder);
				gtk_builder_connect_signals(model->builder, model);
				break;
			case PREF:
				printf("MODEL [INIT] : pref\n");
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
{
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
{
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
{
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

void model_rwrite( view_model *model, int type )
{
	if(model) {
		switch( type ) {
			case MENU:
				printf("MODEL [WRITE] : menu\n");
				break;
			case GAME:
				printf("MODEL [WRITE] : game\n");
				model_game_save(model->game, model->pref_path);
				break;
			case PREF:
				printf("MODEL [WRITE] : pref\n");
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}

void model_game_save( game_model *model, const char *pref_path )
{
	/*
		Used json keys will be:
		"gridLength"
		"gridHeight"
		"tickInterval"
		"gridVisible"
		"backgroundColor"
		"cellColor"
	*/
	char *json = NULL;
	char x_size[10], y_size[10];
	char t_time[10];
	char vis[10];

	sprintf(x_size, "%d", model->max_x);
	sprintf(y_size, "%d", model->max_y);
	sprintf(t_time, "%d", model->tick_t);
	sprintf(vis, "%d", model->visible);

	gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
	gchar *cell = gdk_rgba_to_string(&model->cell_col);

	json = jsm_json_add(json, "gridLength", &x_size);
	json = jsm_json_add(json, "gridHeight", &y_size);
	json = jsm_json_add(json, "tickInterval", &t_time);
	json = jsm_json_add(json, "gridVisible", &vis);
	json = jsm_json_add(json, "backgroundColor", bgrn);
	json = jsm_json_add(json, "cellColor", cell);

	free(bgrn);
	free(cell);

	jsm_write(json, pref_path);

}

void model_game_setup( game_model *model, const char *pref_path )
{
	char *json = jsm_read(pref_path);
	if(model) { /* Free current grid if allocated */
		grid_free(model->max_y, model->grid);
		free(model->live_a);
		free(model->live_d);
	}
	char *tick_i, *row_s, *col_s, *bgCol, *frCol, *infi, *visi; /* free these */

	tick_i = jsm_json_val( json, "tickInterval", 3 );
	row_s  = jsm_json_val( json, "gridHeight", 3 );
	col_s  = jsm_json_val( json, "gridLength", 3 );
	visi   = jsm_json_val( json, "gridVisible", 3 );
	bgCol  = jsm_json_val( json, "backgroundColor", 3 );
	frCol  = jsm_json_val( json, "cellColor", 3 );
	/* Convert numeric values NOTE will be 0 if unable to convert */
	int row  = atoi(row_s);
	int col  = atoi(col_s);
	int vis  = atoi(visi);
	int tick = atoi(tick_i);
	if(tick<100) {
		printf("Warning, interval very small : %d\n", tick);
	}
	/* populate values for model */
	model->max_y  = row;
	model->max_x  = col;
	model->tick_t = tick;
	model->visible = vis;
	/* TODO: static modifiers for now */
	model->cell_s = 10.0;
	model->zoom   = 1.0;
	/* parse colors to model  */
	gdk_rgba_parse(&model->bgrn_col, bgCol);
	gdk_rgba_parse(&model->cell_col, frCol);
	/* Free dynamically allocated values */
	int *live_a1 = (int*)calloc(2, sizeof(int));
	int *live_d1 = (int*)calloc(1, sizeof(int));
	live_a1[0] = 3;
	live_a1[1] = 2;

	live_d1[0] = 3;
	model->live_a = live_a1;
	model->live_d = live_d1;
	g_print("rules %d %d: %d\n", model->live_a[0], model->live_a[1], model->live_d[0]);
	free(tick_i);
	free(row_s);
	free(col_s);
	free(visi);
	free(bgCol);
	free(frCol);
	free(json);
	/* Initialize new grid and give random values */
	model->grid = grid_new(model->max_x, model->max_y);
	grid_rand(model->max_x, model->max_y, model->grid);
	/* set drawing start point at beginning of grid */
	model->startAtCellX = 0;
	model->startAtCellY = 0;
}

void model_pref_setup( pref_model *model, const char *pref_path )
{
	char *json = jsm_read(pref_path);
	//free(model);
	char *tick_i, *row_s, *col_s, *bgCol, *frCol, *infi, *visi; /* free these */

	tick_i = jsm_json_val( json, "tickInterval", 3 );
	row_s  = jsm_json_val( json, "gridHeight", 3 );
	col_s  = jsm_json_val( json, "gridLength", 3 );
	visi   = jsm_json_val( json, "gridVisible", 3 );
	bgCol  = jsm_json_val( json, "backgroundColor", 3 );
	frCol  = jsm_json_val( json, "cellColor", 3 );
	/* Convert numeric values NOTE will be 0 if unable to convert */
	int row  = atoi(row_s);
	int col  = atoi(col_s);
	int vis  = atoi(visi);
	int tick = atoi(tick_i);

	/* populate values for model */
	model->max_y  = row;
	model->max_x  = col;
	model->tick_t = tick;
	model->visible = vis;
	/* TODO: static modifiers for now */
	model->cell_s = 10.0;
	model->zoom   = 1.0;
	/* parse colors to model  */
	gdk_rgba_parse(&model->bgrn_col, bgCol);
	gdk_rgba_parse(&model->cell_col, frCol);
	/* Free dynamically allocated values */

	free(tick_i);
	free(row_s);
	free(col_s);
	free(visi);
	free(bgCol);
	free(frCol);
	free(json);
}
