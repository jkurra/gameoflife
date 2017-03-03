#include "gamearea.h"

void draw_rectangle1( cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height )
{
	if(cairo && color) {
		cairo_rectangle(cairo, start_x, start_y, width, height);
		gdk_cairo_set_source_rgba(cairo, color);
		cairo_fill(cairo);
	} else { }
}

void color_lighter1( GdkRGBA *rgba, float level )
{
    rgba->red   += level;
    rgba->green += level;
    rgba->blue  += level;
}

void draw_GameArea( GtkDrawingArea *area, cairo_t *cr, gpointer data   )
{
    GameModel *area1 = (GameModel*)data;

    if(area1) {
		//g_print("Found area");
        GtkAllocation widget_alloc;
        /* Get current allocation for widget to know draw size. */
        gtk_widget_get_allocation(GTK_WIDGET(area), &widget_alloc);

        int maxx = widget_alloc.width,
            maxy = widget_alloc.height;
        /* How much space is left between first drawn cell and widget border. */
        float x_point = 5.0,//area->margin,
              y_point = 5.0;// area->margin;
        /* Draw background */
        GdkRGBA *bgrn_col = NULL; /* Background color of the grid */
        GdkRGBA *cell_col = NULL; /* Color of each cell in grid */

        cell_col = gdk_rgba_copy(&area1->cell_col);
        bgrn_col = gdk_rgba_copy(&area1->bgrn_col);

	    cairo_rectangle(cr, 0, 0, maxx, maxy);
	    gdk_cairo_set_source_rgba(cr, bgrn_col);
	    cairo_fill(cr);

        for(int cur_x=area1->startX; cur_x<area1->rows; cur_x++) {
            if(x_point > maxx) { break; }
            for(int cur_y=area1->startY; cur_y<area1->cols; cur_y++) {
                if(y_point > maxy) { break; }
                if(area1->grid[cur_x][cur_y] == 1) {//g_print("grid x: %f:%f", x_point, area1->cell_s*area1->zoom);
                    draw_rectangle1(cr, cell_col, x_point, y_point, area1->cell_s*area1->zoom, area1->cell_s*area1->zoom);
                }
                else {
					if(area1->visible) {
	                    GdkRGBA *rgba;

	                    rgba = gdk_rgba_copy(bgrn_col); // gdk_rgba_copy(area->bgrn_col);
	                    color_lighter1(rgba, 0.1);
	                    //draw_rectangle1(cr, rgba, x_point, y_point, area1->cell_s* area1->zoom, area1->cell_s*area1->zoom);
	                    cairo_rectangle(cr, x_point, y_point, area1->cell_s*area1->zoom, area1->cell_s*area1->zoom);
	                    gdk_cairo_set_source_rgba(cr, rgba);
	                    cairo_fill(cr);
	                    gdk_rgba_free(rgba);
					}
                }
                x_point += area1->cell_s*area1->zoom;
                x_point += area1->spacing;
        }
        x_point = 5;
        /* add size of the cell and space between each cell to the columns */
        y_point += area1->cell_s*area1->zoom;
        y_point += area1->spacing;
    }
    //free(cell_col);
    //free(bgrn_col);
}
}
