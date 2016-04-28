#include "jsm.h"

char *jsm_keypair( char *key, char *value, int comma )
{
	char *rtn = NULL;

	int klen = strlen(key),
		vlen = strlen(value);

	int size = klen+vlen+6;

	if(comma) {
		size++;
	}
	rtn = calloc(sizeof(char), size+1);
	//strcat(rtn, len);
	strcat(rtn, "\"");
	strcat(rtn, key);
	strcat(rtn, "\"");
	strcat(rtn, ":");
	strcat(rtn, "\"");
	strcat(rtn, value);
	strcat(rtn, "\"");
	if(comma){
		strcat(rtn, ",");
	}
	rtn[size] = '\0';
	return rtn;
}

char *jsm_jtok( char *json, int start, int end )
{
	char *rtn = NULL;
	int i=0, k=0, 		/* index for the result array */
		size=end-start; 	/* size of the string */

	if(json) {
		rtn = (char*)calloc(size+1, sizeof(char*));
		rtn[size] = '\0';
		for(i=start; i<end; i++, k++) {
			rtn[k] = json[i];
		}
	}

	return rtn;
}

char *jsm_jobj(  int indent,  int size, char *array[size] )
{
	int objectsize = 0;
	char *obj= NULL;
	//g_print("value size: %s\n", array[0]);
	for(int i=0; i<size; i++) {
		objectsize += strlen(array[i])+indent+2;
	}

	obj = calloc(sizeof(char), objectsize+1);
	strcat(obj, "{\n");
	for(int i=0; i<size; i++) {
		for(int k=0; k<indent; k++) {
			strcat(obj, " ");
		}
		strcat(obj,array[i]);
		strcat(obj, "\n");
	}
	strcat(obj, "}\n");

	return obj;
}

char *jsm_jval( char *json, char *key, jsmntype_t type )
{
	char *rtn = NULL;
	/* Initialize parser and read json tokens */
	if(json) {
		jsmn_parser parser;
		jsmntok_t tokens[256];
		jsmn_init(&parser);
		jsmn_parse(&parser, json, strlen(json), tokens, 256);

		for(int i=0; i<tokens->size; i++) { /* Find tokens that match both key and type */
			if(tokens[i].type == type ) {
				char *tkn = jsm_jtok(json, tokens[i].start, tokens[i].end);
				if(tkn != NULL && strcmp(tkn, key) == 0) {
					rtn = jsm_jtok(json, tokens[i+1].start, tokens[i+1].end);
				}
				free(tkn);
			}
		}
	}

	return rtn;
}

char *jsm_fread( const char *file )
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
			} else { printf("JSM [ERROR] : Unable to allocate memory.\n"); }
			fclose(src);
		}
	}

	return json;
}

int jsm_fwrite( char *json, const char *file )
{
	int rtn = 1;
	if(json && file) {
		FILE *src = fopen(file, "w");
		if(src) {
			fputs(json, src);
			fclose(src);
		}
	}

	return rtn;
}

void jsm_read_commons( commons_model *model, const char *pref_path )
{
	if(model) {
		char *json = jsm_fread(pref_path);

		free(model->live_a);
		free(model->live_d);

		char *bgCol, *frCol; /* free these */
		/* populate values for model */
		model->cols    = jsm_atoi(json, "gridCols");
		model->rows    = jsm_atoi(json, "gridRows");
		model->interval  = jsm_atoi(json, "tickInterval");
		model->visible = jsm_atoi(json, "gridVisible");

		/* TODO: static modifiers for now */
		model->cell_s = 10.0;
		model->zoom   = 1.0;
		bgCol = jsm_jval(json, "backgroundColor", 3);
		frCol = jsm_jval(json, "cellColor", 3);
		/* parse colors to model  */
		gdk_rgba_parse(&model->bgrn_col, bgCol);
		gdk_rgba_parse(&model->cell_col, frCol);

		/* Free dynamically allocated values */
		int *live_a1 = (int*)calloc(2, sizeof(int));
		int *live_d1 = (int*)calloc(1, sizeof(int));
		live_a1[0] = 3;
		live_a1[1] = 2;
		live_d1[0] = 3;
		model->live_a = live_a1;
		model->live_d = live_d1;

		free(bgCol);
		free(frCol);
		free(json);
		/* Initialize new grid and give random values */
		if(model->interval < 100) {
			g_print("WARNING: update value too small setting to : 100ms.\n");
			model->interval = 100;
		}
	}
}

void jsm_write_commons( commons_model *model, const char *pref_path  )
{
	/*
		Used json keys will be:
		"gridRows"
		"gridCols"
		"tickInterval"
		"gridVisible"
		"backgroundColor"
		"cellColor"
	*/
	if(model) {
		char *rows  = (char*)calloc(10, sizeof(char*));
		char *cols = (char*)calloc(10, sizeof(char*));
		char *t_time = (char*)calloc(10, sizeof(char*));
		char *vis = (char*)calloc(10, sizeof(char*));

		sprintf(rows, "%d",   model->rows);
		sprintf(cols, "%d",   model->cols);
		sprintf(t_time, "%d", model->interval);
		sprintf(vis, "%d",    model->visible);

		gchar *bgrn = gdk_rgba_to_string(&model->bgrn_col);
		gchar *cell = gdk_rgba_to_string(&model->cell_col);

		char *strings[6];
		strings[0] = jsm_keypair("gridRows", rows, 1);
		strings[1] = jsm_keypair("gridCols", cols, 1);
		strings[2] = jsm_keypair("tickInterval", t_time, 1);
		strings[3] = jsm_keypair("gridVisible", vis, 1);
		strings[4] = jsm_keypair("backgroundColor", bgrn, 1);
		strings[5] = jsm_keypair("cellColor", cell, 0);

		free(bgrn);
		free(cell);
		char *json = jsm_jobj(3, 6, strings);

		jsm_fwrite(json, pref_path);
		free(json);
		for(int i=0; i<6; i++) {
			free(strings[i]);
		}
	} else {}
}



int jsm_jint(char *json, char *key)
{
	int rtn = -1;

	char *tmp_str = jsm_jval( json, key, 3 );
	if(tmp_str) {
		rtn = atoi(tmp_str);
		free(tmp_str);
	}

	return rtn;
}


GdkRGBA *jsm_ctoa( char *color )
{
	GdkRGBA *bgCol;
	gdk_rgba_parse(bgCol, color);
	return bgCol;
}

char *jsm_atoc( GdkRGBA *color )
{
	char *bgCol;
	bgCol = gdk_rgba_to_string(color);
	return bgCol;
}

char *jsm_itoa( int value )
{
	char *rtn;
	sprintf(rtn, "%d", value);
	//g_print("x_size = %s, i=%d\n", rtn, value);
	return rtn;
}

int jsm_atoi( const char *json, const char* key )
{
	int rtn = -1;
	char *str = jsm_jval( json, key, 3 );
	if(rtn) {
		rtn = atoi(str);
		free(str);
	}
	return rtn;
}
