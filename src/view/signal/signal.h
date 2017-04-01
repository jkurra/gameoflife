#ifndef SIGNAL_H_INCLUDED
#define SIGNAL_H_INCLUDED

#include <gtk/gtk.h>
/* OpenGL imports */
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "../../model/model.h"

/** @brief
 *
 *  @param
 */
G_MODULE_EXPORT
void on_MainWindow_destroy( GtkWidget *widget, gpointer data );

/** @brief
 *
 *  @param
 */
G_MODULE_EXPORT
void on_ToMenu_clicked( GtkButton *button, gpointer data );

/** @brief
 *
 *  @param
 */
G_MODULE_EXPORT
void on_ToGame_clicked( GtkButton *button, gpointer data );

/** @brief
 *
 *  @param
 */
G_MODULE_EXPORT
void on_ToPref_clicked( GtkButton *button, gpointer data );

#endif /* SIGNAL_H_ */
