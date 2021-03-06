#include "gamearea.h"

void draw_rectangle1( cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height )
{
	if(cairo && color) {
		cairo_rectangle(cairo, start_x, start_y, width, height);
		gdk_cairo_set_source_rgba(cairo, color);
	//	cairo_fill(cairo);
	} else { }
}

void color_lighter1( GdkRGBA *rgba, float level )
{
    rgba->red   += level;
    rgba->green += level;
    rgba->blue  += level;
}
int GameArea_x_pos( gpointer data, float x, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int max_x = model->g_model->grid->gArray->rows,
		cur_x = 0;

    float x_start = 5.0;
    int x_cell = 0;

    float x_max = 0;
    float x_min = 0;
    x_cell += model->g_model->startY;

    for(cur_x=model->g_model->startX; cur_x<max_x; cur_x++) {
		x_max = x_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += model->g_model->cell_s*model->g_model->zoom;
        x_start += model->g_model->spacing; // space between cells
    }
	//g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",x, x_min, x_max);
    return pos;
}

int GameArea_y_pos( gpointer data, float y, float width, float height )
{
    int pos = -1;
    ViewObject *model = (ViewObject*)data;

    int	max_y = model->g_model->grid->gArray->cols, cur_x = 0;

    float y_start = 5.0;
    int   x_cell = 0;

    float x_max = 0;
    float x_min = 0;

    x_cell += model->g_model->startX;

    for(cur_x=model->g_model->startY; cur_x<max_y; cur_x++) {
		x_max = y_start+(model->g_model->cell_s*model->g_model->zoom);
		x_min = y_start;
        if(y>x_min && y<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        y_start += model->g_model->cell_s*model->g_model->zoom;
        y_start += model->g_model->spacing; // space between cells

    }      //  g_print("button pressed on game1 %f: x_min:%f, x_max:%f\n",y, x_min, x_max);
    return pos;
}

typedef struct {
	GameModel *area1;
	cairo_t *cr;
	GtkDrawingArea *area;
} DrawModel;


void *drawThread(void *arg)
{

	//printf("redraw game model : %d\n", clock());
	DrawModel *are = (DrawModel*)arg;

    GameModel *area1 = are->area1;
	//printf("Drawing area again. \n" );
	if(area1) {


		GtkAllocation widget_alloc;
		/* Get current allocation for widget to know draw size. */
		gtk_widget_get_allocation(GTK_WIDGET(are->area), &widget_alloc);

		int maxx = widget_alloc.width,
			maxy = widget_alloc.height;
		/* How much space is left between first drawn cell and widget border. */
		float x_point = 5.0,//area->margin,
			  y_point = 5.0;// area->margin;
		/* Draw background */
		GdkRGBA *bgrn_col = NULL; /* Background color of the grid */
		GdkRGBA *cell_col = NULL; /* Color of each cell in grid */

		cell_col = gdk_rgba_copy(&area1->cell_col);
		bgrn_col = gdk_rgba_copy(&area1->bgrn_col);

		cairo_rectangle(are->cr, 0, 0, maxx, maxy);
		gdk_cairo_set_source_rgba(are->cr, bgrn_col);
		cairo_fill(are->cr);
	//g_print("Found area %d", area1->grid->gArray->rows);
		for(int cur_x=area1->startX; cur_x<area1->grid->gArray->rows; cur_x++) {
		//	 GdkRGBA *clr = NULL;
			if(x_point >= maxx) { break; }
			for(int cur_y=area1->startY; cur_y<area1->grid->gArray->cols; cur_y++) {
				if(GridArray_get(area1->grid->gArray, cur_x, cur_y )) {//;area1->grid->gArray->g_array[cur_x][cur_y]) {
					switch (area1->grid->gArray->g_array[cur_x][cur_y]->state) {
						case 0:
							if(area1->visible == 1) {//g_print("Found area");
								 GdkRGBA *clr1 = gdk_rgba_copy(bgrn_col); // gdk_rgba_copy(area->bgrn_col);
								color_lighter1( clr1, 0.1);
								gdk_cairo_set_source_rgba(are->cr, clr1);
								cairo_rectangle(are->cr, x_point, y_point, area1->cell_s*area1->zoom, area1->cell_s*area1->zoom);
								gdk_rgba_free(clr1);
							}
							break;
						case 1:{
							GdkRGBA *clr2 = gdk_rgba_copy(cell_col);
							gdk_cairo_set_source_rgba(are->cr, clr2);
							cairo_rectangle(are->cr, x_point, y_point, area1->cell_s*area1->zoom, area1->cell_s*area1->zoom);
							gdk_rgba_free(clr2);
						}
							break;
						default:
							break;
					}
				}
				cairo_fill(are->cr);
			//	gdk_cairo_set_source_rgba(cr, clr);
				//cairo_fill(cr);
				x_point += area1->cell_s*area1->zoom;
				x_point += area1->spacing;
				//if(clr) {
				//	gdk_rgba_free(clr);
				//}
				if(y_point >= maxy) { break; }
		}
		// gdk_cairo_set_source_rgba(cr, clr);
		// cairo_fill(cr);
		x_point = 5;
		/* add size of the cell and space between each cell to the columns */
		y_point += area1->cell_s*area1->zoom;
		y_point += area1->spacing;
	}
	cairo_fill(are->cr);
	gdk_rgba_free(cell_col);
	gdk_rgba_free(bgrn_col);
	//free(cell_col);
	//free(bgrn_col);
	}
}

void draw_MenuArea( GtkDrawingArea *area, cairo_t *cr, gpointer data   )
{
	MenuModel *area1 = (MenuModel*)data;

	if(area1) {
		//printf("grid has rows : %d\n", area1->grid->gArray->rows);
		GtkAllocation widget_alloc;
        /* Get current allocation for widget to know draw size. */
        gtk_widget_get_allocation(GTK_WIDGET(area), &widget_alloc);

        int maxx = widget_alloc.width,
            maxy = widget_alloc.height;
        /* How much space is left between first drawn cell and widget border. */
        float x_point = 5.0,//area->margin,
              y_point = 5.0;// area->margin;
        /* Draw background */
        GdkRGBA bgrn_col; /* Background color of the grid */
        GdkRGBA cell_col; /* Color of each cell in grid */

        gdk_rgba_parse(&cell_col, "rgb(46,52,54)" );
        gdk_rgba_parse(&bgrn_col, "rgb(46,52,54)");

	    cairo_rectangle(cr, 0, 0, maxx, maxy);
	    gdk_cairo_set_source_rgba(cr, &bgrn_col);
	    cairo_fill(cr);

        for(int cur_x=0; cur_x<area1->grid->gArray->rows; cur_x++) {
            if(x_point >= maxx) { break; }
            for(int cur_y=0; cur_y<area1->grid->gArray->cols; cur_y++) {
				if(GridArray_get(area1->grid->gArray, cur_x, cur_y )) {//;area1->grid->gArray->g_array[cur_x][cur_y]) {
					switch (area1->grid->gArray->g_array[cur_x][cur_y]->state) {
						case 0: {
							GdkRGBA *clr1 = gdk_rgba_copy(&bgrn_col); // gdk_rgba_copy(area->bgrn_col);
							color_lighter1( clr1, 0.1);
							gdk_cairo_set_source_rgba(cr, clr1);
							cairo_rectangle(cr, x_point, y_point, 5*1, 5*1);
							gdk_rgba_free(clr1);

							break;
						}
						case 1: {
						 	GdkRGBA *clr2 = gdk_rgba_copy(&cell_col);
							gdk_cairo_set_source_rgba(cr, clr2);
							cairo_rectangle(cr, x_point, y_point, 5*1, 5*1);
							gdk_rgba_free(clr2);
						}
							break;
						default:
							break;
					}
				}
				cairo_fill(cr);
                x_point += 5;
                x_point += 1;
				if(y_point >= maxy) { break; }
        }
        x_point = 5;
        /* add size of the cell and space between each cell to the columns */
        y_point += 5*1.5;
        y_point +=1;
    }
}
//	cairo_fill(cr);
//	gdk_rgba_free(cell_col);
//	gdk_rgba_free(bgrn_col);

}

void draw_GameArea( GtkDrawingArea *area, cairo_t *cr, gpointer data   )
{

		GameModel *area1 = (GameModel*)data;
		DrawModel md;
		md.area1 = area1;
		md.cr = cr;
		md.area = area;

		pthread_t thread1;
		pthread_create(&thread1, NULL, drawThread, &md);
		pthread_join(thread1, NULL);
}
