#include "bmodel.h"

BModel *BModel_new()
{
    BModel *model = (BModel*)calloc(1, sizeof(BModel));

    model->cell_s = 15.0f;		/* Size of each cell in the screen. */
    model->space  = 1.0f;

    model->margin_left  = 10.0f;
    model->margin_right = 10.0f;
    model->margin_up    = 10.0f;
    model->margin_down  = 10.0f;

    model->zoom = 0.0f;

    //printf("bmodel values initialized\n");
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

        char *bgrn = NULL;

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

char *BModel_json( BModel *bmodel )
{
    JsonObject *bmodelObject = json_parse(NULL);

	char *margin_left = (char*) calloc(10, sizeof(char*));
	char *margin_right = (char*) calloc(10, sizeof(char*));
	char *margin_up = (char*) calloc(10, sizeof(char*));
	char *margin_down = (char*) calloc(10, sizeof(char*));

	char *zoom = (char*) calloc(10, sizeof(char*));

    char *cell_s = (char*) calloc(10, sizeof(char*));
    char *space = (char*) calloc(10, sizeof(char*));

    sprintf(margin_left,"%f",bmodel->margin_left);
    sprintf(margin_up,"%f",bmodel->margin_up);
    sprintf(margin_right,"%f",bmodel->margin_right);
    sprintf(margin_down,"%f",bmodel->margin_down);

    sprintf(zoom,"%f",bmodel->zoom);
    sprintf(cell_s,"%f",bmodel->cell_s);
    sprintf(space,"%f",bmodel->space);

    //JsonKeypair interval = json_keypair_create( "interval", iv);
    json_add_value(bmodelObject, json_keypair_create("margin_left", margin_left));
    json_add_value(bmodelObject, json_keypair_create("margin_right", margin_right));
    json_add_value(bmodelObject, json_keypair_create("margin_up", margin_up));
    json_add_value(bmodelObject, json_keypair_create("margin_down", margin_down));

    json_add_value(bmodelObject, json_keypair_create("zoom", zoom));
    json_add_value(bmodelObject, json_keypair_create("cell_s", cell_s));
    json_add_value(bmodelObject, json_keypair_create("space", space));

    //json_add(engineObject, json_tok());
    return bmodelObject->main_object;
}
