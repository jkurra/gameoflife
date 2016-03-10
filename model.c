#include "model.h"

void model_init_view( view_model *model )
{
	switch( model->type ) {
		case MENU:
			g_print("MODEL [INIT] : menu\n");
			view_menu_init( model );
			break;
		case GAME:
			g_print("MODEL [INIT] : game\n");
			view_game_init( model );
			break;
		case PREF:
			g_print("MODEL [INIT] : pref\n");
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
