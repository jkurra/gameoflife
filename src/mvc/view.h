#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "../manager/theme.h"
#include "../manager/config.h"
#include "drawing/graphics.h"
#include "model.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/** @brief Initialize values current model.
 *
 * Initializes view using view_model, which contains type value. Type value is
 * used to determine which model is to be initialized. Therefore it must be set
 * before calling this function, otherwise behaviour may be unexpected. It is
 * also good to notice that this function doesn't free views that may be
 * initialized, so that must be taken care of before calling this function to
 * avoid double assingments of widgets. This function is meant to be used when
 * it is necessary to initialize view using view_model. This way all necessary
 * data is present when values are assigned.
 *
 * @param model Contains data needed to initialize view.
 */
void view_init( view_model *model, int type );


/** @brief Draw current model.
 *
 * Adds selected view to gtk-widget draw queue. Gives quick way of updating the
 * view without having to select which view needs to be drawn. As long as
 * view_model contains correct view and type, it can automatically select right
 * update function.
 *
 * @param model Contains view to be updated.
 */
void view_draw( view_model *model );

/** @brief Close current model.
 *
 * unrefs and calls destroy on currently active views main widget. Notice that
 * type must point to correct widget type or it may try to release incorrect
 * view. Make sure to call this before changing widget type and calling init_view.
 * Purpose of this function is to provide quick way of freeing view. However since
 * view_model contains multiple sub-views it is up to user to make sure that
 * correct view is selected. In future more checks may be assigned to avoid
 * mistakes.
 *
 * @param model Contains view to be closed.
 */
void view_close( view_model *model );

gboolean view_timer_update( game_model *model );

#endif /* VIEW_H_ */
