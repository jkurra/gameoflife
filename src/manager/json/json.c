#include "json.h"

char *json_keypair( char *key, char *value, int comma )
{
	char *rtn = NULL;

	int klen = strlen(key),
		vlen = strlen(value);

	int size = klen+vlen+6;

	if(comma) {
		size++;
	}
	rtn = (char*)calloc(sizeof(char), size+1);
	/* Construct key-value pair */
	strcat(rtn, "\"");
	strcat(rtn, key);
	strcat(rtn, "\"");
	strcat(rtn, ":");
	strcat(rtn, "\"");
	strcat(rtn, value);
	strcat(rtn, "\"");
	/* If requested, add comma at the end of the string. */
	if(comma){
		strcat(rtn, ",");
	}
	rtn[size] = '\0';
	return rtn;
}

char *json_tok( const char *json, int start, int end )
{
	char *rtn = NULL;
	int i=0, k=0, 		/* index for the result array */
		size=end-start; 	/* size of the string */

	if(json) {
		rtn = (char*)calloc(size+2, sizeof(char));
		rtn[size] = '\0';
		for(i=start; i<end; i++, k++) {
			rtn[k] = json[i];
		}
	}

	return rtn;
}

char *json_obj(  int indent,  int size, char *array[size] )
{
	int objectsize = 0;
	char *obj = NULL;
	//g_print("value size: %s\n", array[0]);
	for(int i=0; i<size; i++) {
		objectsize += strlen(array[i])+indent+2;
	}

	obj = (char*)calloc(sizeof(char), objectsize+1);
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

char *json_val( const char *json, char *key, jsmntype_t type )
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
				char *tkn = json_tok(json, tokens[i].start, tokens[i].end);
				if(tkn != NULL && strcmp(tkn, key) == 0) {
					rtn = json_tok(json, tokens[i+1].start, tokens[i+1].end);
				}
				free(tkn);
			}
		}
	}
	//printf("return value %s\n", rtn);
	return rtn;
}

int json_jint(char *json, char *key)
{
	int rtn = -1;

	char *tmp_str = json_val( json, key, 3 );
	if(tmp_str) {
		rtn = atoi(tmp_str);
		free(tmp_str);
	}

	return rtn;
}

int json_atoi( const char *json, char* key )
{
	int rtn = -1;
	char *str = json_val( json, key, 3 );
	if(rtn) {
		rtn = atoi(str);
		free(str);
	}
	return rtn;
}
