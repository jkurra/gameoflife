#include "graphics.h"

#include "../view.h"

void draw_grid( GtkDrawingArea *area, cairo_t *cr, gpointer data );

void graphics_draw( int type, GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
    switch (type) {
        case GRID:
            draw_grid( area, cr, data );
            break;
    }
}

void draw_rectangle( cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height )
{
	if(cairo && color) {
		cairo_rectangle(cairo, start_x, start_y, width, height);
		gdk_cairo_set_source_rgba(cairo, color);
		cairo_fill(cairo);
	} else { }
}

void color_lighter( GdkRGBA *rgba, float level )
{
    rgba->red   += level;
    rgba->green += level;
    rgba->blue  += level;
}

void draw_grid( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{
    game_model *model = (game_model*)data;

    int max_x = model->commons->rows,
        max_y = model->commons->cols,
        cur_x = model->startAtCellX,
        cur_y = model->startAtCellY;
    /* Get size of each cell to be drawn on the screen */
    float size = (model->commons->cell_s/model->commons->zoom);
    float x_start = 2.0, y_start = 2.0;

    GtkAllocation widget_alloc;
    gtk_widget_get_allocation(GTK_WIDGET(area), &widget_alloc);
    int maxx = widget_alloc.width,
        maxy = widget_alloc.height;

    draw_rectangle(cr, &model->commons->bgrn_col, 0, 0, maxx, maxy);

    for(cur_x = model->startAtCellX; cur_x<max_x; cur_x++) {
        if(x_start > maxx) { break; }
        for(cur_y = model->startAtCellY; cur_y<max_y; cur_y++) {
            if(y_start > maxy) { break; }
            if(cur_y >= 0 && cur_x >= 0) {
                int state = -1;
                if(model->grid) {
                    state = model->grid[cur_x][cur_y];
                }
                if(state == 1) {
                    draw_rectangle(cr, &model->commons->cell_col, x_start, y_start, size, size);
                }
                else if(state != 1 && model->commons->visible == 1)  {
                    GdkRGBA *rgba;
                    rgba = gdk_rgba_copy(&model->commons->bgrn_col);
                    color_lighter(rgba, 0.1);
                    draw_rectangle(cr, rgba, x_start, y_start, size, size);
                    gdk_rgba_free(rgba);
                }
            }
            x_start += model->commons->cell_s/model->commons->zoom;
            x_start += model->commons->spacing; // space between cells
        }
        x_start = 2.0;
        y_start += model->commons->cell_s/model->commons->zoom;
        y_start += model->commons->spacing;
    }
}
