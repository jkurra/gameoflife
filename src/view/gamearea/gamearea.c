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

int GameArea_x_pos( GameEngine *engine, float x )
{
    int pos = -1;

    int max_x = engine->board->rows,
		cur_x = 0;

    float x_start = engine->bmodel->margin_left;
    int x_cell = 0;

    float x_max = 0;
    float x_min = 0;

    for(cur_x=0; cur_x<max_x; cur_x++) {
		x_max = x_start+engine->bmodel->cell_s;
		x_min = x_start;
        if(x>x_min && x<x_max) {
            pos = x_cell;
            break;
        }
        x_cell++;
        //cur_x = x_cell;
        x_start += engine->bmodel->cell_s;
        x_start += engine->bmodel->space; // space between cells
    }
	g_print("button pressed on game1 %f: x_min:%f, x_max:%f = %d\n",x, x_min, x_max, pos);

    return pos;
}

int GameArea_y_pos( GameEngine *engine, float y )
{
	int pos = -1;

    int max_y = engine->board->rows,
		cur_y = 0;

    float y_start = engine->bmodel->margin_up;
    int y_cell = 0;

    float y_max = 0;
    float y_min = 0;

    for(cur_y=0; cur_y<max_y; cur_y++) {
		y_max = y_start+engine->bmodel->cell_s;
		y_min = y_start;
        if(y>y_min && y<y_max) {
            pos = y_cell;
            break;
        }
        y_cell++;

        y_start += engine->bmodel->cell_s;
        y_start += engine->bmodel->space; // space between cells
    }
	g_print("button pressed on game1 %f: x_min:%f, x_max:%f = %d\n",y, y_min, y_max, pos);

    return pos;
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
							//if(area1->visible == 1) {
								//g_print("Found area");
								GdkRGBA *clr1 = gdk_rgba_copy(&bgrn_col); // gdk_rgba_copy(area->bgrn_col);
								color_lighter1( clr1, 0.1);
								gdk_cairo_set_source_rgba(cr, clr1);
								cairo_rectangle(cr, x_point, y_point, 5*1, 5*1);
								gdk_rgba_free(clr1);
							//}
							break;}
						case 1:{
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
}

GameArea_draw_nodes( GtkDrawingArea *area, cairo_t *cr, gpointer data )
{


}

void draw_GameArea( GtkDrawingArea *area, cairo_t *cr, gpointer data   )
{
	time_t start,end;
    start=clock();
	GameEngine *engine = (GameEngine*)data;

    if(engine) {

        GtkAllocation widget_alloc;
        /* Get current allocation for widget to know draw size. */
        gtk_widget_get_allocation(GTK_WIDGET(area), &widget_alloc);

        int maxx = widget_alloc.width,
            maxy = widget_alloc.height;

	    float margin_up    = engine->bmodel->margin_up;
		float margin_down  = engine->bmodel->margin_down;
		float margin_left  = engine->bmodel->margin_left;
		float margin_right = engine->bmodel->margin_right;

		float cell_s = engine->bmodel->cell_s;
		float x_point = margin_left ,//area->margin,
			  y_point = margin_up ;// area->margin;

		float spacing =engine->bmodel->space;

		int rows = engine->board->rows,
			cols = engine->board->cols;
		/* Draw background */
        GdkRGBA bgrn_col; /* Background color of the grid */
        gdk_rgba_parse(&bgrn_col, "rgb(40,50,52)");

	    cairo_rectangle(cr, 0, 0, maxx, maxy);
	    gdk_cairo_set_source_rgba(cr, &bgrn_col);
	    cairo_fill(cr);

        for(int cur_x=0; cur_x<rows; cur_x++) {
            if(x_point >= maxx) { break; }
            for(int cur_y=0; cur_y<cols; cur_y++) {
				Node *n = Board_get(engine->board, cur_x, cur_y );
				if(n) {
					GdkRGBA clr2;
					gdk_rgba_parse(&clr2, "rgb(20,12,54)");
					gdk_cairo_set_source_rgba(cr, &clr2);
					cairo_rectangle(cr, x_point, y_point, cell_s, cell_s );
					//gdk_rgba_free(clr2);
				}
				else {
					GdkRGBA *clr1 = gdk_rgba_copy(&bgrn_col); // gdk_rgba_copy(area->bgrn_col);
					color_lighter1( clr1, 0.1);
					gdk_cairo_set_source_rgba(cr, clr1);
					cairo_rectangle(cr, x_point, y_point, cell_s , cell_s );
					gdk_rgba_free(clr1);
				}
				cairo_fill(cr);
                x_point += cell_s ;// area1->cell_s*area1->zoom;
                x_point += spacing;// area1->spacing;
				if(y_point >= maxy) { break; }
        	}
	        x_point = margin_left;

	        /* add size of the cell and space between each cell to the columns */
	        y_point += cell_s ;// area1->cell_s*area1->zoom;
	        y_point += spacing;// area1->spacing;
		}
	}
	end = clock();
	time_t t = (end-start);
}
