#include "view.h"
#include "model.h"
void view_init( view_model *model, int type )
{

	/* Initialize model variables and GTK parts initialization*/
	gtk_init(NULL, NULL);
	model->builder = gtk_builder_new();
	model->type = type; /* Change current view type. */
	/*
		Read css style from file. TODO: add style variable that may be changed
		by the user.
	*/
	GdkDisplay *display = gdk_display_get_default ();
	GdkScreen  *screen = gdk_display_get_default_screen (display);
	model->provider = gtk_css_provider_new ();

	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (model->provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gsize bytes_written, bytes_read;
	if(model->game->commons->themes->sel_path) {
		const gchar* home = model->game->commons->themes->sel_path;

		GError *error1 = 0;
		//g_print("open file :%s", home);
		gtk_css_provider_load_from_path (model->provider,
										 g_filename_to_utf8(home, strlen(home),
										 &bytes_read, &bytes_written, &error1),
										 NULL);

		if(model) {
			switch(model->type) {
				case MENU:
					//printf("MODEL [INIT] : menu\n");
					view_menu_init(model->menu, model->builder);
					gtk_builder_connect_signals(model->builder, model);
					break;
				case GAME:
					//printf("MODEL [INIT] : game\n");
					view_game_init(model->game, model->builder);
					gtk_builder_connect_signals(model->builder, model);
					break;
				case PREF:
					//printf("MODEL [INIT] : pref\n");
					view_pref_init(model->pref, model->builder);
					gtk_builder_connect_signals(model->builder, model);
					break;
				default:
					break;
			}
			gtk_main();
		} else { printf("MODEL [INIT] : ERROR! Received null pointer to model\n"); }
	}else {printf("Unable to open view, no themes available.\n" );}
}

void view_draw( view_model *model )
{
	if(model) {
		switch(model->type) {
			case MENU:
				gtk_widget_queue_draw(model->menu->main_frame);
				break;
			case GAME:
				gtk_widget_queue_draw(model->game->main_frame);
				break;
			case PREF:
				gtk_widget_queue_draw(model->pref->main_frame);
				break;
			default:
				break;
		}
	} else { printf("MODEL [DRAW] : ERROR! Received null pointer to model\n"); }
}

void view_close( view_model *model )
{
	if(model) {
		gtk_main_quit();
		switch(model->type) {
			case MENU:
				//printf("MODEL [CLOSE] : menu\n");
				view_menu_close(model->menu);
				break;
			case GAME:
				//printf("MODEL [CLOSE] : game\n");
				view_game_close(model->game);
				break;
			case PREF:
				//printf("MODEL [CLOSE] : pref\n");
				view_pref_close(model->pref);
				break;
			default:
				break;
		}
	} else { printf("MODEL [CLOSE] : ERROR! Received null pointer to model\n"); }
}

void view_menu_init( menu_model *model, GtkBuilder *builder)
{
	GError	*error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(builder, "gui/gof_menu.glade", &error)) {
		g_warning("%s", error->message);
    	g_free(error);
	}

	model->main_frame = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

  	gtk_widget_show(model->main_frame);
}

void view_game_init( game_model *model, GtkBuilder *builder )
{
	GError  *error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if(!gtk_builder_add_from_file(builder, "gui/gof_game.glade", &error)) {
		g_warning("%s", error->message);
		g_free( error );
	}
	if(!model) {
		g_print("Null model");
	}
	//model->commons->timerid = g_timeout_add(model->commons->interval, (GSourceFunc) view_timer_update, model);
	model->main_frame = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	model->game_area  = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea1"));

	GtkWidget *sp1 = GTK_WIDGET ( gtk_builder_get_object(builder, "gridRowsspinButton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp1), model->commons->rows);
	GtkWidget *sp2 = GTK_WIDGET ( gtk_builder_get_object(builder, "gridColsspinButton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp2), model->commons->cols);

	gtk_widget_show(model->main_frame);
}

void view_pref_init( pref_model *model, GtkBuilder *builder )
{
	GError *error = NULL;
	if(!builder) { g_print("builder unitialized"); }
	if( !gtk_builder_add_from_file(builder, "gui/gof_pref.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
	}
	/* Set values for elements received from the model. */
	GtkWidget *sp = GTK_WIDGET ( gtk_builder_get_object(builder, "row_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp), model->commons->rows);
	GtkWidget *sp1 = GTK_WIDGET ( gtk_builder_get_object(builder, "col_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp1), model->commons->cols);
	GtkWidget*sp2 = GTK_WIDGET( gtk_builder_get_object(builder, "int_spinbutton") );
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp2), model->commons->interval);
	GtkWidget *cb = GTK_WIDGET ( gtk_builder_get_object(builder, "bg_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb), &model->commons->bgrn_col);
	GtkWidget *cb2 = GTK_WIDGET( gtk_builder_get_object(builder, "cell_colorbutton"));
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (cb2), &model->commons->cell_col);
	GtkWidget *switchVis = GTK_WIDGET( gtk_builder_get_object(builder, "switch2"));
	gtk_switch_set_state (GTK_SWITCH(switchVis),model->commons->visible);
	model->main_frame = GTK_WIDGET( gtk_builder_get_object(builder, "main_frame" ));

	//GtkListStore *liststore;
    GtkWidget *combo;
    //GtkCellRenderer *column;

//    liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

	char **dir_list = model->commons->themes->dir_list;
    int    dir_size = model->commons->themes->dir_size;

	combo = GTK_WIDGET( gtk_builder_get_object(builder, "themebox" ));
	int active = -1;
	for(int i=0; i<dir_size; i++) {
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),  dir_list[i]);
		if(strcmp (dir_list[i], model->commons->themes->sel_name) == 0) {
			active = i;
		}
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), active);

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

gboolean view_timer_update( game_model *model )
{
	if(model) {
		grid_next(model->commons->rows, model->commons->cols, model->grid, model->commons->live_a, 2, model->commons->live_d, 1);
		model->c_step++;
		gtk_widget_queue_draw( GTK_WIDGET(model->main_frame) );
	}
	return TRUE;
}

void view_draw_rectangle( cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height )
{
	if(cairo && color) {
		cairo_rectangle(cairo, start_x, start_y, width, height);
		gdk_cairo_set_source_rgba(cairo, color);
		cairo_fill(cairo);
	} else { }
}

G_MODULE_EXPORT
void view_game_draw( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
	view_model *model = (view_model*)data;

	if(model) {
		int max_x = model->game->commons->rows,
			max_y = model->game->commons->cols,
			cur_x = model->game->startAtCellX,
			cur_y = model->game->startAtCellY,
			interval = model->game->commons->interval,
			step = model->game->c_step;

		GtkWidget *interval_sp = GTK_WIDGET ( gtk_builder_get_object(model->builder, "interval_spinbutton") );
		GtkWidget *step_sp = GTK_WIDGET ( gtk_builder_get_object(model->builder, "stepspinbutton") );
		//gtk_spin_button_set_value (GTK_SPIN_BUTTON (sp2), model->commons->cols);

	//	GtkWidget *interval_label = GTK_WIDGET ( gtk_builder_get_object(model->builder, "interval_label") );
	//	GtkWidget *step_label = GTK_WIDGET ( gtk_builder_get_object(model->builder, "step_label") );
/*
		char value[10];
		char step_value[10];
		sprintf(value, "%d", interval);
		sprintf(step_value, "%d", step);
*/
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (interval_sp), interval);
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (step_sp), step);

		//gtk_label_set_text (GTK_LABEL(interval_label), value);
		//gtk_label_set_text (GTK_LABEL(step_label), step_value);
		/* Get currently drawn size of the widget */
		GtkAllocation widget_alloc;
		gtk_widget_get_allocation(GTK_WIDGET(area), &widget_alloc);
		int maxx = widget_alloc.width,
			maxy = widget_alloc.height;
		/* Draw background */
		view_draw_rectangle(cr, &model->game->commons->bgrn_col, 0, 0, maxx, maxy);
		float x_start = 5.0, y_start = 5.0;
		for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
			for(cur_y=model->game->startAtCellY; cur_y<max_y; cur_y++) {

				int state = -1;
				if(x_start > maxx) {
					break;
				}
				if(y_start > maxy) {
					break;
				}
				if(cur_y >= 0 && cur_x >= 0) {
					state = model->game->grid[cur_x][cur_y];
					if(state == 1) {
						view_draw_rectangle(cr, &model->game->commons->cell_col, x_start, y_start, model->game->commons->cell_s/model->game->commons->zoom, model->game->commons->cell_s/model->game->commons->zoom);
					}
					else if(state != 1 && model->game->commons->visible == 1)  {
						/*if(y_start < 0 || x_start < 0) {
							g_print("y:%d : x%d", y_start, x_start);
						}
						else {*/
							int size = (model->game->commons->cell_s/model->game->commons->zoom);
							GdkRGBA *rgba;
							rgba = gdk_rgba_copy(&model->game->commons->bgrn_col);
							rgba->red   += 0.1;
							rgba->green += 0.1;
							rgba->blue  += 0.1;
							view_draw_rectangle(cr, rgba, x_start, y_start, size, size);
							gdk_rgba_free(rgba);
						//}
					}
				}// else { g_print("y:%d : x%d\n", cur_y, cur_x); }

				x_start += model->game->commons->cell_s/model->game->commons->zoom;
				x_start += model->game->commons->cell_s/3.0; // space between cells
			}
			x_start = 5.0;
			y_start += model->game->commons->cell_s/model->game->commons->zoom;
			y_start += model->game->commons->cell_s/3.0;
		}
	} else { }
}
