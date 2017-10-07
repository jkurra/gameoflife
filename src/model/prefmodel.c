#include "prefmodel.h"

PrefModel *PrefModel_new()
{
    PrefModel *model = (PrefModel*)calloc(1, sizeof(PrefModel));
    model->base.type  = PREF;
    model->main_frame = NULL;
    model->builder = NULL;
    return model;
}

void PrefModel_read( PrefModel *model, const char *file )
{
    //char *json = file_read(file);

    //JsonObject *object = json_create(json);
    //printf("json \n%s\n", json);
/*
    char *bg_col = json_val(json, "backgroundColor", 3);
    char *fr_col = json_val(json, "cellColor", 3);

    gdk_rgba_parse(&model->bgrn_col, bg_col);
    gdk_rgba_parse(&model->cell_col, fr_col);

    model->rows = atoi(json_val(json, "gridRows", 3));
    model->cols = atoi(json_val(json, "gridCols", 3));

    model->infinite;
    model->visible = atoi(json_val(json, "gridVisible", 3));
    model->interval = atoi(json_val(json, "tickInterval", 3));*/

}

void PrefModel_free( PrefModel *model )
{
    if(model) {
        /*if(model->main_frame) {
            free(model->main_frame);
            model->main_frame = NULL;
        }*/
        free(model);
        model = NULL;
    }
}
