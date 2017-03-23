#include "signal.h"
#include "../view.h"
#include "../../model/viewobject.h"

gboolean view_timer_update( GameModel *model );

/* COMMON SIGNALS */

G_MODULE_EXPORT
void on_MainWindow_destroy( GtkWidget *widget, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		if(gtk_main_level() > 0) {
			gtk_main_quit();
		}
		//ViewObject_quit(object);
	} else { g_print("%s", log_message("SIGNAL", "ViewObject was NULL when attempting to destroy MainWindow. ")); }
}

G_MODULE_EXPORT
void on_ToGame_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
	//	g_print(log_message("SIGNAL", "Move to GameView."));
		ViewObject_select(object, GAME);
	} else { g_print("%s", log_message("SIGNAL", "ViewObject was NULL when opening GameView")); }
}

G_MODULE_EXPORT
void on_ToPref_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		g_print("%s", log_message("SIGNAL", "Move to GameView."));
		ViewObject_select(object, PREF);
	} else { g_print("%s", log_message("SIGNAL", "ViewObject was NULL when opening PrefView")); }
}

G_MODULE_EXPORT
void on_ToMenu_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		g_print("%s", log_message("SIGNAL", "Move to GameView."));
		ViewObject_select(object, MENU);
	} else { g_print("%s", log_message("SIGNAL", "ViewObject was NULL when opening MenuView")); }
}

/* SINGALS FOR MENU VIEW */


/* SINGALS FOR GAME VIEW */

G_MODULE_EXPORT
void on_SetPlay_clicked ( GtkButton *button, gpointer data )
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
void on_RandGrid_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    //grid_rand( model->g_model->rows, model->g_model->cols, model->g_model->grid );
	Grid_rand( model->g_model->grid );
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_ClearGrid_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    Grid_empty(model->g_model->grid );

    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_NextTurn_clicked( GtkButton *button, gpointer data )
{
	ViewObject *model = (ViewObject*)data;
	model->g_model->c_step++;
	GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->g_model->builder, "step_counter"));
	char str[20];
	sprintf(str, "%d", model->g_model->c_step);
	gtk_label_set_text(GTK_LABEL(step_count), str);
	Grid_next(model->g_model->grid, model->g_model->ruleset);
//    grid_next(model->g_model->rows, model->g_model->cols, model->g_model->grid, model->g_model->live_a, 2, model->g_model->live_d, 1);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_PrevTurn_clicked( GtkButton *button, gpointer data )
{
	//TODO: Not yet implemented
}

G_MODULE_EXPORT
void on_SetRows_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpRows = gtk_spin_button_get_value (button);
    Grid_resize(model->g_model->grid , tmpRows, model->g_model->grid->cols); //grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, tmpRows, model->g_model->cols );
    //model->g_model->grid->rows = tmpRows;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_SetCols_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpCols = gtk_spin_button_get_value (button);
    Grid_resize(model->g_model->grid , model->g_model->grid->rows, tmpCols);//grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, model->g_model->rows, tmpCols);
    //model->g_model->grid->cols = tmpCols;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_SetInterval_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
	int interval = gtk_spin_button_get_value (button);
	model->g_model->interval = interval;

	if(model->g_model->timerid != -1) {
		g_source_remove(model->g_model->timerid);
		model->g_model->timerid = -1;
		model->g_model->timerid = g_timeout_add(model->g_model->interval, (GSourceFunc) view_timer_update, model->g_model);
		//model->g_model->timerid = g_timeout_add(model->g_model->interval, (GSourceFunc)view_timer_update, model);
	}
	GameModel_save(model->g_model);
}

G_MODULE_EXPORT
void on_drawingarea1_button_press_event( GtkWidget *widget, GdkEventButton *event, gpointer data )
{
	GtkAllocation widget_alloc;
	gtk_widget_get_allocation(GTK_WIDGET(widget), &widget_alloc);
	int maxx = widget_alloc.width,
		maxy = widget_alloc.height;

		int posx = GameArea_x_pos(data, event->x, maxx, maxy);// get_x_position( widget, data, event->x);
		int posy = GameArea_y_pos(data, event->y, maxx, maxy);
	//	g_print("button pressed on game : x:%f, y:%d.\n", event->x, event->y);
		if(posx >= 0 && posy >= 0) {
			ViewObject *model = (ViewObject*)data;
			Grid_switch_cell( model->g_model->grid, posy, posx );
			gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
		} else {
			g_print("positions out of range.\n");
		}
}

G_MODULE_EXPORT
void on_drawingarea1_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{

}

/* UMOV START User movement signals on game grid */

G_MODULE_EXPORT
void on_ZoomIn_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	object->g_model->zoom = object->g_model->zoom+0.2;
    GameModel_save(object->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_ZoomOut_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	object->g_model->zoom = object->g_model->zoom-0.2;
    GameModel_save(object->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_MoveUp_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object->g_model->startX -1 > 0) {
		object->g_model->startX -= 1;
		gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
	}
}

G_MODULE_EXPORT
void on_MoveDown_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	object->g_model->startX += 1;
	gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_MoveLeft_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	if(object->g_model->startY -1 > 0) {
		object->g_model->startY -= 1;
		gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
	}
}

G_MODULE_EXPORT
void on_MoveRight_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	object->g_model->startY += 1;
	gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

/* UMOV END */

/* SINGALS FOR MENU VIEW */

G_MODULE_EXPORT
void on_QuitAll_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		gtk_widget_destroy(GTK_WIDGET(object->m_model->main_frame));
	}
	//TODO: call destroy oin main widget.
}

/* SINGALS FOR PREF VIEW */

G_MODULE_EXPORT
void on_SetBgColor_color_set( GtkColorButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(button), &object->g_model->bgrn_col );

}

G_MODULE_EXPORT
void on_SetCellColor_color_set( GtkColorButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(button), &object->g_model->cell_col );
}

G_MODULE_EXPORT
void on_ShowGrid_state_set( GtkSwitch *widget, gboolean   state, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(state == 1) {
		object->g_model->visible = 1;
	} else { object->g_model->visible = 0; }
	GameModel_save(object->g_model);
}

gboolean view_timer_update( GameModel *model )
{
	if(model) {
		Grid_next(model->grid, model->ruleset);
		//grid_next(model->rows, model->cols, model->grid, model->live_a, 2, model->live_d, 1);
		model->c_step++;
		GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
		char str[20];
		sprintf(str, "%d", model->c_step);
		gtk_label_set_text(GTK_LABEL(step_count), str);
        //view_draw((Model*)model);
		// const gchar *name = gtk_widget_get_name(GTK_WIDGET(model->main_frame));
		//g_print("refresh widget:%s \n", name);

		gtk_widget_queue_draw(GTK_WIDGET(model->game_frame));
	}
	return TRUE;
}
