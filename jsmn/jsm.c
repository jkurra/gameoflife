#include "jsm.h"

jsmrtn_t jsm_default_model ( view_model *model )
{
	int rtn = JSM_OK;

	if(!model) {
		rtn = JSM_NULL;
	}
	else {
		FILE *fp;
		fp = fopen(model->pref_path, "w");
		if (fp == NULL) {
			rtn = JSM_ERROR_FREAD;
			printf("Couldn't open file for writing.\n");
			//exit(0);
		}
		fprintf(fp, "{\n");
		fprintf(fp, "   \"X_SIZE\": \"200\",\n");
		fprintf(fp, "   \"Y_SIZE\": \"200\",\n");
		fprintf(fp, "   \"TICK_TIME\": \"200\"\n");
		fprintf(fp, "}");

		fclose(fp);
	}
	return rtn;
}

jsmrtn_t jsm_update_model ( view_model *model )
{
	int rtn = JSM_OK;

	if(!model) {
		rtn = JSM_NULL;
	}
	else {
		printf("JSM [SAVE] :%s\n", model->pref_path);
		printf("JSM [SAVE] :%d\n", model->game->grid_x);
		printf("JSM [SAVE] :%d\n", model->game->grid_y);
		printf("JSM [SAVE] :%s\n", gdk_rgba_to_string (&model->game->backGround));
		printf("JSM [SAVE] :%s\n", gdk_rgba_to_string (&model->game->cellColor));

		FILE *fp;
		fp = fopen(model->pref_path, "w");
		if (fp == NULL) {
			rtn = JSM_ERROR_FREAD;
			printf("Couldn't open file for writing.\n");
			//exit(0);
		}

		fprintf(fp, "{\n");
		fprintf(fp, "   \"X_SIZE\": \"%d\",\n", 	 model->game->grid_x);
		fprintf(fp, "   \"Y_SIZE\": \"%d\",\n", 	 model->game->grid_y);
		fprintf(fp, "   \"TICK_TIME\": \"%d\",\n",  model->game->tick_t);
		fprintf(fp, "   \"bgColor\": \"%s\",\n",  gdk_rgba_to_string (&model->game->backGround));
		fprintf(fp, "   \"frColor\": \"%s\"\n",  gdk_rgba_to_string (&model->game->cellColor));
		fprintf(fp, "}");

		fclose(fp);
		printf("done.\n");
	}

	return rtn;
}

jsmrtn_t jsm_read_model( view_model *model )
{
	int rtn = JSM_NULL;
	char **json;

	if( model ) {
		rtn = jsm_read_file(&json, model->pref_path);
	}

	if(rtn == JSM_OK) { /* file read successfully */
		char *tick_time[30], *x_size[30], *y_size[30], *bgCol[30], *frCol[30];

		rtn = jsm_val( tick_time, json, "TICK_TIME" );
		rtn = jsm_val( x_size, json, "X_SIZE" );
		rtn = jsm_val( y_size, json, "Y_SIZE" );
		rtn = jsm_val( bgCol,  json, "bgColor" );
		rtn = jsm_val( frCol,  json, "frColor" );

		int x = atoi(x_size); /* TODO  check if cast was succesfull */
		int y = atoi(y_size);

		int time = atoi(tick_time);

		/* populate values for model */
		model->game->grid_x = x;
		model->game->grid_y = y;
		model->game->tick_t = time;

		/* parse colors to model  */
		gdk_rgba_parse (&model->game->backGround, bgCol);
		gdk_rgba_parse (&model->game->cellColor , frCol);

		/* static modifiers for now */
		model->game->cell_s = 10;
		model->game->zoom   = 1;
		model->game->tick_t = 100;

		model->game->grid = grid_init(x, y, model->game->grid);
		model->game->grid = grid_rand(x, y, model->game->grid);

		/* set drawing start point at beginning of grid */
		model->game->startAtCellX = 0;
		model->game->startAtCellY = 0;
	}

	return rtn;
}

jsmrtn_t jsm_read_file(char **json, const char *file)
{

	int rtn = JSM_OK;
	printf("JSM [OPEN] :%s:...", file);

	FILE *fptr = fopen(file, "r");

	if( fptr != 0) {
		printf("done.\n");
		fseek( fptr , 0L , SEEK_END);
		long flen = ftell( fptr ); /* how many characters in file */
        rewind( fptr );

		char **buffer = calloc( sizeof(char), flen+1 );
		if(!buffer) {
			printf("JSM [ERROR] : Unable to allocate memory.", file);
			rtn = JSM_ERROR_ALLOC;
		}
		else {
			fread( buffer, flen, 1 , fptr);
		}
    fclose(fptr); /* close filestream */
		(*json) = buffer;
	}
	else {
		printf("failed.\n");
		rtn = JSM_ERROR_FREAD;
	}

	return rtn;
}

jsmrtn_t jsm_write_file(char *json, const char *file)
{
	int i=0, r = JSM_OK;
	printf("trying to open file : %s\n", file);

	FILE *fp = fopen(file, "rw");
	fwrite ( json , sizeof(char), sizeof(json) , fp );
	fclose(fp);

	return r;
}

jsmrtn_t jsm_val(char *rtn3, const char *json, const char *key)
{
	int rtn = JSM_OK;
	printf("JSM [PARSE] : %s : ", key);
	/* Calculate lenght for the full json */
	if( !key || !json ) {
		rtn = JSM_NULL;
	}

	if(rtn == JSM_OK) {
		int i=0, l=strlen(json);
		/* Parse all elements into an array */
		jsmn_parser parser;
		jsmntok_t 	tokens[256];
		jsmn_init(&parser);
		jsmn_parse(&parser, json, l, tokens, 256);
		int size = tokens->size; /* number of found json elements */
	  //printf("size : %s.", json);
		for(i=0; i<size; i++) {
			jsmntok_t *tmp_t = &tokens[i];
			int size = tmp_t->end-tmp_t->start;
		  if(tmp_t->type == JSMN_STRING) { /* Value is string */
				char nn[size];
				jsm_obj(nn, json, tmp_t->start, tmp_t->end);
				if(strcmp(nn, key) == 0) {
					jsmntok_t *tmp_t2 = &tokens[i+1];
					/*if(tmp_t2->type == JSMN_PRIMITIVE) { /* Value is primitive */
					//		printf("Object values must be strings or primitives.");
					//}*/
					jsmntok_t *tmp1 = &tokens[i+1];// next value is the data
					int tmp1_size = tmp1->end-tmp1->start;
					char nn1[tmp1_size];
					jsm_obj( nn1, json, tmp1->start, tmp1->end );
					jsm_obj( rtn3, json, tmp1->start, tmp1->end ); /* add to return data */
				}
			}
		}
		printf("%s done.\n", rtn3);
	}

	return rtn;
}

jsmrtn_t jsm_obj(char *result, const char *full_json, int start, int end)
{
	int rtn = JSM_OK;
	if(!full_json) {
		rtn = JSM_NULL;
	}
	else {
		int i=0, k=0, 		/* index for the result array */
			s=end-start; 	/* size of the string */
		result[s] = '\0';
		for(i=start; i<end; i++, k++)
			result[k] = full_json[i];
	}

	return rtn;
}
