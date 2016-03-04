#include "controller.h"

void controller_model(view_model *model, int type)
{
	switch (model->type) { /* Determine which model is sending the signal. */
		case MENU: /* MAIN MENU */
			gtk_widget_destroy(GTK_WIDGET(model->menu->main_frame));
			break;
		case GAME: /* GAME */
			g_source_remove(model->game->timerid);
			
			gtk_widget_destroy(GTK_WIDGET(model->game->main_frame));
			break;
		case PREF: /* PREFERENCES */
			gtk_widget_destroy(GTK_WIDGET(model->pref->main_frame));
			break;
		default:
			break;
	}
	model->type = type;
	model_init_view(model);
}

G_MODULE_EXPORT
void one_menuButton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	controller_model((view_model*)data, MENU);
}

G_MODULE_EXPORT
void on_SettingsButton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	controller_model((view_model*)data, PREF);
}

G_MODULE_EXPORT
void on_startGamebutton_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	controller_model((view_model*)data, GAME);
	/*
	int rtn = model_game_data( model->game, model->pref_path) ;
	if(rtn == JSM_OK) {
		gtk_widget_destroy(GTK_WIDGET(model->menu->main_frame));
			//game.timerid = g_timeout_add(game.tick_t, (GSourceFunc) model_grid_update, &game);
		model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model->game);
		model->type = 1;	/* Set new model to game */
	//	model_init_view( model );
	//}
	//else {
		//g_print("UNABLE TO FIND SETTINGS");
	//}
}

G_MODULE_EXPORT
void on_pause_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;

	g_source_remove(model->game->timerid);
	g_print("pause pressed %d\n", model->game->timerid);
}

G_MODULE_EXPORT
void on_resume_clicked( GtkButton *button, gpointer data )
{
	view_model *model = (view_model*)data;
	model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model->game);
	g_print("resume pressed %d\n", model->game->timerid);
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
	game_model *game = (game_model*)data;
	if(game->startAtCellY >= 5)
		game->startAtCellY-=5;
		model_draw_game(game);
}

G_MODULE_EXPORT
void on_down_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	game->startAtCellY+=5;
	model_draw_game(game);
}

G_MODULE_EXPORT
void on_left_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	if(game->startAtCellX >= 5)
		game->startAtCellX -= 5;
		model_draw_game(game);
}

G_MODULE_EXPORT
void on_right_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	game->startAtCellX += 5;
	model_draw_game(game);
}

G_MODULE_EXPORT
void on_zoom_in_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	if(game->zoom > 1)
		game->zoom = game->zoom-1;
		model_draw_game(game);
}

G_MODULE_EXPORT
void on_zoom_out_clicked( GtkButton *button, gpointer data )
{
	game_model *game = (game_model*)data;
	game->zoom = game->zoom+1;
	model_draw_game(game);
}
