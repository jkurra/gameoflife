#include "controller.h"

void controller_model(view_model *model, int type)
{
	//g_print("Buttonpressed, value : %s\n", model->pref_path);
	switch (model->type) { /* Determine which model is sending the signal. */
		case MENU: /* MAIN MENU */
			gtk_widget_destroy(GTK_WIDGET(model->menu->main_frame));
			break;
		case GAME: /* GAME */
			g_source_remove(model->game->timerid);
			
			gtk_widget_destroy(GTK_WIDGET(model->game->main_frame));
			break;
		case PREF: /* PREFERENCES */
			gtk_widget_destroy(GTK_WIDGET(model->pref->main_frame));
			break;
		default:
			break;
	}
	model->type = type;
	model_init_view( model );
}

G_MODULE_EXPORT
void on_menu_button_clicked( GtkButton *button, gpointer data )
{
	jsm_update_model( (view_model*)data );
	controller_model( (view_model*)data, MENU );
}

G_MODULE_EXPORT
void on_row_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->grid_x = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_col_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->grid_y = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_int_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
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
	gtk_color_button_get_color (button, &model->game->backGround);
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
void set_cell_color(GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	gtk_color_chooser_get_rgba (button,  &model->game->cellColor);

}

G_MODULE_EXPORT
void set_bg_color(GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	gtk_color_button_get_color (button, &model->game->backGround);
}

G_MODULE_EXPORT
void gridRowChange(GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->grid_x = gtk_spin_button_get_value_as_int (button);
	//g_print("button pressed %s\n", model->pref_path);
}

G_MODULE_EXPORT
void gridColumnChange(GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->grid_y = gtk_spin_button_get_value_as_int (button);
	//g_print("button pressed %s\n", model->pref_path);
}

G_MODULE_EXPORT
void tickIntervaChange(GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->tick_t = gtk_spin_button_get_value_as_int (button);
	g_print("button pressed %s\n", model->pref_path);
}
G_MODULE_EXPORT
void on_saveButton_clicked( GtkButton *button, gpointer data )
{
	//view_model *model = (view_model*)data;
	jsm_update_model( (view_model*)data );
}

G_MODULE_EXPORT
void on_prefAdd_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	//controller_model((view_model*)data, MENU);
	jsm_update_model( (view_model*)data );
	g_print("button pressed %s\n", model->pref_path);
}

G_MODULE_EXPORT
void on_switch5_clicked( GtkSwitch *button, gboolean  state, gpointer data )
{

	view_model *model = (view_model*)data;
	jsm_update_model( (view_model*)data );
	g_print("switch pressed \n");
}

G_MODULE_EXPORT
void one_menuButton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	jsm_update_model( (view_model*)data );
	controller_model((view_model*)data, MENU);
}

G_MODULE_EXPORT
void on_SettingsButton_clicked( GtkButton *button, gpointer data )
{
	controller_model((view_model*)data, PREF);
}

G_MODULE_EXPORT
void on_startGamebutton_clicked( GtkButton *button, gpointer data )
{
	controller_model((view_model*)data, GAME);
}

G_MODULE_EXPORT
void on_pause_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;

	g_source_remove(model->game->timerid);
	g_print("pause pressed %d\n", model->game->timerid);
}

G_MODULE_EXPORT
void on_resume_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	//model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model->game);
	g_print("resume pressed %d\n", model->game->timerid);
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
	model->game->startAtCellX += 5;
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	if(game->zoom > 1)
		game->zoom = game->zoom-1;
		//model_draw_game(game);
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	game->zoom = game->zoom+1;
	//model_draw_game(game);
}
