#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "view.h"
#include "jsmn/jsm.h"

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/** @brief Initialize current model.
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
void model_init_view( view_model *model );

/** @brief Draw current model.
 *
 * Adds selected view to gtk-widget draw queue. Gives quick way of updating the
 * view without having to select which view needs to be drawn. As long as
 * view_model contains correct view and type, it can automatically select right
 * update function.
 *
 * @param model Contains view to be updated.
 */
void model_draw_view( view_model *model );

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
void model_close_view( view_model *model );

void model_update( view_model *model, int type );

void model_rwrite( view_model *model, int type );

void model_game_save( game_model *model, const char *pref_path );

void model_game_setup( game_model *model, const char *pref_path );

#endif /* MODEL_H_ */
