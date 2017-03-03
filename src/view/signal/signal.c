#include "signal.h"
#include "../view.h"
#include "../../model/viewobject.h"

gboolean view_timer_update( GameModel *model );

/* COMMON SIGNALS */

G_MODULE_EXPORT
on_MainWindow_destroy( GtkWidget *widget, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_quit(object);
	}
}

/* SINGALS FOR MENU VIEW */

G_MODULE_EXPORT
void on_ToGame_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, GAME);
	} else {
		g_print("NULL Gameobject\n");
	}
}

G_MODULE_EXPORT
void on_ToPref_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, PREF);
	} else {
		g_print("NULL Prefobject\n");
	}
}

G_MODULE_EXPORT
on_QuitAll_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	if(object) {
		ViewObject_quit(object);
	}
}

/* SINGALS FOR GAME VIEW */

G_MODULE_EXPORT
void on_ToMenu_clicked( GtkButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		ViewObject_select(object, MENU);
	} else {g_print("NULL MENUobject\n");}
}

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
    grid_rand( model->g_model->rows, model->g_model->cols, model->g_model->grid );

    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_ClearGrid_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    model->g_model->grid = grid_empty(model->g_model->grid, model->g_model->rows, model->g_model->cols);

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

    grid_next(model->g_model->rows, model->g_model->cols, model->g_model->grid, model->g_model->live_a, 2, model->g_model->live_d, 1);
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
    model->g_model->grid = grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, tmpRows, model->g_model->cols );
    model->g_model->rows = tmpRows;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_SetCols_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpCols = gtk_spin_button_get_value (button);
    model->g_model->grid = grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, model->g_model->rows, tmpCols);
    model->g_model->cols = tmpCols;
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

int GameArea_x_pos( gpointer data, float x, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int max_x = model->g_model->rows,
		cur_x = 0;

    float x_start = 5.0;
    int x_cell = 0;

    float x_max = 0;
    float x_min = 0;
    x_cell += model->g_model->startY;

    for(cur_x=model->g_model->startX; cur_x<max_x; cur_x++) {
		x_max = x_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += model->g_model->cell_s*model->g_model->zoom;
        x_start += model->g_model->spacing; // space between cells
    }
	g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",x, x_min, x_max);
    return pos;
}

int GameArea_y_pos( gpointer data, float y, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int	max_y = model->g_model->cols, cur_x = 0;

    float y_start = 5.0;
    int   x_cell = 0;

    float x_max = 0;
    float x_min = 0;

    x_cell += model->g_model->startX;

    for(cur_x=model->g_model->startY; cur_x<max_y; cur_x++) {
		x_max = y_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = y_start;
        if(y>x_min && y<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        y_start += model->g_model->cell_s*model->g_model->zoom;
        y_start += model->g_model->spacing; // space between cells

    }        g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",y, x_min, x_max);
    return pos;
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
		g_print("button pressed on game : x:%f, y:%d.\n", event->x, event->y);
		if(posx >= 0 && posy >= 0) {
			ViewObject *model = (ViewObject*)data;
			grid_switch_cell( model->g_model->grid, posx, posy );
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

G_MODULE_EXPORT
void window_close( GtkWidget widget, gpointer data )
{
	//gtk_main_quit();
}

/* SINGALS FOR MENU VIEW */


/* SINGALS FOR PREF VIEW */

on_SetBgColor_color_set( GtkColorButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( button, &object->g_model->bgrn_col );

}

on_SetCellColor_color_set( GtkColorButton *button, gpointer data )
{
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( button, &object->g_model->cell_col );
}

on_ShowGrid_state_set( GtkSwitch *widget, gboolean   state, gpointer data )
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
