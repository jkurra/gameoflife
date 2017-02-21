#include "view.h"

void GameView_init( GameModel *model, ViewObject *object )
{
    if(model) {
        /* Search most used frames in UI */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "window1"));
        model->game_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "drawingarea1"));
        /* Search UI-elements that are programmatically modified. */
        GtkWidget *overlay    = GTK_WIDGET(gtk_builder_get_object(model->builder, "overlay3"));
        GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
        GtkWidget *row_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "gridRowsspinButton"));
        GtkWidget *col_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "gridColsspinButton"));
        GtkWidget *int_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "interval_spinbutton"));
        /* Assign UI spinbutton values from model */
        char str[20];
        sprintf(str, "%d", model->c_step);
        gtk_label_set_text(GTK_LABEL(step_count), str);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(col_button), model->cols);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(row_button), model->rows);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(int_button), model->interval);
        /* Set overlay to pass buttons in navigation to front so user can press them. */
        gtk_overlay_set_overlay_pass_through(GTK_OVERLAY(overlay), GTK_WIDGET(model->game_frame), FALSE);
        /*
            Auto-connect signals in glade files to defined signals.
            Signals can be located in src/view/signal/signal.h file.
        */
        gtk_builder_connect_signals(model->builder, object);
        //TODO: cleanup old and unused signals, some of them may be needed.
        // g_signal_connect (G_OBJECT(model->game_frame),  "button-press-event", G_CALLBACK (on_drawingarea_button_press_event ), NULL);
        // g_signal_connect (G_OBJECT(model->game_frame),  "drag-begin", G_CALLBACK (on_drawingarea_button_press_event ), NULL);
        g_signal_connect( G_OBJECT(model->game_frame ), "draw", G_CALLBACK(draw_GameArea), model );
        /* Show all widgets under main_frame */
        gtk_widget_show_all(model->main_frame);
    } else { log_message("GameView init", "Unknown model type receive "); }
}

void MenuView_init( MenuModel *model, ViewObject *object)
{
	if(model) {
		/* Search most used frames in UI */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "window1"));
        /* Search UI-elements that are programmatically modified. */
        if(!model->builder) {
            g_print("model was null!");
        }
        gtk_builder_connect_signals(model->builder, object);
        // g_signal_connect( G_OBJECT(model->game_frame ), "draw", G_CALLBACK(draw_GameArea), model );
        /* Show all widgets under main_frame */
        gtk_widget_show_all(model->main_frame);
	} else { log_message("GameView init", "Unknown model type receive "); }
}

void PrefView_init( PrefModel *model, ViewObject *object )
{
	if(model) {
		/* Search most used frames in UI */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "window1"));
        /* Search UI-elements that are programmatically modified. */

        gtk_builder_connect_signals(model->builder, object);
        // g_signal_connect( G_OBJECT(model->game_frame ), "draw", G_CALLBACK(draw_GameArea), model );
        /* Show all widgets under main_frame */
        gtk_widget_show_all(model->main_frame);
	} else { log_message("GameView init", "Unknown model type receive "); }
}

void GameView_draw( GameModel *model, cairo_t *cr, gpointer data  )
{

}

void MenuView_draw( MenuModel *model, cairo_t *cr, gpointer data )
{

}

void PrefView_draw( PrefModel *model, cairo_t *cr, gpointer data )
{

}

void GameView_close( GameModel *model )
{
	if(model) {
		GtkWidget *overlay    = GTK_WIDGET(gtk_builder_get_object(model->builder, "overlay3"));
        GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
		GtkWidget *row_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "gridRowsspinButton"));
		GtkWidget *col_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "gridColsspinButton"));
		GtkWidget *int_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "interval_spinbutton"));

        gtk_widget_destroy(step_count);
		gtk_widget_destroy(overlay);
		gtk_widget_destroy(row_button);
		gtk_widget_destroy(col_button);
		gtk_widget_destroy(int_button);

        g_object_unref (G_OBJECT(step_count));
		g_object_unref (G_OBJECT(overlay));
		g_object_unref (G_OBJECT(row_button));
		g_object_unref (G_OBJECT(col_button));
		g_object_unref (G_OBJECT(int_button));

		gtk_widget_destroy(GTK_WIDGET(model->game_frame));
		g_object_unref (G_OBJECT(model->game_frame));

		gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		g_object_unref (G_OBJECT(model->main_frame));

	} else { /*log_message("GameView close", "Unknown model type receive ");*/ }
}

void MenuView_close( MenuModel *model )
{
	if(model) {
        gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		//g_object_unref (G_OBJECT(model->main_frame));
	} else { /*log_message("MenuView close", "Unknown model type receive ");*/ }
}

void PrefView_close( PrefModel *model )
{
	if(model) {
        gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		g_object_unref (G_OBJECT(model->main_frame));
	} else { /*log_message("PrefView close", "Unknown model type receive "); */}
}

void view_init( Model *model, ViewObject *object)
{
    switch (model->type) {
        case GAME:
            GameView_init((GameModel*)model, object);
            break;
        case MENU:
            MenuView_init((MenuModel*)model, object);
            break;
        case PREF:
            PrefView_init((PrefModel*)model, object);
            break;
        default:
            /*log_message("View init", "Unknown model type receive ");*/
            break;
    }
}

void view_draw( Model *model )
{
    switch (model->type) {
        case GAME: /* Initialize game view */
            //GameView_draw((GameModel*)model);
            break;
        case MENU:
            //MenuView_draw((MenuModel*)model);
            break;
        case PREF:
            //PrefView_draw((PrefModel*)model);
            break;
            log_message("View draw", "Unknown model type receive ");
        default:
            break;
    }
}

void view_close( Model *model )
{
    switch (model->type) {
        case GAME: /* Initialize game view */
            GameView_close((GameModel*)model);
            break;
        case MENU:
            MenuView_close((MenuModel*)model);
            break;
        case PREF:
            PrefView_close((PrefModel*)model);
            break;
        default:
            log_message("View close", "Unknown model type receive ");
            break;
    }
}
