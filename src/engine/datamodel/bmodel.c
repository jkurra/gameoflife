#include "bmodel.h"

BModel *BModel_new()
{
    BModel *model = (BModel*)calloc(1, sizeof(BModel));

    return model;
}

void BModel_save( BModel *model )
{
    if(model) {


        char *cell_s = (char*) calloc(10, sizeof(char*));
        char *zoom_s = (char*) calloc(10, sizeof(char*));

        char *m_right = (char*) calloc(10, sizeof(char*));
        char *m_left = (char*) calloc(10, sizeof(char*));
        char *m_up = (char*) calloc(10, sizeof(char*));
        char *m_down = (char*) calloc(10, sizeof(char*));

        gchar *bgrn = NULL;

        //sprintf(rows, "%d",   model->cell_s);
        //sprintf(rows, "%d",   model->zoom);

        /*sprintf(rows, "%d",   model->grid->gArray->rows);
        sprintf(cols, "%d",   model->grid->gArray->cols);
        sprintf(t_time, "%d", model->interval);
        sprintf(vis, "%d",    model->visible);

        gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
        gchar *cell = gdk_rgba_to_string(&model->cell_col);

        printf("saving bgrn: %s\n", bgrn);
        printf("saving cell: %s\n", cell);

		JsonObject *object = json_parse(NULL);

        char *zoom = (char*)calloc(10, sizeof(char*));
        sprintf(zoom, "%f", model->zoom);

		json_add_value(object, json_keypair_create("gridRows", rows));
		json_add_value(object, json_keypair_create("gridCols", cols));
		json_add_value(object, json_keypair_create("tickInterval", t_time));
		json_add_value(object, json_keypair_create("gridVisible", vis));
		json_add_value(object, json_keypair_create("backgroundColor", bgrn));
		json_add_value(object, json_keypair_create("cellColor", cell));
        json_add_value(object, json_keypair_create("defaultTheme", model->themes->sel_name));
        json_add_value(object, json_keypair_create("zoom", zoom));

        free(bgrn);
        free(cell);
        ///printf("Writing object: \n %s\n", object->main_object);
        file_write(object->main_object, model->conf->sel_path);*/
    }
}

void BModel_read( BModel *model )
{

}
