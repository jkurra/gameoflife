#include "view.h"

void GameView_show( GameModel *model )
{
    if(model) {
        /*
         * Save main widgets that are modified using values in model, so we don't
         * have to look for them every time they are needed.
         */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        model->game_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "drawingarea1"));
        /* Search local UI-elements that are programmatically modified. */
        GtkWidget *overlay    = GTK_WIDGET(gtk_builder_get_object(model->builder, "overlay3"));
        GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
        GtkWidget *row_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetRows"));
        GtkWidget *col_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetCols"));
        GtkWidget *int_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetInterval"));
        GtkWidget *dead_switch = GTK_WIDGET(gtk_builder_get_object(model->builder, "DeadCellSwitch"));

        GtkWidget *color_bb = GTK_WIDGET(gtk_builder_get_object(model->builder, "BagckgroundColor"));
        GtkWidget *color_bc = GTK_WIDGET(gtk_builder_get_object(model->builder, "CellColor"));

        /* Get step value as character string from step counter from model. */
        char str[20];
        sprintf(str, "%d", model->c_step);
        /* Assign UI spinbutton values from model */
        gtk_label_set_text(GTK_LABEL(step_count), str);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(col_button), model->grid->cols);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(row_button), model->grid->rows);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(int_button), model->interval);
        gtk_switch_set_state(GTK_SWITCH(dead_switch), model->visible);
        /* Assign UI color chooser values from model */
        gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_bb), &model->bgrn_col);
        gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_bc), &model->cell_col);
        /* Show all widgets under main_frame */
        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void MenuView_show( MenuModel *model )
{
    if(model) {
        /*
         * Save main widgets that are modified using values in model, so we don't
         * have to look for them every time they are needed.
         */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        model->game_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "menuBackground"));
        /* Search UI-elements that are programmatically modified. */

        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void PrefView_show( PrefModel *model )
{
    if(model) {
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void view_show( Model *model )
{
    switch (model->type) {
        case GAME: /* Initialize game view */
            GameView_show((GameModel*)model);
            break;
        case MENU:
            MenuView_show((MenuModel*)model);
            break;
        case PREF:
            PrefView_show((PrefModel*)model);
            break;
        default:
            log_message("View show", "Unknown model type receive ");
            break;
    }
}

void MenuView_destroy( MenuModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /*log_message("PrefView close", "Unknown model type receive "); */}
}

void GameView_destroy( GameModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /*log_message("PrefView close", "Unknown model type receive "); */}
}

void PrefView_destroy( PrefModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /*log_message("PrefView close", "Unknown model type receive "); */}
}

void view_destroy( Model *model )
{
    switch (model->type) {
        case GAME: /* Initialize game view */
            GameView_destroy((GameModel*)model);
            break;
        case MENU:
            MenuView_destroy((MenuModel*)model);
            break;
        case PREF:
            PrefView_destroy((PrefModel*)model);
            break;
        default:
            //log_message("View close", "Unknown model type receive ");
            break;
    }
}

void MenuView_hide( MenuModel *model )
{
	if(model) {
        gtk_widget_hide(model->main_frame);
	} else { /*log_message("MenuView close", "Unknown model type receive ");*/ }
}

void GameView_hide( GameModel *model )
{
	if(model) {
        if(model->timerid != -1) {
            g_source_remove(model->timerid);
            model->timerid = -1;
        }
        gtk_widget_hide(model->main_frame);
	} else { /*log_message("GameView close", "Unknown model type receive ");*/ }
}

void PrefView_hide( PrefModel *model )
{
	if(model) {
        gtk_widget_hide(model->main_frame);
	} else { /*log_message("PrefView close", "Unknown model type receive "); */}
}

void view_hide( Model *model )
{
    switch (model->type) {
        case GAME: /* Initialize game view */
            GameView_hide((GameModel*)model);
            break;
        case MENU:
            MenuView_hide((MenuModel*)model);
            break;
        case PREF:
            PrefView_hide((PrefModel*)model);
            break;
        default:
            log_message("View close", "Unknown model type receive ");
            break;
    }
}
