#include "json.h"

static void create_main_object( JsonObject *object );

/** @brief Pull single token from json string.
 *
 *  Pulls token from json string based on given start and end values. Only for
 *  Getting tokens, doesn't check contents so validity is up to user. Returned
 *  value must be freed using standard free().
 *
 *  @json   Contains full json string.
 *  @start  Index of the first character to be added.
 *  @end    Index of the last character to be added.
 *  @return newly allocated token.
 */
static JsonObject **ob_array_realloc1( JsonObject **array, int oldSize, int newSize );

/** @brief Pull single token from json string.
 *
 *  Pulls token from json string based on given start and end values. Only for
 *  Getting tokens, doesn't check contents so validity is up to user. Returned
 *  value must be freed using standard free().
 *
 *  @json   Contains full json string.
 *  @start  Index of the first character to be added.
 *  @end    Index of the last character to be added.
 *  @return newly allocated token.
 */
static JsonKeypair **array_realloc1( JsonKeypair **array, int oldSize, int newSize );

/** @brief Pull single token from json string.
 *
 *  Pulls token from json string based on given start and end values. Only for
 *  Getting tokens, doesn't check contents so validity is up to user. Returned
 *  value must be freed using standard free().
 *
 *  @json   Contains full json string.
 *  @start  Index of the first character to be added.
 *  @end    Index of the last character to be added.
 *  @return newly allocated token.
 */
static char *json_tok( const char *json, int start, int end );

JsonObject *json_parse( const char *json )
{
    JsonObject *rtn = (JsonObject*)calloc(1, sizeof(JsonObject));
    rtn->base.type = OBJECT;
    /*
        NOTE: It is totally fine to give NULL pointer as json. In that case
        Empty json object is initialized. Objects and values may be added later.
        Therefore this function will always return pointer to allocated object,
        and never NULL pointer.
    */
    rtn->object_id = NULL; /* Object may or may not have ID, so we intialize it to NULL */
    /*
        Initalize object arrays to NULL, so we can later alloc them as needed.
     */
    rtn->objects = NULL;
    rtn->values  = NULL;
    /* All arrays have size 0 at this point. Sizes are grown dynamically as needed. */
    rtn->objects_size = 0;
    rtn->values_size  = 0;

    if(json) {
        rtn->main_object = (char*)calloc(strlen(json)+1, sizeof(char));
        strncpy(rtn->main_object, json, strlen(json));  /* Copy parameter json to object. */
        /* Initialize parser and its properties. */
        jsmn_parser parser;
        jsmntok_t tokens[256];
        jsmn_init(&parser);
        /*
            NOTE: although jsmn_parse returns error, it also returns count if
            parse was successfull. We use this count to determine how many
            tokens were found as a whole.
         */
        jsmnerr_t tkn_count = jsmn_parse(&parser, json, strlen(json), tokens, 256);
        /* flag counters */
        int val = 0;
        int oval = 0;
        /* Start looping tokens. */
        for(int i=0; i<tkn_count ; i++) {
            if(tokens[i].type == JSMN_STRING) { /* Token at i was string. */
                /* Save string for later use, deleted at the end of each loop.*/
                char *str_save = json_tok(json, tokens[i].start, tokens[i].end);
                /*
                    String token may have object, string or other value following it.
                    Well add it to objects or strings depending on the result.
                 */
                if(tokens[i+1].type == JSMN_OBJECT) {
                    rtn->objects = ob_array_realloc1( rtn->objects, rtn->objects_size, rtn->objects_size+1);
                    char *ob = json_tok(json, tokens[i+1].start, tokens[i+1].end);
                    rtn->objects[oval] = json_parse(ob);
                    free(ob);
                    rtn->objects[oval]->object_id = (char*)calloc(strlen(str_save)+1, sizeof(char)); //json_tok(json, tokens[i-1].start, tokens[i-1].end);
                    strncpy(rtn->objects[oval]->object_id, str_save, strlen(str_save));
                    int addToInt = 1;
                    addToInt+=rtn->objects[oval]->values_size*2;
                    rtn->objects_size++;
                    oval++;
                    i+=addToInt;
                }
                else {  /* Token was string or other primitive. */
                    rtn->values = array_realloc1(rtn->values, rtn->values_size, rtn->values_size+1);
                    char *tmpkey = json_tok(json, tokens[i].start, tokens[i].end);
                    char *tmpval = json_tok(json, tokens[i+1].start, tokens[i+1].end);
                    rtn->values[val] = json_keypair_create(tmpkey, tmpval);
                    rtn->values_size++;
                    free(tmpkey);
                    free(tmpval);
                    val++;
                    i++;
                }
                free(str_save);
            }
        }
    }
    else {
        rtn->main_object = (char*)calloc(3, sizeof(char));
        strncpy(rtn->main_object, "{}", 3);
    }

    return rtn;
}

void json_free( JsonObject *json )
{
    for(int i=0; i<json->objects_size; i++) {
        json_free( json->objects[i] );
    }

    free(json->objects);
    json->objects = NULL;

    for(int i=0; i<json->values_size; i++) {
        json_keypair_free(json->values[i]);
    }

    free(json->values);
    json->values = NULL;

    if(json->main_object) {
        free(json->main_object);
        json->main_object=NULL;
    }
    if(json->object_id) {
        free(json->object_id);
        json->object_id=NULL;
    }

    free(json);
    json = NULL;
}

void json_add( JsonObject *json, JsonToken *to_add )
{
    if(json && to_add) {
        switch (to_add->type) {
            case KEYPAIR:
                json_add_value (json, (JsonKeypair*)to_add);
                break;
            case OBJECT:
                json_add_object(json, (JsonObject*)to_add);
                break;
            default:
                break;
        }
    }
}

JsonToken *json_find( JsonObject* json, const char *key)
{
    JsonToken *rtn = NULL; /* Pointer to value-keypair in json object struct (if found). */
    if(json && key) { /* Cannot search is one of these is NULL. */
        for(int i=0; i<json->values_size; i++) {
            /* Loop until match is found from values. If never found, rtn remains NULL */
            if(strcmp(json->values[i]->key, key) == 0) {
                /*
                    Return pointer to a value in structure, NOT a copy pointer.
                    Therefore if returned pointer is freed, it is also lost from
                    "json" structure. Because of this user of this function must be
                    careful not to call free other than json_free to full object,
                    Keypairs are always deleted internally.
                */
                rtn = (JsonToken*)json->values[i];
                /*
                    NOTE: json should only contain one value with certain key,
                    so we break here. Because of this FIRST value with matching
                    key is returned and others are ignored. No checks for multiple
                    values with same key, are added for now.
                */
                break;
            }
        }
        if(!rtn) {
            for(int i=0; i<json->objects_size; i++) {
                if(strcmp(json->objects[i]->object_id, key) == 0) {
                    rtn = (JsonToken*)json->objects[i];
                    break;
                }
            }
        }
    }

    return rtn;
}

JsonKeypair *json_keypair_create( const char *key, const char *value )
{
    JsonKeypair *rtn = NULL;
    /*
        Initialize all values to NULL. If NULL values are provided, return will
        also contain NULL. TODO: define proper behaviour in this case. Should
        json key-value pair contain NULL values, or should we simply return
        NULL pointer if unintialized values are provided?
    */
    if( key && value ) { /* If key was given, initialize it, otherwise use NULL */
        rtn = (JsonKeypair*)calloc(1, sizeof(JsonKeypair));
        rtn->base.type = 0;
        rtn->key = (char*)calloc(strlen(key)+1, sizeof(char));
        strncpy(rtn->key, key, strlen(key));
        rtn->value = (char*)calloc(strlen(value)+1, sizeof(char));
        strncpy(rtn->value, value, strlen(value));
    }

    return rtn;
}

void json_keypair_free(JsonKeypair *keypair)
{
    if(keypair) {
        /*
            It is impossible to know if user of this struct has changed some
            values to NULL. Therefore we check for NULL pointers before attempting
            to free them.
        */
        if(keypair->key) {
            free(keypair->key);
            keypair->key = NULL; /* Remove dangling pointer. */
        }
        if(keypair->value) {
            free(keypair->value);
            keypair->value = NULL; /* Remove dangling pointer. */
        }
        free(keypair);  /* Free struct pointer and set it to NULL */
        keypair = NULL;
    } else { }

}

void json_add_value( JsonObject *json, JsonKeypair *to_add )
{
    if(json && to_add) { /* Only change data if both pointers are provided. */
        /*
            Resize value array in object to +1 space. NOTICE that old pointer
            is freed in array_realloc before creating new one.
        */
        json->values = array_realloc1( json->values, json->values_size, json->values_size+1);
        /*
            Set last value in object to given pointer.
            This pointer is freed when json_free is called.
        */
        json->values[json->values_size] = to_add;
        json->values_size++; /* Update size variable. */
        create_main_object(json); /* Update main_object string. */
    } else { }
}

void json_rem_value( JsonObject *json, JsonKeypair *to_rem )
{
    if(json && to_rem) {
        /* TODO: Not yet implemented. */
    } else { }
}

void json_add_object( JsonObject *json, JsonObject *to_add )
{
    if(json && to_add) { /* Only change data if both pointers are provided. */
        /*
            Resize value array in object to +1 space. NOTICE that old pointer
            is freed in array_realloc before creating new one.
        */
        json->objects = ob_array_realloc1( json->objects, json->objects_size, json->objects_size+1);
        /*
            Set last value in object to given pointer.
            This pointer is freed when json_free is called.
        */
        json->objects[json->objects_size] = to_add;
        json->objects_size++; /* Update size variable. */
        create_main_object(json); /* Update main_object string. */
    } else { }
}

void json_rem_object( JsonObject *json, const char *to_rem )
{
    if(json && to_rem) {
        /* TODO: Not yet implemented. */
    } else { }
}

char *array_realloc( char *array, int oldSize, int newSize )
{
    char *rtn = (char*)calloc(newSize+1, sizeof(char));

    if(array) {
        strncpy(rtn, array, strlen(array));
        free(array);
        array = NULL;
    }

    return rtn;

}

static void create_main_object( JsonObject *object )
{
    char *tmp = (char*)calloc(4, sizeof(char));
    strncpy(tmp, "{\n", 2);

    for(int i=0; i<object->values_size; i++) {
        int length = strlen(object->values[i]->key)+strlen(object->values[i]->value)+7;
        char *line = (char*)calloc(length+1, sizeof(char));
        strncpy(line, "\"", 1);
        strncat(line, object->values[i]->key, strlen(object->values[i]->key));
        strncat(line, "\"", 1);
        strncat(line, ":", 1);
        strncat(line, "\"", 1);
        strncat(line, object->values[i]->value, strlen(object->values[i]->value));
        strncat(line, "\"", 1);
        if(i+1==object->values_size && object->objects_size == 0) {
            strncat(line, "\n", 2);
        }else {
            strncat(line, ",\n", 2);
        }
        printf("line: %s", line );

        tmp = array_realloc( tmp, strlen(tmp), strlen(tmp)+length );
        strncat(tmp, line, strlen(line));

        free(line);
        line =NULL;
    }
    for(int i=0; i<object->objects_size; i++) {
        int length = strlen(object->objects[i]->main_object)+3;
        char *line = (char*)calloc(length+1, sizeof(char));
        strncpy(line, object->objects[i]->main_object, strlen(object->objects[i]->main_object));
        if(i+1==object->objects_size ) {
            strncat(line, "\n", 2);
        }else {
            strncat(line, ",\n", 2);
        }
        printf("line: %s", line );

        tmp = array_realloc( tmp, strlen(tmp), strlen(tmp)+length );
        strncat(tmp, line, strlen(line));

        free(line);
        line =NULL;
    }

    if(object->main_object) {
        free(object->main_object);
        object->main_object = NULL;
    }
    tmp = array_realloc( tmp, strlen(tmp), strlen(tmp)+1);
    strncat(tmp, "}", 1);

    object->main_object = (char*)calloc(strlen(tmp)+1, sizeof(char));
    strncpy(object->main_object, tmp, strlen(tmp));

    free(tmp);
    tmp = NULL;
}

JsonKeypair *json_keypair_copy( JsonKeypair *keypair )
{
    JsonKeypair *rtn = (JsonKeypair*)calloc(1, sizeof(JsonKeypair));

    rtn->key   = (char*)calloc(strlen(keypair->key)+1, sizeof(char));
    rtn->value = (char*)calloc(strlen(keypair->value)+1, sizeof(char));

    strncpy(rtn->key, keypair->key, strlen(keypair->key));
    strncpy(rtn->value, keypair->value, strlen(keypair->value));

    return rtn;
}

JsonKeypair **array_realloc1( JsonKeypair **array, int oldSize, int newSize )
{
    JsonKeypair **rtn = (JsonKeypair**)calloc(newSize+1, sizeof(JsonKeypair*));
    if(array) {
        for(int k=0; k<oldSize; k++) {
            //rtn[k] = (JsonKeypair*)calloc(1, sizeof(JsonKeypair));
            rtn[k] = json_keypair_copy( array[k] );
            //printf("%s\n", );
        }
        for(int k=0; k<oldSize; k++) {
             json_keypair_free(array[k]);
            //array[k] = NULL;
        }
        free(array);
        array = NULL;
    }

    return rtn;

}


JsonObject *JsonObjectject_copy( JsonObject *object )
{
    JsonObject *rtn = (JsonObject*)calloc(1, sizeof(JsonObject));

    rtn->main_object = (char*)calloc(strlen(object->main_object)+1, sizeof(char));
    strncpy(rtn->main_object, object->main_object, strlen(object->main_object));
    if(object->object_id != NULL) {
        rtn->object_id = (char*)calloc(strlen(object->object_id)+1, sizeof(char));
        strncpy(rtn->object_id, object->object_id, strlen(object->object_id));
    }else {rtn->object_id = NULL;}

    rtn->values_size  = object->values_size;
    rtn->objects_size = object->objects_size;

    rtn->values = array_realloc1( rtn->values, 0, object->values_size+1);
    rtn->objects = ob_array_realloc1( rtn->objects, 0, rtn->objects_size+1);

    rtn->values_size  = object->values_size;
    rtn->objects_size = object->objects_size;

    return rtn;
}

JsonObject **ob_array_realloc1( JsonObject **array, int oldSize, int newSize )
{
    JsonObject **rtn = (JsonObject**)calloc(newSize+1, sizeof(JsonObject*));
    if(array) {
        for(int k=0; k<oldSize; k++) {
        //    rtn[k] = (JsonObject*)calloc(1, sizeof(JsonObject));
            rtn[k] = JsonObjectject_copy( array[k]);

        }
        for(int k=0; k<oldSize; k++) {
            json_free(array[k]);
            array[k] = NULL;
        }
        free(array);
        array = NULL;
    }

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
