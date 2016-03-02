#include "view.h"

void view_menu_init( view_model *model )
{
	GtkBuilder *builder;
  GError     *error = NULL;

	gtk_init( NULL, NULL );
  builder = gtk_builder_new();

  if( ! gtk_builder_add_from_file( builder, "glade-ui/gof_menu.glade", &error ) )
  {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
	}

	model->menu->main_frame = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
	gtk_builder_connect_signals( builder, model );
	g_object_unref( G_OBJECT( builder ) );

  gtk_widget_show( model->menu->main_frame );
  gtk_main();
}

void view_game_init( view_model *model )
{
	GtkBuilder *builder;
  GError     *error = NULL;

	gtk_init( NULL, NULL );
  builder = gtk_builder_new();

  if( !gtk_builder_add_from_file( builder, "glade-ui/gof_game.glade", &error ) )
  {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
	}

	model->game->main_frame = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
	gtk_builder_connect_signals( builder, model );
	g_object_unref( G_OBJECT( builder ) );

  gtk_widget_show( model->game->main_frame );
  gtk_main();
}

void view_pref_init( view_model *model )
{
	GtkBuilder *builder;
  GError     *error = NULL;

	gtk_init( NULL, NULL );
  builder = gtk_builder_new();

  if( !gtk_builder_add_from_file( builder, "glade-ui/gof_pref.glade", &error ) )
  {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
	}
	/* Set values for elements received from the model. */
	GtkSpinButton *sp = GTK_WIDGET( gtk_builder_get_object(builder, "spinbutton11") );
	gtk_spin_button_set_value (sp, model->game->grid_x);
	GtkSpinButton *sp1 = GTK_WIDGET( gtk_builder_get_object(builder, "spinbutton12") );
	gtk_spin_button_set_value (sp1, model->game->grid_y);
	GtkSpinButton *sp2 = GTK_WIDGET( gtk_builder_get_object(builder, "spinbutton13") );
	gtk_spin_button_set_value (sp2, model->game->tick_t);

	GtkColorButton *cb = GTK_WIDGET( gtk_builder_get_object(builder, "colorbutton1") );
	gtk_color_button_set_color (cb, &model->game->backGround);
	GtkColorButton *cb2 = GTK_WIDGET( gtk_builder_get_object(builder, "colorbutton2") );
	gtk_color_button_set_color (cb2, &model->game->cellColor);
	/* Tie signals to objects */
	model->pref->main_frame = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
	gtk_builder_connect_signals( builder, model );
	g_object_unref( G_OBJECT( builder ) );

  gtk_widget_show( model->pref->main_frame );
  gtk_main();
}

void view_popup_init( game_model *model )
{
	GtkBuilder *builder;
  GError     *error = NULL;

	gtk_init( NULL, NULL );

  builder = gtk_builder_new();

  if( !gtk_builder_add_from_file( builder, "glade-ui/gof_value_popup.glade", &error ) )
  {
		g_warning( "%s", error->message );
    g_free( error );
    return( 1 );
	}

	model->main_frame = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
	gtk_builder_connect_signals( builder, model );
	g_object_unref( G_OBJECT( builder ) );

  gtk_widget_show( model->main_frame );
  gtk_main();
}

G_MODULE_EXPORT
void view_menu_draw ( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{

}

G_MODULE_EXPORT
void view_game_draw ( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
	view_model *model = (view_model*)data;

	//g_print("startx: %d\n", model->game->grid_x);
	int max_x = model->game->grid_x,
			max_y = model->game->grid_y,
			cur_x = model->game->startAtCellX,
			cur_y = model->game->startAtCellY;

		//cairo_set_source_rgb (cr, 0, 0, 0);
	//GdkRGBA bgColor;	// background color
	//GdkRGBA frColor;	// color of front

//	G//dkColor bgColor;
	//bgColor = gdk_color_copy(model->game->backGround);
/*	gdk_color_parse ( "black", &bgColor );
	gtk_widget_modify_bg(area, GTK_STATE_NORMAL, &bgColor);
*/
	//gdk_color_parse ( "black", &model->game->backGround );
	gtk_widget_modify_bg(area, GTK_STATE_NORMAL, &model->game->backGround);
	//gtk_widget_override_background_color(area, GTK_STATE_NORMAL, &model->game->backGround);
	int x_start=5, y_start=5;
	for(cur_y=model->game->startAtCellY; cur_y<max_y; cur_y++) {
		for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
			int state = -1;
			state = model->game->grid[cur_y][cur_x];
			//g_print("%d", state);
			if( state == 1 ) {
				cairo_rectangle(cr, x_start, y_start, model->game->cell_s/model->game->zoom, model->game->cell_s/model->game->zoom);
			}
			x_start += model->game->cell_s/model->game->zoom;
			x_start += model->game->cell_s/3; // space between cells
		}
		x_start = 5;
		y_start += model->game->cell_s/model->game->zoom;
		y_start += model->game->cell_s/3;
	}

	//GdkRGBA color;
	//gdk_cairo_set_source_rgba(cr, &model->game->cellColor);
	//gdk_rgba_parse (&color, "black");
	gdk_cairo_set_source_rgba(cr, &model->game->cellColor);

	cairo_fill(cr);
}

G_MODULE_EXPORT
void view_pref_draw ( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{

}
