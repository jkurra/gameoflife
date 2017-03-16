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
int GameArea_x_pos( gpointer data, float x, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int max_x = model->g_model->grid->rows,
		cur_x = 0;

    float x_start = 5.0;
    int x_cell = 0;

    float x_max = 0;
    float x_min = 0;
    x_cell += model->g_model->startY;

    for(cur_x=model->g_model->startX; cur_x<max_x; cur_x++) {
		x_max = x_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += model->g_model->cell_s*model->g_model->zoom;
        x_start += model->g_model->spacing; // space between cells
    }
	//g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",x, x_min, x_max);
    return pos;
}

int GameArea_y_pos( gpointer data, float y, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int	max_y = model->g_model->grid->cols, cur_x = 0;

    float y_start = 5.0;
    int   x_cell = 0;

    float x_max = 0;
    float x_min = 0;

    x_cell += model->g_model->startX;

    for(cur_x=model->g_model->startY; cur_x<max_y; cur_x++) {
		x_max = y_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = y_start;
        if(y>x_min && y<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        y_start += model->g_model->cell_s*model->g_model->zoom;
        y_start += model->g_model->spacing; // space between cells

    }      //  g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",y, x_min, x_max);
    return pos;
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

        for(int cur_x=area1->startX; cur_x<area1->grid->rows; cur_x++) {
            if(x_point > maxx) { break; }
            for(int cur_y=area1->startY; cur_y<area1->grid->cols; cur_y++) {
                if(y_point > maxy) { break; }
                if(area1->grid->g_grid[cur_x][cur_y]->state == 1 ) {//g_print("grid x: %f:%f", x_point, area1->cell_s*area1->zoom);
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
