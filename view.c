#include "view.h"

void view_init( view_model *model )
{
	if(model) {
		gtk_init(NULL, NULL);
		model->builder = gtk_builder_new();

	}
}

void view_free( view_model *model )
{
	if(model) {
		g_object_unref(G_OBJECT(model->builder));

	}
}

void view_menu_init( menu_model *model, GtkBuilder *builder)
{
	GError	*error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(builder, "glade-ui/gof_menu.glade", &error)) {
		g_warning("%s", error->message);
    	g_free(error);
	}

	model->main_frame = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	//gtk_builder_connect_signals(model->builder, model);
	GtkAllocation allocation;
	gtk_widget_get_allocation(model->main_frame, &allocation);

  	gtk_widget_show(model->main_frame);
  	int max_x = gtk_widget_get_allocated_width(model->main_frame),
		max_y = gtk_widget_get_allocated_height(model->main_frame);
	// ("x: %d : y: %d\n", max_x, max_y );
}

void view_game_init( game_model *model, GtkBuilder *builder )
{
	GError  *error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(builder, "glade-ui/gof_game.glade", &error)) {
		g_warning("%s", error->message);
	   g_free( error );
	}
	if(!model) {
		g_print("Null model");
	}
	model->timerid = g_timeout_add(model->tick_t, (GSourceFunc) view_timer_update, model);
	model->main_frame = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	model->game_area  = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea1"));
	//gtk_builder_connect_signals( model->builder, model);

	gtk_widget_show(model->main_frame);
}

void view_pref_init( pref_model *model, GtkBuilder *builder )
{
	GError *error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if( !gtk_builder_add_from_file(builder, "glade-ui/gof_pref.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
	}
	/* Set values for elements received from the model. */
	GtkWidget *sp = GTK_WIDGET ( gtk_builder_get_object(builder, "row_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp), model->max_x);
	GtkWidget *sp1 = GTK_WIDGET ( gtk_builder_get_object(builder, "col_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp1), model->max_y);
	GtkWidget*sp2 = GTK_WIDGET( gtk_builder_get_object(builder, "int_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp2), model->tick_t);

	GtkWidget *cb = GTK_WIDGET ( gtk_builder_get_object(builder, "bg_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb), &model->bgrn_col);
	GtkWidget *cb2 = GTK_WIDGET( gtk_builder_get_object(builder, "cell_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb2), &model->cell_col);

	GtkWidget *switchVis = GTK_WIDGET( gtk_builder_get_object(builder, "switch2"));
	gtk_switch_set_state (GTK_SWITCH(switchVis),model->visible);
	/* Tie signals to objects */
	model->main_frame = GTK_WIDGET( gtk_builder_get_object(builder, "main_frame" ));
	//gtk_builder_connect_signals(model->builder, model);

  gtk_widget_show( model->main_frame );
}

void view_menu_close( menu_model *model )
{
	if(model) {
		g_object_ref_sink(G_OBJECT(model->main_frame));
		gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		g_object_unref(G_OBJECT(model->main_frame));
	} else { printf("view [CLOSE] : ERROR! Received null pointer.\n"); }
}

void view_game_close( game_model *model )
{
	if(model) {
		g_object_ref_sink(G_OBJECT(model->main_frame));
		gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		g_object_unref(G_OBJECT(model->main_frame));
	} else { printf("view [CLOSE] : ERROR! Received null pointer.\n"); }
}

void view_pref_close( pref_model *model )
{
	if(model) {
		g_object_ref_sink(G_OBJECT(model->main_frame));
		gtk_widget_destroy(GTK_WIDGET(model->main_frame));
		g_object_unref(G_OBJECT(model->main_frame));
	} else { printf("view [CLOSE] : ERROR! Received null pointer.\n"); }
}

G_MODULE_EXPORT
void view_menu_draw( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{

}

gboolean view_timer_update( game_model *model )
{
	if(!model) {
		g_print("null model");
	}

	grid_next(model->max_x, model->max_y, model->grid, model->live_a, 2, model->live_d, 1);
	gtk_widget_queue_draw( model->main_frame );
	//g_object_unref(G_OBJECT( builder ));
	return TRUE;
}

G_MODULE_EXPORT
void view_game_draw( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
	view_model *model = (view_model*)data;

	//GtkAllocation allocation;
	//gtk_widget_get_allocation(GTK_DRAWING_AREA(gameArea), &allocation);

	int max_x = model->game->max_x,
		 max_y = model->game->max_y,
			cur_x = model->game->startAtCellX,
			cur_y = model->game->startAtCellY;

			int maxx = gtk_widget_get_allocated_width(area),
				maxy = gtk_widget_get_allocated_height(area);
   ///sg_print("x: %d : y: %d\n", max_x, max_y );
	cairo_rectangle(cr, 0,0, maxx, maxy);
	gdk_cairo_set_source_rgba(cr, &model->game->bgrn_col);
	cairo_fill(cr);
	//1gtk_widget_override_background_color(GTK_WIDGET(area), GTK_STATE_NORMAL, &model->game->bgrn_col);

	float x_start=5.0, y_start=5.0;
	for(cur_y=model->game->startAtCellY; cur_y<max_y; cur_y++) {
		for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
			int state = -1;
			if(x_start > maxx) {
				break;
			}
			if(y_start > maxy) {
				break;
			}
			//g_print("x: %d : y: %d\n", cur_x, cur_y );
			state = model->game->grid[cur_y][cur_x];
			if( state == 1 ) {
				cairo_rectangle(cr, x_start, y_start, model->game->cell_s/model->game->zoom, model->game->cell_s/model->game->zoom);
				gdk_cairo_set_source_rgba(cr, &model->game->cell_col);
				cairo_fill(cr);
			}
			else if( state != 1 && model->game->visible == 1)  {

				GdkRGBA *rgba;
				//gdk_rgba_parse (&rgba, "grey");
				rgba = gdk_rgba_copy(&model->game->bgrn_col);
				rgba->red   += 0.1;
				rgba->green += 0.1;
				rgba->blue  += 0.1;
				cairo_rectangle(cr, x_start, y_start, (model->game->cell_s/model->game->zoom), (model->game->cell_s/model->game->zoom));
				gdk_cairo_set_source_rgba(cr, rgba);
				cairo_fill(cr);
				gdk_rgba_free(rgba);
				//x_start -= 0.1;
				//y_start -= 0.1;
			}

			x_start += model->game->cell_s/model->game->zoom;
			x_start += model->game->cell_s/3.0; // space between cells
		}
		x_start = 5.0;
		y_start += model->game->cell_s/model->game->zoom;
		y_start += model->game->cell_s/3.0;
	}
}

G_MODULE_EXPORT
void view_pref_draw ( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{

}
