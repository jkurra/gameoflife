#include "model.h"

void model_init_view( view_model *model )
{
	switch( model->type ) {
		case MENU:{
			g_print("MODEL [INIT] : menu\n");
			view_menu_init( model );
			break; }
		case GAME:{
			g_print("MODEL [INIT] : game\n");
			view_game_init( model );
			break;}
		case PREF:{
			g_print("MODEL [INIT] : pref\n");
			view_pref_init( model );
			break;}
		default:
			break;
	}
}

void model_draw_view( view_model *model )
{
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
}

void model_close_view( view_model *model )
{
	switch( model->type ) {
		case MENU:
			gtk_widget_destroy( GTK_WIDGET(model->menu->main_frame) );
			break;
		case GAME:
			gtk_widget_destroy( GTK_WIDGET(model->game->main_frame) );
			break;
		case PREF:
			gtk_widget_destroy( GTK_WIDGET(model->pref->main_frame) );
			break;
		default:
			break;
	}
}

void model_update( view_model *model, int type )
{
	switch( type ) {
		case MENU:
			break;
		case GAME: {
			char *json = jsm_read(model->pref_path);
			printf("JSM [PARSE] : %s : ", json);
			if(json) {
				char *tick_time, *x_size, *y_size, *bgCol, *frCol,*infi, *visi; /* free these */
				tick_time = jsm_value(json, "TICK_TIME", 3);
				x_size = jsm_value(json, "X_SIZE", 3);
				y_size = jsm_value(json, "Y_SIZE", 3);
				bgCol  = jsm_value(json, "bgColor", 3);
				frCol  = jsm_value(json, "frColor", 3);
				visi   = jsm_value(json, "gridVis", 3);
				/*jsm_val( tick_time, json, "TICK_TIME" );
				jsm_val( x_size, 	  json, "X_SIZE" );
				jsm_val( y_size, 	  json, "Y_SIZE" );
				jsm_val( bgCol,  	  json, "bgColor" );
				jsm_val( frCol,     json, "frColor" );
				jsm_val( visi,      json, "gridVis" );
*/
				int x = atoi( x_size ); /* TODO  check if cast was succesfull */
				int y = atoi( y_size) ;
				int visible = atoi(visi) ;
				int time = atoi(tick_time);

				/* populate values for model */
				model->game->max_x = x;
				model->game->max_y = y;
				model->game->tick_t = time;

				/* parse colors to model  */
				gdk_rgba_parse( &model->game->bgrn_col, bgCol );
				gdk_rgba_parse( &model->game->cell_col , frCol );

				/* static modifiers for now */
				model->game->cell_s = 10.0;
				model->game->zoom   = 1.0;
				model->game->tick_t = 100;
				model->game->visible = visible;
				if(model->game->grid) {
					printf("free grid");
					grid_free(y, model->game->grid);

				}

				free(tick_time);
				free(x_size);
				free(y_size);
				free(bgCol);
				free(frCol);
				free(visi);

				model->game->grid = grid_new( x, y );
				grid_rand(x, y, model->game->grid);
				//grid_print(x, y, model->game->grid);
				/* set drawing start point at beginning of grid */
				model->game->startAtCellX = 0;
				model->game->startAtCellY = 0;

				free(json);
			}
			break;
		}
		case PREF:
			break;
		default:
			break;
	}
}
