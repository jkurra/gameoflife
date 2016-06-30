#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "view.h"
//#include "jsmn/jsm.h"
#include "../manager/config.h"

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/* @brief Initializes new view_model
 *
 * Initializes view model containing game, menu and pref-models. This way any
 * function of those models may be accessed through view_model. It also creates
 * simple and fast way of initializing all necessary models safely without having
 * to initalize every model individually. It is then possible to change active
 * model to close and open other views included in this model. Must be freed
 * using model_view_free.
 *
 * @param type Type of the model that is set active.
 * @param pref_path Path to file containing settings.
 * @return Pointer to newly allocated view_model.
 */
view_model *model_view_new( int type, char *pref_path );

/* @brief Get new view model.
 *
 */
game_model *model_game_new();

/* @brief Get new view model.
 *
 */
menu_model *model_menu_new();

/* @brief Get new view model.
 *
 */
pref_model *model_pref_new();

/* @brief Get new view model.
 *
 */
commons_model *model_commons_new();

/* @brief Free given model.
 *
 */
void model_view_free( view_model *model );

/* @brief Get new view model.
 *
 */
void model_game_free( game_model *model );

/* @brief Get new view model.
 *
 */
void model_menu_free( menu_model *model );

/* @brief Get new view model.
 *
 */
void model_pref_free( pref_model *model );

/* @brief Free given view model.
 *
 */
void model_commons_free( commons_model *model );

/* @brief Attach update function id to timer
 *
 */
void model_attach_timer( view_model *model, int interval );

/* @brief Remove timer
 *
 */
void model_remove_timer( view_model *model, int timer_id );

/* @brief Update
 *
 */
void model_update( view_model *model, int type );

/* @brief Get new view model.
 *
 */
void model_game_setup( game_model *model, const char *pref_path );

/* @brief Get new view model.
 *
 */
void model_pref_setup( pref_model *model, const char *pref_path );


/* TODO: these actually belong to view */

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

#endif /* MODEL_H_ */
