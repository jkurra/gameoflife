#include "gamearea.h"
#include "../view.h"

int GameArea_x_pos( gpointer data, float x, float width, float height )
{
    int pos = -1;
    view_model *model = (view_model*)data;

    //GtkAllocation widget_alloc;
//    int maxx = width,
//        maxy = height;

    int max_x = model->game->commons->rows,
        //max_y = model->game->commons->cols,
        cur_x = 0;
        //interval = model->game->commons->interval;
    //    step = model->game->c_step;

    float x_start = 2.0;
    int x_cell = 0;
    //g_print("g:%d", max_x);
    float x_max = 0;
    float x_min = 0;
    x_cell += model->game->startAtCellY;
    for(cur_x=model->game->startAtCellX; cur_x<max_x; cur_x++) {
        x_max = x_start+(model->game->commons->cell_s/model->game->commons->zoom);
        x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            //g_print("pos x:%f,\n",y);
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += model->game->commons->cell_s/model->game->commons->zoom;
        x_start += model->game->commons->cell_s/model->commons->spacing; // space between cells
        //g_print("button pressed on game1 : x_min:%f, x_max:%f\n", x_min, x_max);
    }
    //g_print("button pressed on game1 : x:%d.\n", pos);
    return pos;
}

int GameArea_y_pos( gpointer data, float y, float width, float height )
{
    int pos = -1;
    view_model *model = (view_model*)data;

    //GtkAllocation widget_alloc;
    //gtk_widget_get_allocation(GTK_WIDGET(model->game->area), &widget_alloc);
    //int maxx = width,
    //    maxy = height;

    int// max_x = model->game->commons->rows,
        max_y = model->game->commons->cols,
        cur_x = 0;
        //cur_y = model->game->startAtCellY;
        //interval = model->game->commons->interval,
        //step = model->game->c_step;


    float y_start = 2.0;
    int x_cell = 0;
    //g_print("g:%d", max_x);
    float x_max = 0;
    float x_min = 0;

    x_cell += model->game->startAtCellX;

    for(cur_x=model->game->startAtCellY; cur_x<max_y; cur_x++) {
        x_max = y_start+(model->game->commons->cell_s/model->game->commons->zoom);
        x_min = y_start;
        if(y>x_min && y<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        y_start += model->game->commons->cell_s/model->game->commons->zoom;
        y_start += model->game->commons->cell_s/model->commons->spacing; // space between cells
        //g_print("button pressed on game1 : x_min:%f, x_max:%f\n", x_min, x_max);
    }
    return pos;
}
