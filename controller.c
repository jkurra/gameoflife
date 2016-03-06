#include "controller.h"

void controller_model( view_model *model, int type )
{
	if(!model) {
		g_print("Unable to initialize, model was null. \n");
	}
	else {
		switch (model->type) { /* Determine which model is sending the signal. */
			case MENU: /* MAIN MENU */
				gtk_widget_destroy( GTK_WIDGET(model->menu->main_frame) );
				break;
			case GAME: /* GAME */
				if(model->game->timerid != -1) {
					g_source_remove( model->game->timerid );
					model->game->timerid = -1;
				}
				else {
						g_print("CONTROL [INIT]: Timer not available, skip removal. \n");
				}
				gtk_widget_destroy( GTK_WIDGET(model->game->main_frame) );
				break;
			case PREF: /* PREFERENCES */
				jsm_update_model( model );
				jsm_read_model( model );
				gtk_widget_destroy( GTK_WIDGET(model->pref->main_frame) );
				break;
			default:
				break;
		}
		model->type = type;
		model_init_view( model );
	}
}

G_MODULE_EXPORT
void on_settingsbutton_clicked( GtkButton *button, gpointer data )
{
	controller_model( (view_model*)data, PREF );
}

G_MODULE_EXPORT
void on_startgamebutton_clicked( GtkButton *button, gpointer data )
{
	controller_model( (view_model*)data, GAME );
}

G_MODULE_EXPORT
void on_menu_button_clicked( GtkButton *button, gpointer data )
{
	controller_model( (view_model*)data, MENU );
}

G_MODULE_EXPORT
void on_row_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->grid_x = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_col_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->grid_y = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_int_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->tick_t = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_rule1spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_rule2spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_rule3spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{

}
G_MODULE_EXPORT
void on_bg_colorbutton_color_set( GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	gtk_color_chooser_get_rgba ( button, &model->game->backGround );
}

G_MODULE_EXPORT
void on_cell_colorbutton_color_set( GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	gtk_color_chooser_get_rgba ( button, &model->game->cellColor );
}

/*
	deprecated
*/


G_MODULE_EXPORT
void on_pause_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model && model->game->timerid != -1) {
		g_source_remove(model->game->timerid);
		model->game->timerid = -1;
		g_print("pause pressed %d\n", model->game->timerid);
	}
}

G_MODULE_EXPORT
void on_resume_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model && model->game->timerid == -1) {
		model->game->timerid = g_timeout_add( model->game->tick_t, (GSourceFunc) model_grid_update, model );
		g_print("resume pressed %d\n", model->game->timerid);
	}
}

G_MODULE_EXPORT
void on_next_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_prev_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_up_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellY >= 5)
		model->game->startAtCellY-=5;
}

G_MODULE_EXPORT
void on_down_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellY < model->game->grid_y)
		model->game->startAtCellY+=5;
}

G_MODULE_EXPORT
void on_left_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellX >= 5)
		model->game->startAtCellX -= 5;
}

G_MODULE_EXPORT
void on_right_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellX < model->game->grid_x)
		model->game->startAtCellX += 5;
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
	//game_model *game = (game_model*)data;
	view_model *model = (view_model*)data;
	if(model->game->zoom > 1)
		model->game->zoom = model->game->zoom-1;
		//model_draw_game(game);
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
	//game_model *game = (game_model*)data;
	view_model *model = (view_model*)data;
	model->game->zoom = model->game->zoom+1;
	//model_draw_game(game);
}
