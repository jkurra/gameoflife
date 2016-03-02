#include "model.h"

gboolean model_grid_update( view_model *model )
{
//	g_print("testing");
	grid_next(model->game->grid_x, model->game->grid_y, model->game->grid);
	//print_game(game_data->grid);
	//gtk_widget_queue_draw (game_data->win);
//g_print("testing");
 		//model_draw_game(game_data);
		model_draw_view(model);
    return TRUE;
}

void model_init_view( view_model *model )
{
	switch( model->type ) {
		case MENU:
			g_print("INIT: menu,\n");
			view_menu_init( model );
			break;
		case GAME:
			g_print("INIT: game,\n");
			jsm_read_model( model );
			//model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model);
			view_game_init( model );
			break;
		case PREF:
			g_print("INIT: preferences,\n");
			view_pref_init( model );
			break;
		default:
			break;
	}
}

void model_draw_view( view_model *model )
{
	switch( model->type ) {
		case MENU:
			gtk_widget_queue_draw (model->menu->main_frame);
			break;
		case GAME:
			gtk_widget_queue_draw (model->game->main_frame);
			break;
		case PREF:
			gtk_widget_queue_draw (model->pref->main_frame);
			break;
		default:
			break;
	}
}
