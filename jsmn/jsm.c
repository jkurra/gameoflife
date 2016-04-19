#include "jsm.h"

char *jsm_json_tok( char *json, int start, int end )
{
	char *rtn = NULL;
	int i=0, k=0, 		/* index for the result array */
		size=end-start; 	/* size of the string */

	if(json) {
		rtn = (char*)calloc(size+1, sizeof(char*));
		rtn[size] = '\0';
		for(i=start; i<end; i++, k++)
			rtn[k] = json[i];
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

char *jsm_json_add( char *json, char *key, char *value )
{
	char *rtn = NULL;//printf("JSM [JSON] : Add to json.\n");

	int addSize = strlen(key) + strlen(value);
	char *toAdd = NULL;

	if(!json) {
		toAdd = calloc(sizeof(char), addSize+7);
		strcat(toAdd, "{");
	}
	else {
		toAdd = calloc(sizeof(char), addSize+7);
		strcat(toAdd, ",");
	}
	/*  Prepare key-value pair to be added to string. */
	strcat(toAdd, "\"");
	strcat(toAdd, key);
	strcat(toAdd, "\"");
	strcat(toAdd, ":");
	strcat(toAdd, "\"");
	strcat(toAdd, value);
	strcat(toAdd, "\"");

	if(json) {
		/* Initialize parser and read json tokens */
		jsmn_parser parser;
		jsmntok_t tokens[256];
		jsmn_init(&parser);
		jsmn_parse(&parser, json, strlen(json), tokens, 256);

		rtn = calloc(sizeof(char), strlen(json)+strlen(toAdd)+1);
		char *tmp = jsm_json_tok(json, tokens[0].start, tokens[0].end-1);
		strcat(rtn, tmp);
		free(tmp);
	} else {
		rtn = calloc(sizeof(char), addSize+8);
	}

	strcat(rtn, toAdd);
	strcat(rtn, "}");

	free(toAdd);
	free(json);
	//printf("JSM [JSON] : Saved successfully.\n");
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
char *jsm_ctoa()
{

}
void jsm_atoc(GdkRGBA *color, char *asStr )
{

	gdk_rgba_parse(color, asStr);
}

char *jsm_itoa( const char *value )
{
	char *rtn;
	return rtn;
}
/* Exctract integer directly from json string */
int jsm_atoi( const char *json, const char* key )
{
	int rtn = -1;
	char *str = jsm_json_val( json, key, 3 );
	rtn = atoi(str);
	free(str);
	return rtn;
}
