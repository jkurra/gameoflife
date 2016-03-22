#include "model.h"

void model_init_view( view_model *model )
{
	if(model) {
		switch( model->type ) {
			case MENU:
				printf("MODEL [INIT] : menu\n");
				view_menu_init( model );
				break;
			case GAME:
				printf("MODEL [INIT] : game\n");
				view_game_init( model );
				break;
			case PREF:
				printf("MODEL [INIT] : pref\n");
				view_pref_init( model );
				break;
			default:
				break;
		}
	} else { printf("MODEL [INIT] : ERROR! Received null pointer to model\n"); }
}

void model_draw_view( view_model *model )
{
	if(model) {
		switch( model->type ) {
			case MENU:
				gtk_widget_queue_draw( model->menu->main_frame );
				break;
			case GAME:
				gtk_widget_queue_draw( model->game->main_frame );
				break;
			case PREF:
				gtk_widget_queue_draw( model->pref->main_frame );
				break;
			default:
				break;
		}
	} else { printf("MODEL [DRAW] : ERROR! Received null pointer to model\n"); }
}

void model_close_view( view_model *model )
{
	if(model) {
		switch( model->type ) {
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
				printf("MODEL [UPDATE] : pref\n");
				break;
			case GAME:
				printf("MODEL [UPDATE] : game\n");
				model_game_setup(model->game, model->pref_path);
				break;
			case PREF:
				printf("MODEL [UPDATE] : pref\n");
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}

void model_rwrite( view_model *model, int type)
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
	char *json = NULL;
	char x_size[10];
	char y_size[10];
	char t_time[10];
	char vis[10];

	sprintf(x_size, "%d", model->max_x);
	sprintf(y_size, "%d", model->max_y);
	sprintf(t_time, "%d", model->tick_t);
	sprintf(vis, "%d", model->visible);

	gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
	gchar *cell = gdk_rgba_to_string(&model->cell_col);

	json = jsm_json_add(json, "X_SIZE", &x_size);
	json = jsm_json_add(json, "Y_SIZE", &y_size);
	json = jsm_json_add(json, "TICK_TIME", &t_time);
	json = jsm_json_add(json, "gridVis", &vis);
	json = jsm_json_add(json, "bgColor", bgrn);
	json = jsm_json_add(json, "frColor", cell);

	free(bgrn);
	free(cell);

	int s = jsm_write(json, pref_path);
	if(s != JSM_OK) {
		printf("write failed");
	}
}

void model_game_setup( game_model *model, const char *pref_path )
{
	char *json = jsm_read(pref_path);
	if(model->grid) { /* Free current grid if allocated */
		grid_free(model->max_y, model->grid);
	}
	char *tick_i, *row_s, *col_s, *bgCol, *frCol, *infi, *visi; /* free these */

	tick_i = jsm_json_val( json, "TICK_TIME", 3 );
	row_s  = jsm_json_val( json, "Y_SIZE", 3 );
	col_s  = jsm_json_val( json, "X_SIZE", 3 );
	visi   = jsm_json_val( json, "gridVis", 3 );
	bgCol  = jsm_json_val( json, "bgColor", 3 );
	frCol  = jsm_json_val( json, "frColor", 3 );
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
	/* Initialize new grid and give random values */
	model->grid = grid_new(model->max_x, model->max_y);
	grid_rand(model->max_x, model->max_y, model->grid);
	/* set drawing start point at beginning of grid */
	model->startAtCellX = 0;
	model->startAtCellY = 0;
}
