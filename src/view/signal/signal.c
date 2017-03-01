#include "signal.h"
#include "../view.h"
#include "../../model/viewobject.h"

/* SINGALS FOR MENU VIEW */
G_MODULE_EXPORT
void on_startGamebutton_clicked ( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, GAME);
	}else {
		g_print("NULL Gameobject\n");
	}
}

G_MODULE_EXPORT
void on_settingsButton_clicked ( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, PREF);
	} else {
		g_print("NULL Prefobject\n");
	}
}

/* SINGALS FOR GAME VIEW */
gboolean view_timer_update( GameModel *model )
{
	if(model) {
		grid_next(model->rows, model->cols, model->grid, model->live_a, 2, model->live_d, 1);
		model->c_step++;
		GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
		char str[20];
		sprintf(str, "%d", model->c_step);
		gtk_label_set_text(GTK_LABEL(step_count), str);
        //view_draw((Model*)model);
		// const gchar *name = gtk_widget_get_name(GTK_WIDGET(model->main_frame));
		//g_print("refresh widget:%s \n", name);
		gtk_widget_queue_draw(GTK_WIDGET(model->main_frame));
	}
	return TRUE;
}

G_MODULE_EXPORT
void on_start_pause_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    if(model->g_model->timerid != -1) {
        g_source_remove(model->g_model->timerid);
        model->g_model->timerid = -1;
    } else {
        model->g_model->timerid = g_timeout_add(model->g_model->interval, (GSourceFunc) view_timer_update, model->g_model);
    }
}

G_MODULE_EXPORT
void on_drawingarea1_button_press_event( GtkWidget *widget, GdkEventButton *event, gpointer data )
{

}

G_MODULE_EXPORT
void on_drawingarea1_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{

}

G_MODULE_EXPORT
void on_prev_button_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_menu_button_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, MENU);
	} else {g_print("NULL MENUobject\n");}
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
    GameModel *model = (GameModel*)data;
	model->zoom = model->zoom+0.2;
    GameModel_save(model);
    //gtk_widget_queue_draw(GTK_WIDGET(model->main_frame));
	//view_draw( (Model*)model );
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
    GameModel *model = (GameModel*)data;
	model->zoom = model->zoom-0.2;
    GameModel_save(model);
    //gtk_widget_queue_draw(GTK_WIDGET(model->main_frame));
	//view_draw( (Model*)model );
}

G_MODULE_EXPORT
void on_up_clicked( GtkButton *button, gpointer data )
{/*
    GameModel *model = (GameModel*)data;
	if(model->game->startAtCellY < model->game->commons->rows) {
		model->game->startAtCellY += 1;
		view_draw( model );
	}
*/
}

G_MODULE_EXPORT
void on_down_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_left_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void on_right_clicked( GtkButton *button, gpointer data )
{

}

G_MODULE_EXPORT
void window_close( GtkWidget widget, gpointer data )
{
	//gtk_main_quit();
}

G_MODULE_EXPORT
void on_next_button_clicked( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    grid_next(model->g_model->rows, model->g_model->cols, model->g_model->grid, model->g_model->live_a, 2, model->g_model->live_d, 1);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
    g_print("next clicked");
}

G_MODULE_EXPORT
void on_randomize_button_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    grid_rand( model->g_model->rows, model->g_model->cols, model->g_model->grid );

    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
    g_print("randomize clicked");
}

G_MODULE_EXPORT
void on_clear_button_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    model->g_model->grid = grid_empty(model->g_model->grid, model->g_model->rows, model->g_model->cols);
    //update_from_Model_to_GameArea(model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
    g_print("clear clicked");
}

G_MODULE_EXPORT
void on_grid_rows_spinButton_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpRows = gtk_spin_button_get_value (button);
    model->g_model->grid = grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, tmpRows, model->g_model->cols );
    model->g_model->rows = tmpRows;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
    g_print("row added");
}

G_MODULE_EXPORT
void on_grid_cols_spinButton_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpCols = gtk_spin_button_get_value (button);
    model->g_model->grid = grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, model->g_model->rows, tmpCols);
    model->g_model->cols = tmpCols;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));

}

G_MODULE_EXPORT
void on_interval_spinbutton_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
	int interval = gtk_spin_button_get_value (button);
	model->g_model->interval = interval;
	GameModel_save(model->g_model);

	if(model->g_model->timerid != -1) {
		g_source_remove(model->g_model->timerid);
		model->g_model->timerid = -1;
		model->g_model->timerid = g_timeout_add(model->g_model->interval, (GSourceFunc)view_timer_update, model);
	}

}

/* SINGALS FOR MENU VIEW */


/* SINGALS FOR PREF VIEW */
