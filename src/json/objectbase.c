#include "objectbase.h"
#include "stdlib.h"

ObjectBase *ObjectBase_new()
{
    ObjectBase *rtn;

    rtn = (ObjectBase*)calloc(1, sizeof(ObjectBase));

    rtn->values = NULL;
    rtn->values_size = 0;

    return rtn;
}

char *json_tok( const char *json, int start, int end )
{
	char *rtn = NULL;
	int i=0, k=0, 		/* index for the result array */
		size=end-start; 	/* size of the string */

	if(json) {
		rtn = (char*)calloc(size+3, sizeof(char));

        if(rtn) {
      		rtn[size] = '\0';
      		for(i=start; i<end; i++, k++) {
                  //strncpy(dest, &src[5], i);
      			rtn[k] = json[i];
      		}
        }
	}

	return rtn;
}

ObjectBase *ObjectBase_create( const char *objectString )
{
    ObjectBase *rtn = ObjectBase_new();

    jsmn_parser parser;
    jsmn_init(&parser);

    jsmntok_t tokens[256];
    int ts = jsmn_parse(&parser, objectString, strlen(objectString), tokens, 256);

    for(int i=0; i<ts; i++) {
        if(tokens[i].type == JSMN_STRING) {

            if(tokens[i+1].type == JSMN_OBJECT) {
                char *token = json_tok(objectString, tokens[i].start, tokens[i].end);
            //    printf("[%d][Object] size:%d { %s:%s }\n",i, tokens[i+1].size, token, json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
                char *key = json_tok(objectString, tokens[i].start, tokens[i].end);
                char *val = json_tok(objectString, tokens[i+1].start, tokens[i+1].end);
                JsonValue *value = JsonValue_new_object(key, val);
                free(token);

                free(key);
                free(val);
                //printf("[object] : %s:%s\n", val->key, val->obj);
                ObjectBase_add(rtn, value);
                i+=tokens[i+1].size*2;
                i++;
            //    printf("i increased to : %d\n", i);
        } else if(tokens[i+1].type == JSMN_PRIMITIVE) {
                char *nmb = json_tok(objectString, tokens[i+1].start, tokens[i+1].end);
                int asint = atoi(nmb);
                free(nmb);
                printf("number %d\n", asint);
                char *key = json_tok(objectString, tokens[i].start, tokens[i].end);
                JsonValue *val = JsonValue_new_number(key, asint);
                free(key);
                ObjectBase_add(rtn, val);
                i++;
            } else {
                //printf("[%d][String] { %s:%s }\n",i, json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
                char *key = json_tok(objectString, tokens[i].start, tokens[i].end);
                char *val = json_tok(objectString, tokens[i+1].start, tokens[i+1].end);
                JsonValue *value = JsonValue_new_string(key, val);

                free(key);
                free(val);
                //printf("[string] : %s:%s\n", val->key, val->string);
                ObjectBase_add(rtn, value);
                i++;
            }
        }
        else if(tokens[i+1].type == JSMN_UNDEFINED) {
            //printf("[%d][Undefined] { %s:%s }\n",i, json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
            //JsonValue *val = JsonValue_new_object(json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
        //    ObjectBase_add(rtn, val);
            i++;
        }
        else if(tokens[i+1].type == JSMN_ARRAY) {
            //printf("[%d][Array] { %s:%s }\n",i, json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
            //JsonValue *val = JsonValue_new_object(json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
        //    ObjectBase_add(rtn, val);
            i++;
        }
        else if(tokens[i+1].type == JSMN_PRIMITIVE) {
            //printf("[%d][Primitive] { %s:%s }\n",i, json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
            //JsonValue *val = JsonValue_new_object(json_tok(objectString, tokens[i].start, tokens[i].end), json_tok(objectString, tokens[i+1].start, tokens[i+1].end));
        //    ObjectBase_add(rtn, val);
            i++;
        }
    }

    return rtn;
}

void ObjectBase_free( ObjectBase *baseObject )
{

    for(int i=0; i<baseObject->values_size; i++) {
        JsonValue_free(baseObject->values[i]);
    }

    free(baseObject->values);
    baseObject->values = NULL;

    free(baseObject);
    baseObject = NULL;
}

void ObjectBase_add( ObjectBase *baseObject, JsonValue *value )
{
    if(baseObject != NULL && value != NULL) {
        if(baseObject->values == NULL) {
            baseObject->values = (JsonValue**)calloc(1, sizeof(JsonValue*));
        }
        else {
            baseObject->values = (JsonValue**)realloc(baseObject->values, (baseObject->values_size+1)*sizeof(JsonValue*));
        }

        baseObject->values[baseObject->values_size] = value;
        baseObject->values_size += 1;
    }
}

JsonValue *ObjectBase_get( ObjectBase *baseObject, const char *key )
{
    JsonValue *rtn = NULL;

    for(int i=0; i<baseObject->values_size; i++) {
        switch (baseObject->values[i]->type) {
            case OBJECT: {
                ObjectBase *base = ObjectBase_create(baseObject->values[i]->obj);
                JsonValue * tmp = ObjectBase_get(base, key);

                if(tmp != NULL ) {
                    rtn = JsonValue_copy(tmp);
                }
                ObjectBase_free(base);
                break;
            }
            default:{
                char *value = JsonValue_key(baseObject->values[i]);
                if(value != NULL) {
                    if(strcmp(value, key) == 0) {
                        rtn = baseObject->values[i];
                    }
                }
                break;
            }
        }
    }

    return rtn;
}

char *ObjectBase_to_string( ObjectBase *baseObject )
{
    char *rtn = NULL;

    rtn = (char*)calloc(3, sizeof(char));
    strncpy(rtn, "{\n", 3);

    for(int i=0; i<baseObject->values_size; i++) {

        char *value = NULL;

        char *tmp = JsonValue_to_string(baseObject->values[i]);
        value = (char*)calloc(4+strlen(tmp), sizeof(char));
        strncpy(value, "   ", 4);
        strncat(value, tmp, strlen(tmp)+4);

        free(tmp);
        tmp = NULL;

        if(value != NULL) {
            int len = strlen(value)+strlen(rtn);

            rtn = (char*)realloc(rtn, (len+4)*sizeof(char));
            strncat(rtn, value, strlen(value));
            if(i+1 < baseObject->values_size) {
                strncat(rtn, ",\n", 3);
            }
        }

        free(value);
        value = NULL;
    }

    if(rtn != NULL) {
        strncat(rtn, "\n}\n", 4);
    }

    return rtn;
}
