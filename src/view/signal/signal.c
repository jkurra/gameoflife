#include "signal.h"
#include "../view.h"
#include "../../model/viewobject.h"

int signal_GameView_connect( GtkBuilder *builder, GameModel *model )
{
	int err = 1; //TODO: change value if value init fails

	if(builder && model) {
		GtkWidget *overlay    = GTK_WIDGET(gtk_builder_get_object(builder, "overlay3"));
		GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(builder, "step_counter"));
		GtkWidget *row_button = GTK_WIDGET(gtk_builder_get_object(builder, "SetRows"));
		GtkWidget *col_button = GTK_WIDGET(gtk_builder_get_object(builder, "SetCols"));
		GtkWidget *int_button = GTK_WIDGET(gtk_builder_get_object(builder, "SetInterval"));
		GtkWidget *dead_switch = GTK_WIDGET(gtk_builder_get_object(builder, "DeadCellSwitch"));

		GtkWidget *color_bb = GTK_WIDGET(gtk_builder_get_object(builder, "BagckgroundColor"));
		GtkWidget *color_bc = GTK_WIDGET(gtk_builder_get_object(builder, "CellColor"));

		/* Get step value as character string from step counter from model. */
		char str[20];
		sprintf(str, "%d", model->c_step);
		/* Assign UI spinbutton values from model */
		gtk_label_set_text(GTK_LABEL(step_count), str);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(col_button), model->grid->gArray->cols);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(row_button), model->grid->gArray->rows);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(int_button), model->interval);
		gtk_switch_set_state(GTK_SWITCH(dead_switch), model->visible);
		/* Assign UI color chooser values from model */
		gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_bb), &model->bgrn_col);
		gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_bc), &model->cell_col);
	}

	return err;
}

int signal_MenuView_connect( GtkBuilder *builder, GameModel *model )
{
	int err = 1; //TODO: change value if value init fails
	//TODO: add widget updates as needed.
	return err;
}

int signal_PrefView_connect( GtkBuilder *builder, GameModel *model )
{
	int err = 1; //TODO: change value if value init fails
	//TODO: add widget updates as needed.
	return err;
}

int signal_connect( GtkBuilder *builder, Model *model )
{
	int err = 1;

	switch (model->type) {
		case GAME: /* Initialize game view */
			err = signal_GameView_connect(builder, (GameModel*)model);
            break;
        case MENU:
			err = signal_MenuView_connect(builder, (GameModel*)model);
            break;
        case PREF:
			err = signal_PrefView_connect(builder, (GameModel*)model);
            break;
        default:
            break;
	}

	return err;
}

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
void on_CellColor_clicked ( GtkButton *button, gpointer data )
{
	g_print("Color selected.");
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(button), &object->g_model->cell_col );
	GameModel_save(object->g_model);
//	gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_BagckgroundColor_clicked ( GtkButton *button, gpointer data )
{
	g_print("Color selected.");
	ViewObject *object = (ViewObject*)data;
	gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(button), &object->g_model->bgrn_col );
	GameModel_save(object->g_model);
	//gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_SetPlay_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    if(model->g_model->timerid != -1) {
		model->g_model->is_playing = 0;
        g_source_remove(model->g_model->timerid);
        model->g_model->timerid = -1;
    } else {
		model->g_model->is_playing = 1;
        model->g_model->timerid = g_timeout_add(33, (GSourceFunc) view_timer_update, model->g_model);
		ViewObject_start_grid_loop(model);
	}
}


G_MODULE_EXPORT
void on_RandGrid_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    //grid_rand( model->g_model->rows, model->g_model->cols, model->g_model->grid );
	Grid_mod(model->g_model->grid, RANDOM,  NULL);
	//Grid_rand( model->g_model->grid );
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_ClearGrid_clicked ( GtkButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;
    //GridArray_empty(model->g_model->grid );
	Grid_mod( model->g_model->grid, EMPTY, NULL );
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

	Grid_ptr data1;
	data1.row = tmpRows; //model->g_model->grid->gArray->rows;
	data1.col = model->g_model->grid->gArray->cols;
//	data.rules = model->g_model->grid->gArray->rules;
//	printf("new Grid size: x:%d, y:%d \n", data1.row, data1.col);
	Grid_mod( model->g_model->grid, RESIZE, &data1);
//    Grid_resize(model->g_model->grid , tmpRows, model->g_model->grid->cols); //grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, tmpRows, model->g_model->cols );
    //model->g_model->grid->rows = tmpRows;
    GameModel_save(model->g_model);
    gtk_widget_queue_draw(GTK_WIDGET(model->g_model->main_frame));
}

G_MODULE_EXPORT
void on_DeadCellSwitch_state_set( GtkSwitch *widget, gboolean state, gpointer data )
{
	g_print("State set.");
	ViewObject *object = (ViewObject*)data;

	if(state == 1) {
		object->g_model->visible = 1;
	} else { object->g_model->visible = 0; }
	GameModel_save(object->g_model);
	gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
}

G_MODULE_EXPORT
void on_SetCols_value_changed( GtkSpinButton *button, gpointer data )
{
    ViewObject *model = (ViewObject*)data;

    int tmpCols = gtk_spin_button_get_value (button);

		Grid_ptr data1;
		data1.row = model->g_model->grid->gArray->rows; //model->g_model->grid->gArray->rows;
		data1.col = tmpCols;
	//	data.rules = model->g_model->grid->gArray->rules;
		Grid_mod( model->g_model->grid, RESIZE, &data1);
    //Grid_resize(model->g_model->grid , model->g_model->grid->rows, tmpCols);//grid_resize(model->g_model->grid, model->g_model->rows, model->g_model->cols, model->g_model->rows, tmpCols);
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
		//TODO: set game model update value here. Refresh value is always same.
		//g_source_remove(model->g_model->timerid);
	//	model->g_model->timerid = -1;
		//model->g_model->timerid = g_timeout_add(33, (GSourceFunc) view_timer_update, model->g_model);
		//model->g_model->timerid = g_timeout_add(model->g_model->interval, (GSourceFunc)view_timer_update, model);
	}
	GameModel_save(model->g_model);
}

G_MODULE_EXPORT
void on_drawingarea1_button_press_event( GtkWidget *widget, GdkEventButton *event, gpointer data )
{
	g_print("Draw pressed of range.\n");
	GtkAllocation widget_alloc;
	gtk_widget_get_allocation(GTK_WIDGET(widget), &widget_alloc);
	int maxx = widget_alloc.width,
		maxy = widget_alloc.height;

		int posx = GameArea_x_pos(data, event->x, maxx, maxy);// get_x_position( widget, data, event->x);
		int posy = GameArea_y_pos(data, event->y, maxx, maxy);
	//	g_print("button pressed on game : x:%f, y:%d.\n", event->x, event->y);
		if(posx >= 0 && posy >= 0) {
			ViewObject *model = (ViewObject*)data;
			Grid_switch( model->g_model->grid, posy, posx );
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

gboolean on_drawingarea_key_press_event( GtkWidget *widget, GdkEventKey *event, gpointer *data )
{
	ViewObject *object = (ViewObject*)data;
	//printf("Grid key event %d\n", event->keyval);
	switch (event->keyval) {
		case GDK_KEY_Right:
			object->g_model->startY += 1;
			gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
			break;
		case GDK_KEY_Left:
			if(object->g_model->startY -1 > 0) {
				object->g_model->startY -= 1;
				gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
			}
			break;
		case GDK_KEY_Up:
			if(object->g_model->startX -1 > 0) {
				object->g_model->startX -= 1;
				gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
			}
			break;
		case GDK_KEY_Down:
			object->g_model->startX += 1;
			gtk_widget_queue_draw(GTK_WIDGET(object->g_model->main_frame));
			break;
		default:
			g_print("Key press detected.");
			break;
	}
	return TRUE;
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
void on_themebox_changed( GtkComboBox *box, gpointer data )
{
	ViewObject *object = (ViewObject*)data;

	if(object) {
		// TODO: set selected value in combobox to selected in theme manager.
	//	theme_select(object->theme, box->);
	}
}

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
		if(model->grid->updated == 1) {
			//model->updated = 0;
			GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
			char str[20];
			sprintf(str, "%d", model->c_step);
			gtk_label_set_text(GTK_LABEL(step_count), str);

			GtkAllocation widget_alloc;
			/* Get current allocation for widget to know draw size. */
			gtk_widget_get_allocation(GTK_WIDGET(model->game_frame), &widget_alloc);
			int maxx = widget_alloc.width,
				maxy = widget_alloc.height;
			//model->game_frame
			gtk_widget_queue_draw_area (model->game_frame, 0, 0, maxx, maxy);
			//model->updated = 0;
		}
		//gtk_widget_queue_draw(GTK_WIDGET(model->game_frame));
	}
	return TRUE;
}
