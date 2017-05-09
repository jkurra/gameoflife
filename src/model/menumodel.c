#include "menumodel.h"

MenuModel *MenuModel_new()
{
    MenuModel *model = (MenuModel*)calloc(1, sizeof(MenuModel));
    model->base.type  = MENU;
    model->main_frame = NULL;
    model->builder = NULL;
    return model;
}

void MenuModel_free( MenuModel *model )
{
    if(model) {
        //if(model->main_frame) {
            /*free(model->main_frame);
            model->main_frame = NULL;*/
        //}
        free(model);
        model = NULL;
    }
}

void MenuModel_read( MenuModel *model, const char *file )
{
    model->grid = Grid_new(100, 100);
    printf("created new grid: %d\n", model->grid->gArray->rows);
}
