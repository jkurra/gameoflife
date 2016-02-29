#include "model.h"
#include "jsm.h"
int read_file(char *buff, const char *fname);

gboolean model_grid_update( view_model *model )
{
//	g_print("testing");
	grid_next(model->game->grid_x, model->game->grid_y, model->game->grid);
	//print_game(game_data->grid);
	//gtk_widget_queue_draw (game_data->win);
//g_print("testing");
 		//model_draw_game(game_data);
		model_draw_view(model);
    return TRUE;
}

void model_init_view( view_model *model )
{
	switch(model->type) {
		case MENU:
			//g_print("drawing menu\n");
			view_menu_init( model );
			break;
		case GAME:
			//g_print("drawing game\n");
			model_game_data( model->game, model->pref_path);
			//g_print("model : %d", model->game->grid_x);
			model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model);
			view_game_init( model );
			break;
		case PREF:
			view_pref_init( model );
			break;
		default:
			break;
	}
}

void model_draw_view( view_model *model )
{
	switch(model->type) {
		case MENU://g_print("drawing menu");
			gtk_widget_queue_draw (model->menu->main_frame);
			break;
		case GAME://g_print("drawing game1");
			//model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model->game);
			gtk_widget_queue_draw (model->game->main_frame);
			//model->game->timerid = g_timeout_add(model->game->tick_t, (GSourceFunc) model_grid_update, model->game);
			break;
		case PREF:
			gtk_widget_queue_draw (model->pref->main_frame);
			break;
		default:
			break;
	}
}

void model_draw_game( game_model *model )
{
	gtk_widget_queue_draw (model->main_frame);
}

int model_game_data( game_model *model, const char *file)
{
	int  **grid;
	char **json;

	int rtn = jsm_read_file(&json, file);//read_file(json, file); // read json file

	if(rtn == JSM_OK) { /* file read successfully */
		char *tick_time[30], *x_size[30], *y_size[30];

		jsm_val( tick_time, json, "TICK_TIME" );
		jsm_val( x_size, json, "X_SIZE" );
		jsm_val( y_size, json, "Y_SIZE" );

		int x = atoi(x_size); /* TODO  check if cast was succesfull */
		int y = atoi(y_size);

		int time = atoi(tick_time);

		//grid = grid_init( x, y, grid );
		//grid = grid_rand( x, y, grid );

		/* populate values for model */
		model->grid_x = x;
		model->grid_y = y;
		model->tick_t = time;

		/* static modifiers for now */
		model->cell_s = 10;
		model->zoom   = 1;
		model->tick_t = 100;

		model->grid = grid_init(x, y, model->grid);
		model->grid = grid_rand(x, y, model->grid);

		/* set drawing start point at beginning of grid */
		model->startAtCellX = 0;
		model->startAtCellY = 0;
	}

    return rtn;
}

void model_menu_data( view_model *model )
{

}

void model_pref_data( view_model *model )
{

}


static void cat(FILE *fp)
{
    char   buffer[4096];
    size_t nbytes;
    while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) != 0)
			fwrite(buffer, sizeof(char), nbytes, stdout);
}

int read_file(char *buff, const char *fname) {

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    else {
		perror("getcwd() error");
	}



   char *result = malloc(strlen(cwd)+strlen(fname)+1);//+1 for the zero-terminator
   //in real code you would check for errors in malloc here
   strcpy(result, cwd);
   strcat(result, fname);
  printf("test..%s\n", result);
  FILE *fp = fopen(result, "r");

  const char *file;
	long lSize;
  char *buffer;
      //while ((file = *++argv) != 0)
      //{
          if ((fp = fopen(result, "r")) != 0)
          {
              fseek( fp , 0L , SEEK_END);
              lSize = ftell( fp );
              rewind( fp );
             // cat(fp);
              buffer = calloc( 1, lSize+1 );
              if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

              /* copy the file into the buffer */
              if( 1!=fread( buffer , lSize, 1 , fp) )
                fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

             // fclose(fp);
          }
          else {
			  return -1;
		  }

       printf( "std : %s\n", buffer );
       buff[lSize] = '\0';
       int i=0;
       for(i=0; i<lSize; i++)
		buff[i] = buffer[i];


      // struct jsmn_parser *parser;
      // jsmn_init(&parser);


      // jsmntok_t tokens[256];
       //const char *js;
       //js = tokens[0];
       //int len = 500;
       //len = strlen(buffer);
       //printf("len: %d\n", len );
      // jsmn_parse(parser, buffer+1, len, tokens, 256);

       //printf("tokens: %d\n", err );
      //}
  //if(f != NULL) {
      //fprintf(f, "Testing...\n");
  //}
  return 0;
}
