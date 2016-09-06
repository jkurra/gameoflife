#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "view.h"
#include "model.h"

/** @brief Change current model.
 *
 * Controller changes current model based on user input. This function takes
 * new model as input and prepares appropriate model based on currently
 * selected model. This way as model is received, it doesn't matter where
 * the signal was from and appropriate action can be taken. This function
 * is meant for changing the model, it can only handle specific models since it
 * is often necessary to modify current models, for example close current
 * window.
 *
 * @param model Model to be changed.
 * @param type  Type of the new model.
 */
void controller_model( view_model *model, int type );

#endif /* CONTROLLER_H_ */
