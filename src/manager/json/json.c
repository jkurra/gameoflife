#include "json.h"

void json_add_value( json_ob *json, const char *keypair )
{
    char **tmp_val = (char**)calloc(json->values_size+1, sizeof(char*));
    for(int i=0; i<json->values_size; i++) {
        tmp_val[i] = (char*)calloc(strlen(json->values[i])+1, sizeof(char));
        strncpy(tmp_val[i], json->values[i], strlen(json->values[i]));
    }

    for(int i=0; i<json->values_size; i++) {
        free(json->values[i]);
        json->values[i] = NULL;
    }
    free(json->values);
    json->values = NULL;

    json->values = (char**)calloc(json->values_size+2, sizeof(char*));

    for(int i=0; i<json->values_size; i++) {
    //    printf("i:%d\n", i);
        json->values[i] = (char*)calloc(strlen(tmp_val[i])+1, sizeof(char));
        strncpy(json->values[i], tmp_val[i], strlen(tmp_val[i])+1);
    }

    json->values[json->values_size] = (char*)calloc(strlen(keypair)+1, sizeof(char));
    strncpy(json->values[json->values_size], keypair, strlen(keypair));

    for(int i=0; i<json->values_size+1; i++) {
        free(tmp_val[i]);
        tmp_val[i] = NULL;
    }
    free(tmp_val);
    tmp_val = NULL;
    json->values_size += 1;
}

char **array_realloc( char **array, int oldSize, int newSize )
{
    char **rtn = (char**)calloc(newSize, sizeof(char*));
    if(array) {
        for(int k=0; k<oldSize; k++) {
            rtn[k] = (char*)calloc(strlen(array[k])+1, sizeof(char));
            strncpy(rtn[k], array[k], strlen(array[k]));
        }
        for(int k=0; k<oldSize; k++) {
            free(array[k]);
            array[k] = NULL;
        }
        free(array);
        array = NULL;
    }



    return rtn;

}

char *json_to_string(json_ob *jsonObject)
{
    char *rtn = (char*)calloc(3, sizeof(char));
    int full_len = 2;
    strncpy(rtn, "{\n", 2);

    for(int i=0; i<jsonObject->values_size; i++) {
        char *tmp = NULL;
        if(rtn) {
            int ln = strlen(rtn);
            tmp = (char*)calloc(ln+1, sizeof(char));
            strncpy(tmp, rtn, ln);
            free(rtn);
            rtn = NULL;
        }

        int length = strlen(jsonObject->values[i]);
        full_len += length+2+3;
        rtn = (char*)calloc(full_len+1, sizeof(char));
        if(tmp) {
            strncpy(rtn, tmp, strlen(tmp));
        }
        free(tmp);
        tmp =NULL;
        //strncpy(rtn, jsonObject->values[i], full_len);
        strcat(rtn, "   ");
        strcat(rtn, jsonObject->values[i]);
        if(i<jsonObject->values_size-1) {
            strcat(rtn, ",\n");
        }else {
            strcat(rtn, "\n");
        }
    }

    strcat(rtn, "}");
    return rtn;
}

char *json_get( json_ob *object, const char *key )
{
    //g_print("found key: %s ", key);
    char *rtn = NULL;
    for(int i=0; i<object->values_size; i++) {
        g_print("Compare: %s:%s\n ", key, object->values[i]);
        if(strcmp(object->values[i], key) == 0) {
            //g_print("found key", object->values[i]);
            rtn = (char*)calloc(strlen(object->values[i])+1, sizeof(char));
            strncpy(object->values[i], rtn, strlen(object->values[i]));
        }
    }
    return rtn;
}

json_ob *json_create( const char *json )
{
    json_ob *rtn = (json_ob*)calloc(1, sizeof(json_ob));

    rtn->objects = NULL;
    rtn->values  = NULL;

    rtn->objects_size = 0;
    rtn->values_size  = 0;

    if(json) {
            /* Parse given json string. */
            jsmn_parser parser;
            jsmntok_t tokens[256];
            jsmn_init(&parser);
            jsmn_parse(&parser, json, strlen(json), tokens, 256);

        /* There must be even number of tokens, or some values are missing. */
        if (tokens->size % 2 == 0) {
            for(int i=0; i<tokens->size; i++) {
                if(tokens[i].type == JSMN_OBJECT && i>0) {
                    char *tkn1 = json_tok(json, tokens[i].start, tokens[i].end);
                    //printf("object %s\n", tkn1);
                    rtn->objects = (char**)calloc(rtn->objects_size+2, sizeof(char*));
                    rtn->objects[rtn->objects_size+1] = (char*)calloc(strlen(tkn1)+1, sizeof(char));

                    strncpy(rtn->objects[rtn->objects_size+1], tkn1, strlen(tkn1));

                    rtn->objects_size++;
                    //printf("token %s, %d\n", tkn1, rtn->objects_size);
                    free(tkn1);
                }
                if(tokens[i].type == JSMN_STRING) {

                    char *tkn1 = json_tok(json, tokens[i].start, tokens[i].end);
                    char *tkn2 = json_tok(json, tokens[i+1].start, tokens[i+1].end);
                    char *pair = NULL;

                    pair = json_keypair( tkn1, tkn2, 0 );

                    if(rtn->values_size > 0) {
                        rtn->values = array_realloc(rtn->values, rtn->values_size, rtn->values_size+1);
                        rtn->values[rtn->values_size] = (char*)calloc(strlen(pair)+1, sizeof(char));
                        strncpy(rtn->values[rtn->values_size], pair, strlen(pair));

                    } else {
                        rtn->values = (char**)calloc(rtn->values_size+1, sizeof(char*));
                        rtn->values[rtn->values_size] = (char*)calloc(strlen(pair)+1, sizeof(char));
                        strncpy(rtn->values[rtn->values_size], pair, strlen(pair));
                    }
                    i++;
                    rtn->values_size++;
                    free(tkn1);
                    free(tkn2);
                    free(pair);
                }

            }
        }
    }
    return rtn;
}

void json_free( json_ob *json )
{
    for(int i=0; i<json->objects_size; i++) {
        free(json->objects[i]);
        json->objects[i] = NULL;
    }

    free(json->objects);
    json->objects = NULL;

    for(int i=0; i<json->values_size; i++) {
        free(json->values[i]);
        json->values[i] = NULL;
    }

    free(json->values);
    json->values = NULL;

    free(json);
    json = NULL;

}


char *json_keypair( char *key, char *value, int comma )
{
    char *rtn = NULL;

	int klen = strlen(key),
		vlen = strlen(value);

	int size = klen+vlen+6;

	/*if(comma) {
		size++;
	}*/
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
		//strcat(rtn, ",");
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
