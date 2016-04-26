#include "jsm.h"

char *jsm_json_tok( char *json, int start, int end )
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

char *jsm_json_val( char *json, char *key, jsmntype_t type )
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
				char *tkn = jsm_json_tok(json, tokens[i].start, tokens[i].end);
				if(tkn != NULL && strcmp(tkn, key) == 0) {
					rtn = jsm_json_tok(json, tokens[i+1].start, tokens[i+1].end);
				}
				free(tkn);
			}
		}
	}

	return rtn;
}

char *jsm_jval( char *key, char *value, int comma )
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

char *jsm_create_object( int size, char *array[size], int indent )
{
	int objectsize = 0;
	char *obj= NULL;
	//g_print("value size: %d\n", size);
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
			} else { printf("JSM [ERROR] : Unable to allocate memory.\n"); }
			fclose(src);
		}
	}

	return json;
}

jsmrtn_t jsm_write( char *json, const char *file )
{
	int rtn = JSM_OK;
	if(json && file) {
		FILE *src = fopen(file, "w");
		if(src) {
			fputs(json, src);
			fclose(src);
		} else { rtn = JSM_ERROR_FREAD; }
	} else { rtn = JSM_NULL; }

	return rtn;
}

int jsm_jint(char *json, char *key)
{
	int rtn = -1;

	char *tmp_str = jsm_json_val( json, key, 3 );
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

char *jsm_itoa( const char *value )
{
	char *rtn;
	return rtn;
}

int jsm_atoi( const char *json, const char* key )
{
	int rtn = -1;
	char *str = jsm_json_val( json, key, 3 );
	//g_print("atoi: %s : %s\n",key, str);
	if(rtn) {
		rtn = atoi(str);
		free(str);
	}
	return rtn;
}
