#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <gtk/gtk.h>

#include "gamearea/gamearea.h"
#include "../model/viewobject.h"
#include "../model/model.h"
#include "../output/log.h"

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/** @brief Intialize view using base Model.
 *
 *  Intializes view using given model. Model must be a subclass of baseclass Model.
 *  Model is recognised using "type" value in model. Available subclasses can be
 *  found from "Model.h" file and constructed using corresponding constructor
 *  functions. Subclass must be cast to base "Model" class before using this
 *  function. For example, with GameModel you would use
 *  "Model *model = (Model*)game_model". Invalid casts cannot be caught in this
 *  function so user must be careful.
 *
 *  @param model Base class of the model to show.
 */
void view_show( Model *model );

/** @brief Intialize view using base Model.
 *
 *  Intializes view using given model. Model must be a subclass of baseclass Model.
 *  Model is recognised using "type" value in model. Available subclasses can be
 *  found from "Model.h" file and constructed using corresponding constructor
 *  functions. Subclass must be cast to base "Model" class before using this
 *  function. For example, with GameModel you would use
 *  "Model *model = (Model*)game_model". Invalid casts cannot be caught in this
 *  function so user must be careful.
 *
 *  @param model Base class of the model to show.
 */
void view_hide( Model *model );

/** @brief Free view model values and close it.
 *
 *  Calls free() for each dynamically allocated variable within subclass of Model.
 *  Checks if variable is NULL before attempting to free it. Subclass must be cast
 *  to base "Model" class before using this function. For example, with GameModel
 *  you would use "Model *model = (Model*)game_model". Invalid casts cannot be
 *  caught in this function so user must be careful.
 *
 * @param model Model to be closed.
 */
void view_destroy( Model *model );

#endif /* VIEW_H_ */
