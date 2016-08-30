#include "draw.h"

void draw_rectangle( cairo_t *cairo, GdkRGBA *color,
                     int start_x, int start_y,
                     int width,   int height )
{
    cairo_rectangle(cairo, start_x, start_y, width, height);
	gdk_cairo_set_source_rgba(cairo, color);
	cairo_fill(cairo);
}

void draw_grid( cairo_t *cr, int **grid, int height, int width )
{
    for(int i=0; i<width; i++) {
        for(int k=0; k<height; k++) {

        }
    }
}
