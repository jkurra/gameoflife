#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>

#include "view.h"
#include "../data/grid.h"
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
view_model *model_view_new( int type, config *conf );

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


#endif /* MODEL_H_ */
