#include "view.h"

/** @brief
 *
 *  @param
 */
void GameView_show( GameModel *model );

/** @brief
 *
 *  @param
 */
void MenuView_show( MenuModel *model );

/** @brief
 *
 *  @param
 */
void PrefView_show( PrefModel *model );

/** @brief
 *
 *  @param
 */
void GameView_destroy( GameModel *model );

/** @brief
 *
 *  @param
 */
void MenuView_destroy( MenuModel *model );

/** @brief
 *
 *  @param
 */
void PrefView_destroy( PrefModel *model );

/** @brief
 *
 *  @param
 */
void MenuView_hide( MenuModel *model );

/** @brief
 *
 *  @param
 */
void GameView_hide( GameModel *model );

/** @brief
 *
 *  @param
 */
void PrefView_hide( PrefModel *model );

void view_show( Model *model )
{
    printf("grid has rows : %d \n", model->type);
    switch (model->type) {
        case GAME: /* Initialize game view */
            GameView_show((GameModel*)model);
            break;
        case MENU:printf("grid has rows : \n");
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

void GameView_show( GameModel *model )
{
    if(model) {
        /*
         * Save main widgets that are modified using values in model, so we don't
         * have to look for them every time they are needed.
         */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        model->game_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "drawingarea1"));
        /*
         * Add data from model to widgets in glade files so that they are
         * passed to UI when user first opens window.
         */
        int error = signal_connect(model->builder, model);
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
        /*
         * Add data from model to widgets in glade files so that they are
         * passed to UI when user first opens window.
         */
         printf("Moel aha rows : %d\n", model->grid->gArray->rows);
        int error = signal_connect(model->builder, model);
        /* Show all widgets under main_frame */
        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void PrefView_show( PrefModel *model )
{
    if(model) {
        /*
         * Save main widgets that are modified using values in model, so we don't
         * have to look for them every time they are needed.
         */
        model->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "MainWindow"));
        /*
         * Add data from model to widgets in glade files so that they are
         * passed to UI when user first opens window.
         */
        int error = signal_connect(model->builder, model);
        /* Show all widgets under main_frame */
        gtk_widget_show_all(GTK_WIDGET(model->main_frame));
    }
}

void MenuView_destroy( MenuModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /* log_message("PrefView close", "Unknown model type receive "); */}
}

void GameView_destroy( GameModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /* log_message("PrefView close", "Unknown model type receive "); */}
}

void PrefView_destroy( PrefModel *model )
{
	if(model) {
        if(model->main_frame)
            gtk_widget_destroy(model->main_frame);
	} else { /* log_message("PrefView close", "Unknown model type receive "); */}
}

void MenuView_hide( MenuModel *model )
{
	if(model) {
        gtk_widget_hide(model->main_frame);
	} else { /* log_message("MenuView close", "Unknown model type receive "); */}
}

void GameView_hide( GameModel *model )
{
	if(model) {
        if(model->timerid != -1) {
            g_source_remove(model->timerid);
            model->timerid = -1;
        }
        gtk_widget_hide(model->main_frame);
	} else { /* log_message("GameView close", "Unknown model type receive "); */}
}

void PrefView_hide( PrefModel *model )
{
	if(model) {
        gtk_widget_hide(model->main_frame);
	} else { /* log_message("PrefView close", "Unknown model type receive "); */}
}
