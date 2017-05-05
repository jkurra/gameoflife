#include "model.h"

Model *model_new()
{
    Model *model = (Model*)calloc(1, sizeof(Model));
    /*
        Base model has a type which is used to determine wheter
        it can be cast to another "subclass". Available subcasses
        can be found in "model.h"
    */
    model->type = -1;

    return model;
}

void model_free( Model *model )
{
    if(model) {
        free(model);
        model = NULL;
    }
}
