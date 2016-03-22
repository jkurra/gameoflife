#include "controller.h"

void controller_clean_menu( view_model *model )
{

}

void controller_clean_game( view_model *model )
{
	if(model && model->game->timerid != -1)
		g_source_remove(model->game->timerid);
		model->game->timerid = -1;
}

void controller_clean_pref( view_model *model )
{
	if(model)
		model_rwrite(model, GAME); /* Write changes to to file */
		model_update(model, GAME); /* update model with new changes */
}

void controller_model( view_model *model, int type )
{
	if(!model) {
		printf("CONTROL [ERROR] : Received null model pointer.\n");
	}
	else {
		switch (model->type) { /* Determine which model is sending the signal. */
			case MENU: /* MAIN MENU */
				controller_clean_menu(model);
				break;
			case GAME: /* GAME */
				controller_clean_game(model);
				break;
			case PREF: /* PREFERENCES */
				controller_clean_pref(model);
				break;
			default:
				break;
		}
		model_close_view(model);	/* Close currently selected view */
		model->type = type;			/* Select new view to be initialized */
		model_init_view(model); 	/* Initialize new view */
	}
}

G_MODULE_EXPORT
void on_settingsbutton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		controller_model(model, PREF);
}

G_MODULE_EXPORT
void on_startgamebutton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		controller_model(model, GAME);
}

G_MODULE_EXPORT
void on_menu_button_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		controller_model(model, MENU);
}

G_MODULE_EXPORT
void on_row_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->max_x = gtk_spin_button_get_value_as_int (button);
}

G_MODULE_EXPORT
void on_col_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->max_y = gtk_spin_button_get_value_as_int (button);
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
void on_switch2_state_set( GtkSwitch *sw, gboolean state, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model) {
		if(state == TRUE) {
			model->game->visible = 1;
		}
		else {
			model->game->visible = 0;
		}
	}

}

G_MODULE_EXPORT
void on_bg_colorbutton_color_set( GtkColorChooser *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		gtk_color_chooser_get_rgba ( button, &model->game->bgrn_col );

}

G_MODULE_EXPORT
void on_cell_colorbutton_color_set( GtkColorChooser *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		gtk_color_chooser_get_rgba ( button, &model->game->cell_col );
}

G_MODULE_EXPORT
void on_nextButton_clicked( GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		grid_next(model->game->max_x, model->game->max_y, model->game->grid, model->game->live_a,2, model->game->live_d, 1);
		model_draw_view(model);
}

/*
	deprecated
*/

G_MODULE_EXPORT
void on_pause_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model && model->game->timerid != -1) {
		//g_source_remove(model->game->timerid);
		//model->game->timerid = -1;
		g_print("pause pressed %d\n", model->game->timerid);
	}
}

G_MODULE_EXPORT
void on_resume_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model && model->game->timerid == -1) {
		//model->game->timerid = g_timeout_add( model->game->tick_t, (GSourceFunc) model_grid_update, model );
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
		model_draw_view( model );
}

G_MODULE_EXPORT
void on_down_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellY < model->game->max_y)
		model->game->startAtCellY+=5;
		model_draw_view( model );
}

G_MODULE_EXPORT
void on_left_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellX >= 5)
		model->game->startAtCellX -= 5;
		model_draw_view( model );
}

G_MODULE_EXPORT
void on_right_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellX < model->game->max_x)
		model->game->startAtCellX += 5;
		model_draw_view( model );
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	//if(model->game->zoom > 1)
		model->game->zoom = model->game->zoom-0.2;
		model_draw_view( model );
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->zoom = model->game->zoom+0.2;
	model_draw_view( model );
}
