#include "jsm.h"

char *jsm_token( const char *json, int start, int end )
{
	char *rtn = NULL;
	int i=0, k=0, 		/* index for the result array */
		size=end-start; 	/* size of the string */

	rtn = (char*)calloc(size+1, sizeof(char*));
	rtn[size] = '\0';
	for(i=start; i<end; i++, k++)
		rtn[k] = json[i];

	return rtn;
}

char *jsm_value( const char *json, char *key, jsmntype_t type)
{
	char *rtn = NULL;
	int i=0;

	/* Initialize parser and read json tokens */
	jsmn_parser parser;
	jsmntok_t tokens[256];
	jsmn_init(&parser);
	jsmn_parse(&parser, json, strlen(json), tokens, 256);

	for(i=0; i<tokens->size; i++) { /* Find tokens that match both key and type */
		if(tokens[i].type == type ) {
			char *tkn = jsm_token(json, tokens[i].start, tokens[i].end);
			if(tkn != NULL && strcmp(tkn, key) == 0) {
				rtn = jsm_token(json, tokens[i+1].start, tokens[i+1].end);
			}
			free(tkn);
		}
	}

	return rtn;
}

char *jsm_json( const char *json, char *key, char *value )
{
	char *rtn = NULL;

	/* Initialize parser and read json tokens */
	jsmn_parser parser;
	jsmntok_t tokens[256];
	jsmn_init(&parser);
	jsmn_parse(&parser, json, strlen(json), tokens, 256);

	int addSize = strlen(key) + strlen(value);
	char *toAdd = calloc(sizeof(char), addSize+6); /* +6 because quotes and such */

	/*  Prepare key-value pair to be added to string. */
	strcat(toAdd, "\"");
	strcat(toAdd, key);
	strcat(toAdd, "\"");
	strcat(toAdd, ":");
	strcat(toAdd, "\"");
	strcat(toAdd, value);
	strcat(toAdd, "\"");

	rtn = calloc(sizeof(char), strlen(json)+strlen(toAdd)+1);
	char *tmp = jsm_token(json, tokens[0].start, tokens[0].end-1);

	strcat(rtn, tmp);
	strcat(rtn,toAdd);
	strcat(rtn, "}");
	free(tmp);
	free(toAdd);

	return rtn;
}

char *jsm_read( const char *file )
{
	char *json = NULL;
	if(file) {
		FILE *src = fopen(file, "r");
		if(src) {
			printf("JSM [READ] : File opened.\n");
			fseek(src , 0L , SEEK_END);
			long flen = ftell(src);
			rewind(src);

			json = calloc(sizeof(char), flen+1);

			if(json) {
				size_t res = fread(json, 1, flen , src);
				json[res] = '\0';
				//if(res != flen) {printf("JSM [ERROR] : Reading failure. %d\n", res);}
			}
			else {
				printf("JSM [ERROR] : Unable to allocate memory.");
			}

			fclose(src);
		}
	}

	return json;
}

jsmrtn_t jsm_write(char *json, const char *file)
{
	int rtn = JSM_OK;

	if(json && file) {
		FILE *src = fopen(file, "w");
		if(src) {
			printf("JSM [WRITE] : File opened for write.\n");
			//printf("%s\n", json);
			////fwrite ( json , sizeof(char), sizeof(json) , src );
			fputs(json, src);
			fclose(src);
		}
		else {
			rtn = JSM_ERROR_FREAD;
		}
	}
	else {
		rtn = JSM_NULL;
	}

	return rtn;
}

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
		printf("JSM [SAVE] :%d\n", model->game->max_x);
		printf("JSM [SAVE] :%d\n", model->game->max_y);
		printf("JSM [SAVE] :%s\n", gdk_rgba_to_string (&model->game->bgrn_col));
		printf("JSM [SAVE] :%s\n", gdk_rgba_to_string (&model->game->cell_col));

		FILE *fp;
		fp = fopen(model->pref_path, "w");
		if (fp == NULL) {
			rtn = JSM_ERROR_FREAD;
			printf("Couldn't open file for writing.\n");
			//exit(0);
		}
		fprintf(fp, "{\n");
		fprintf(fp, "   \"X_SIZE\": \"%d\",\n",    model->game->max_x);
		fprintf(fp, "   \"Y_SIZE\": \"%d\",\n",    model->game->max_y);
		fprintf(fp, "   \"TICK_TIME\": \"%d\",\n", model->game->tick_t);
		fprintf(fp, "   \"bgColor\": \"%s\",\n",   gdk_rgba_to_string (&model->game->bgrn_col));
		fprintf(fp, "   \"frColor\": \"%s\"\n",    gdk_rgba_to_string (&model->game->cell_col));
		fprintf(fp, "   \"gridVis\": \"%d\"\n",    model->game->visible);
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
		grid_free(model->game->max_y, model->game->grid);
		char *tick_time[30], *x_size[30], *y_size[30], *bgCol[30], *frCol[30],*infi[30], *visi[30];

		rtn = jsm_val( tick_time, json, "TICK_TIME" );
		rtn = jsm_val( x_size, json, "X_SIZE" );
		rtn = jsm_val( y_size, json, "Y_SIZE" );
		rtn = jsm_val( bgCol,  json, "bgColor" );
		rtn = jsm_val( frCol,  json, "frColor" );
		rtn = jsm_val( visi,  json, "gridVis" );

		int x = atoi( x_size ); /* TODO  check if cast was succesfull */
		int y = atoi( y_size) ;
		int visible = atoi(visi) ;
		int time = atoi(tick_time);

		/* populate values for model */
		model->game->max_x = x;
		model->game->max_y = y;
		model->game->tick_t = time;

		/* parse colors to model  */
		gdk_rgba_parse( &model->game->bgrn_col, bgCol );
		gdk_rgba_parse( &model->game->cell_col , frCol );

		/* static modifiers for now */
		model->game->cell_s = 10.0;
		model->game->zoom   = 1.0;
		model->game->tick_t = 100;
		model->game->visible = visible;
		model->game->grid = grid_new( x, y );
		grid_rand(x, y, model->game->grid);
		//grid_print(x, y, model->game->grid);
		/* set drawing start point at beginning of grid */
		model->game->startAtCellX = 0;
		model->game->startAtCellY = 0;
	}
	free(json);
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
