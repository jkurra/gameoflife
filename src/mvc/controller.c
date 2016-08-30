#include "controller.h"
#include "drawing/gamearea.h"

void controller_clean_menu( view_model *model )
{

}

void controller_clean_game( view_model *model )
{
	if(model && model->game->commons->timerid != -1) {
		model_remove_timer(model, model->game->commons->timerid);
	} else { }
}

void controller_clean_pref( view_model *model )
{
	/*
		Since user left preferences, write changed values to json file.
		NOTICE that values are already changed to model at this point
	*/
	if(model) {
		config_write(model->game->commons, NULL);
	} else { }
}

void controller_model( view_model *model, int type )
{
	if(model) {
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
		view_close(model);	/* Close currently selected view */

		model_update(model, GAME);
		model_update(model, PREF);

		view_init(model, type); 	/* Initialize new view */
	} else { printf("[%s] Controller received NULL model.", log_timestamp()); }
}

G_MODULE_EXPORT
void on_reduce_interval_button_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model) {
		if(model->game->commons->interval-100 > 100) {
			model->game->commons->interval -= 100;
			/* Update time to use new values  */
			model_remove_timer( model, model->game->commons->timerid );
			model_attach_timer( model, model->game->commons->timerid );
		}
	}
}

G_MODULE_EXPORT
void on_increase_interval_button_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model) {
		if(model->game->commons->interval-100 < 5000) {
			model->game->commons->interval += 100;
			/* Update time to use new values  */
			model_remove_timer( model, model->game->commons->timerid );
			model_attach_timer( model, model->game->commons->timerid );
		}
	}
}

G_MODULE_EXPORT
void on_settingsButton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		controller_model(model, PREF);
}

G_MODULE_EXPORT
void on_startGamebutton_clicked( GtkButton *button, gpointer data )
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
void on_randomize_button_clicked(GtkButton *button, gpointer data)
{//g_print("Rand pressed \n");
	view_model *model = (view_model*)data;
	if(model)
		grid_rand(model->commons->rows, model->commons->cols, model->game->grid);
		gtk_widget_queue_draw( GTK_WIDGET(model->game->main_frame) );
}

G_MODULE_EXPORT
void on_grid_cols_spinButton_value_changed( GtkSpinButton *button, gpointer data )
{	//g_print("Cols pressed %d\n", gtk_spin_button_get_value_as_int(button));
	view_model *model = (view_model*)data;
	if(model) {
		int tmp_cols = -1;
		tmp_cols = model->game->c_cols;
		model->game->commons->cols = gtk_spin_button_get_value_as_int(button);
		model->game->grid = grid_resize(model->game->grid, model->game->c_rows, tmp_cols, model->game->commons->rows, model->game->commons->cols);
		model->game->c_rows = model->commons->rows;
		model->game->c_cols = model->commons->cols;
		config_write(model->game->commons, model->commons->conf);
		gtk_widget_queue_draw(GTK_WIDGET(model->game->main_frame));
	}
}

G_MODULE_EXPORT
void on_drawingarea1_button_press_event (GtkWidget *widget, GdkEventButton *event, gpointer data)
{


	GtkAllocation widget_alloc;
	gtk_widget_get_allocation(GTK_WIDGET(widget), &widget_alloc);
	int maxx = widget_alloc.width,
		maxy = widget_alloc.height;

		int posx = GameArea_x_pos(data, event->x, maxx, maxy);// get_x_position( widget, data, event->x);
		int posy = GameArea_y_pos(data, event->y, maxx, maxy);
	g_print("button pressed on game : x:%d, y:%d.\n", posx, posy);
	if(posx >= 0 && posy >= 0) {
		view_model *model = (view_model*)data;
		grid_switch_cell( model->game->grid, posx, posy );
		gtk_widget_queue_draw(GTK_WIDGET(model->game->main_frame));
	}else {
		g_print("positions out of range.\n");
	}
}

G_MODULE_EXPORT
void on_drawingarea1_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{

	//g_print("button released on game.\n");
}

G_MODULE_EXPORT
void on_interval_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model) {
		if(model->game->commons->interval-100 < 5000) {
			model->game->commons->interval =  gtk_spin_button_get_value_as_int(button);
			config_write(model->game->commons, model->commons->conf);
			if(model->game->commons->timerid != -1) { // Only update timer if game is running
				model_remove_timer( model, model->game->commons->timerid );
				model_attach_timer( model, model->game->commons->timerid );
			}
		}
	}
}

G_MODULE_EXPORT
void on_grid_rows_spinButton_value_changed ( GtkSpinButton *button, gpointer data )
{	//g_print("Rows pressed %d\n", gtk_spin_button_get_value_as_int(button));
	view_model *model = (view_model*)data;
	if(model) {
		int tmp_rows = -1;
		tmp_rows = model->game->c_rows;
		model->game->commons->rows = gtk_spin_button_get_value_as_int(button);
		model->game->grid = grid_resize(model->game->grid, tmp_rows, model->game->c_cols, model->game->commons->rows, model->game->commons->cols);
		model->game->c_rows = model->commons->rows;
		model->game->c_cols = model->commons->cols;
		config_write(model->game->commons, model->commons->conf);
		gtk_widget_queue_draw(GTK_WIDGET(model->game->main_frame));
	}
}


G_MODULE_EXPORT
void on_row_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->commons->rows = gtk_spin_button_get_value_as_int(button);
}

G_MODULE_EXPORT
void on_col_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->commons->cols = gtk_spin_button_get_value_as_int(button);
}

G_MODULE_EXPORT
void on_int_spinbutton_value_changed ( GtkSpinButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		model->game->commons->interval = gtk_spin_button_get_value_as_int(button);
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
			model->game->commons->visible = 1;
		}
		else {
			model->game->commons->visible = 0;
		}
	}

}

G_MODULE_EXPORT
void on_bg_colorbutton_color_set( GtkColorChooser *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		gtk_color_chooser_get_rgba ( button, &model->game->commons->bgrn_col );

}

G_MODULE_EXPORT
void on_cell_colorbutton_color_set( GtkColorChooser *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		gtk_color_chooser_get_rgba ( button, &model->game->commons->cell_col );
}

G_MODULE_EXPORT
void on_nextButton_clicked( GtkColorButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model)
		//g_print("rules1 %d %d: %d\n", model->game->commons->rows, model->game->commons->live_a[1], model->game->commons->live_d[0]);
		grid_next(model->game->commons->rows, model->game->commons->cols, model->game->grid, model->game->commons->live_a,2, model->game->commons->live_d, 1);
		model->game->c_step++;
		view_draw(model);
}

/*
	deprecated
*/

G_MODULE_EXPORT
void on_start_pause_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model) {
		if( model->game->commons->timerid == -1) {
			char *newlabel = "||";
			GtkWidget *button = GTK_WIDGET ( gtk_builder_get_object(model->builder, "start_pause_button") );
			gtk_button_set_label(GTK_BUTTON(button), newlabel);

			model_attach_timer(model, model->game->commons->timerid);
			//g_print("start pressed %d\n", model->game->commons->timerid );

		}
		else {
			char *newlabel = ">";
			GtkWidget *button = GTK_WIDGET ( gtk_builder_get_object(model->builder, "start_pause_button") );
			gtk_button_set_label(GTK_BUTTON(button), newlabel);

			model_remove_timer( model, model->game->commons->timerid );
			//g_print("pause pressed %d\n", model->game->commons->timerid);
		}
	}
}

G_MODULE_EXPORT
void on_themebox_changed(GtkComboBoxText *widget, gpointer data) {
	//g_print(" themebox chaned \n");
	view_model *model = (view_model*)data;
	//g_print(" test is selected %s \n", gtk_combo_box_text_get_active_text(widget));
	if(model) {
		theme_select(model->game->commons->themes, gtk_combo_box_text_get_active_text(widget));
		//controller_model( model, PREF );

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
	//if(model->game->startAtCellX >= 5){
		model->game->startAtCellX-=1;
		view_draw( model );
	//}
}

G_MODULE_EXPORT
void on_down_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellX < model->game->commons->cols)
		model->game->startAtCellX += 1;
		view_draw( model );
}

G_MODULE_EXPORT
void on_left_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
		//if(model->game->startAtCellY >= 5){
		model->game->startAtCellY -= 1;
		view_draw( model );//}
}

G_MODULE_EXPORT
void on_right_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	if(model->game->startAtCellY < model->game->commons->rows)
		model->game->startAtCellY += 1;
		view_draw( model );
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->commons->zoom = model->game->commons->zoom-0.2;
	view_draw( model );
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->commons->zoom = model->game->commons->zoom+0.2;
	view_draw( model );
}
