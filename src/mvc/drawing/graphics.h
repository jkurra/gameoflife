#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#define GRID 0
#define CELL 1

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

typedef struct
{
    GtkDrawingArea  *area;
    cairo_t  *cairo;

} draw_widget;

void graphics_draw( int type, GtkDrawingArea *area, cairo_t *cr, gpointer data );

#endif /* GRAPHICS_H_ */
