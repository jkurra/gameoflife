#include "gamearea.h"
#include "../view.h"

int GameArea_x_pos( gpointer data, float x, float width, float height )
{
    int pos = -1;
    view_model *model = (view_model*)data;

    GtkAllocation widget_alloc;
    int maxx = width,
        maxy = height;

    int max_x = model->game->commons->rows,
        max_y = model->game->commons->cols,
        cur_x =0,
        interval = model->game->commons->interval,
        step = model->game->c_step;

    float x_start = 5.0, y_start = 5.0;
    int x_cell = 0;
    //g_print("g:%d", max_x);
    float x_max = 0;
    float x_min = 0;
    x_cell += model->game->startAtCellY;
    for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
        x_max = x_start+(model->game->commons->cell_s/model->game->commons->zoom);
        x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            //g_print("pos x:%f,\n",y);
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += model->game->commons->cell_s/model->game->commons->zoom;
        x_start += model->game->commons->cell_s/3.0; // space between cells
        //g_print("button pressed on game1 : x_min:%f, x_max:%f\n", x_min, x_max);
    }
    //g_print("button pressed on game1 : x:%d.\n", pos);
    return pos;
}

int GameArea_y_pos( gpointer data, float y, float width, float height )
{
    int pos = -1;
    view_model *model = (view_model*)data;

    GtkAllocation widget_alloc;
    //gtk_widget_get_allocation(GTK_WIDGET(model->game->area), &widget_alloc);
    int maxx = width,
        maxy = height;

    int max_x = model->game->commons->rows,
        max_y = model->game->commons->cols,
        cur_x =0,
        cur_y = model->game->startAtCellY,
        interval = model->game->commons->interval,
        step = model->game->c_step;


    float x_start = 5.0, y_start = 5.0;
    int x_cell = 0;
    //g_print("g:%d", max_x);
    float x_max = 0;
    float x_min = 0;
        x_cell += model->game->startAtCellX;
    for(cur_x=model->game->startAtCellY; cur_x<max_x; cur_x++) {
        x_max = x_start+(model->game->commons->cell_s/model->game->commons->zoom);
        x_min = x_start;
        if(y>x_min && y<x_max) {
            pos = x_cell;
            //g_print("pos x:%f,\n",y);
            break;
        }
        x_cell++;
        x_start += model->game->commons->cell_s/model->game->commons->zoom;
        x_start += model->game->commons->cell_s/3.0; // space between cells
        //g_print("button pressed on game1 : x_min:%f, x_max:%f\n", x_min, x_max);
    }
    return pos;
}

void GameArea_draw_rectangle( cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height )
{
	if(cairo && color) {
		cairo_rectangle(cairo, start_x, start_y, width, height);
		gdk_cairo_set_source_rgba(cairo, color);
		cairo_fill(cairo);
	} else { }
}
