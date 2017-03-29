#include "view.h"
#include <GL/gl.h>

static gboolean
game_area_render (GtkGLArea *area, GdkGLContext *context)
{

  return TRUE;
}

void GameView_show( GameModel *model )
{
    if(model) {
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        model->game_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "drawingarea1"));
        /* Search UI-elements that are programmatically modified. */
        GtkWidget *overlay    = GTK_WIDGET(gtk_builder_get_object(model->builder, "overlay3"));
        GtkWidget *step_count = GTK_WIDGET(gtk_builder_get_object(model->builder, "step_counter"));
        GtkWidget *row_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetRows"));
        GtkWidget *col_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetCols"));
        GtkWidget *int_button = GTK_WIDGET(gtk_builder_get_object(model->builder, "SetInterval"));
        /* Assign UI spinbutton values from model */
        char str[20];
        sprintf(str, "%d", model->c_step);
        gtk_label_set_text(GTK_LABEL(step_count), str);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(col_button), model->grid->cols);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(row_button), model->grid->rows);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(int_button), model->interval);
       //gtk_gl_area_new (void);
        //model->game_frame = gtk_gl_area_new();
        //GtkGLArea *area  = gtk_gl_area_new();
        //int argc = 1;
        //  char *argv[1] = {(char*)"Something"};
         //glutInit(&argc, argv);
         //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    //    g_signal_connect (area, "realize", G_CALLBACK (on_realize), model);
    //    g_signal_connect (area, "render", G_CALLBACK (game_area_render), model);
        //g_signal_connect (model->game_frame, "render", G_CALLBACK (render), NULL);
        /* Set overlay to pass buttons in navigation to front so user can press them. */

        //gtk_overlay_add_overlay (GTK_OVERLAY(overlay),model->game_frame  );
       //gtk_overlay_reorder_overlay (overlay, model->game_frame , 0);
        //gtk_overlay_add_overlay (GTK_OVERLAY(overlay),model->game_frame  );
       //gtk_overlay_reorder_overlay (overlay, model->game_frame , 0);
    // gtk_overlay_set_overlay_pass_through(GTK_OVERLAY(overlay), GTK_WIDGET(model->game_frame), FALSE);
        //gtk_overlay_add_overlay (GTK_OVERLAY(overlay),model->game_frame  );
        //gtk_overlay_reorder_overlay (overlay, GTK_WIDGET(model->game_frame), 0);
        ///gtk_overlay_set_overlay_pass_through(GTK_OVERLAY(overlay), GTK_WIDGET(model->game_frame), TRUE);
        /* Show all widgets under main_frame */
        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void MenuView_show( MenuModel *model )
{
    if(model) {
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
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
