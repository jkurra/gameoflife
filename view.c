#include "view.h"

void view_init( view_model *model )
{
	if(model)
		gtk_init(NULL, NULL);
		model->builder = gtk_builder_new();
}

void view_free( view_model *model )
{
	if(model->builder)
		g_object_unref(G_OBJECT(model->builder));
}

void view_menu_init( view_model *model )
{
	GError	*error = NULL;
	if(!model->builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(model->builder, "glade-ui/gof_menu.glade", &error)) {
		g_warning("%s", error->message);
    g_free(error);
	}

	model->menu->main_frame = GTK_WIDGET(gtk_builder_get_object(model->builder, "window1"));
	gtk_builder_connect_signals(model->builder, model);

  gtk_widget_show(model->menu->main_frame);
}

void view_game_init( view_model *model )
{
	GError  *error = NULL;
	if(!model->builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(model->builder, "glade-ui/gof_game.glade", &error)) {
		g_warning("%s", error->message);
    g_free( error );
	}

	model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) view_timer_update, model);
	model->game->main_frame = GTK_WIDGET( gtk_builder_get_object( model->builder, "window1" ) );
	gtk_builder_connect_signals( model->builder, model);

	gtk_widget_show(model->game->main_frame);
}

void view_pref_init( view_model *model )
{
	GError *error = NULL;
	if(!model->builder) { g_print("builder unitialized"); }
	if( !gtk_builder_add_from_file(model->builder, "glade-ui/gof_pref.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
	}
	/* Set values for elements received from the model. */
	GtkWidget *sp = GTK_WIDGET ( gtk_builder_get_object(model->builder, "row_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp), model->game->max_x);
	GtkWidget *sp1 = GTK_WIDGET ( gtk_builder_get_object(model->builder, "col_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp1), model->game->max_y);
	GtkWidget*sp2 = GTK_WIDGET( gtk_builder_get_object(model->builder, "int_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp2), model->game->tick_t);

	GtkWidget *cb = GTK_WIDGET ( gtk_builder_get_object(model->builder, "bg_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb), &model->game->bgrn_col);
	GtkWidget *cb2 = GTK_WIDGET( gtk_builder_get_object(model->builder, "cell_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb2), &model->game->cell_col);

	GtkWidget *switchVis = GTK_WIDGET( gtk_builder_get_object(model->builder, "switch2"));
	gtk_switch_set_state (GTK_SWITCH(switchVis),model->game->visible);
	/* Tie signals to objects */
	model->pref->main_frame = GTK_WIDGET( gtk_builder_get_object(model->builder, "main_frame" ));
	gtk_builder_connect_signals(model->builder, model);

  gtk_widget_show( model->pref->main_frame );
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

gboolean view_timer_update( view_model *model )
{
	/*GtkBuilder *builder = gtk_builder_new();
	GError     *error = NULL;
	if( !gtk_builder_add_from_file(builder, "glade-ui/gof_game.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
	}*/

	grid_next(model->game->max_x, model->game->max_y, model->game->grid, model->game->live_a,2, model->game->live_d, 1);
	//model_draw_view(model);
	//gtk_widget_queue_draw( model->game->main_frame );
	//GtkAllocation allocation;
	//allocation.x;
	//GtkWidget *area = GTK_WIDGET( gtk_builder_get_object(builder, "drawingarea1") );
	//gtk_widget_get_allocation (area, &allocation);
	//area->window;
	//gtk_widget_queue_draw_area(area, allocation.x, allocation.y, allocation.width, allocation.height);
	gtk_widget_queue_draw( model->game->main_frame );
	//g_object_unref(G_OBJECT( builder ));
	return TRUE;
}

G_MODULE_EXPORT
void view_game_draw( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
	view_model *model = (view_model*)data;

	int max_x = model->game->max_x,
			max_y = model->game->max_y,
			cur_x = model->game->startAtCellX,
			cur_y = model->game->startAtCellY;

	gtk_widget_override_background_color(GTK_WIDGET(area), GTK_STATE_NORMAL, &model->game->bgrn_col);
	float x_start=5.0, y_start=5.0;
	for(cur_y=model->game->startAtCellY; cur_y<max_y; cur_y++) {
		for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
			int state = -1;
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
