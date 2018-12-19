#include "jsonvalue.h"

#include <stdlib.h>

JsonValue *JsonValue_new_string( const char *key, const char *string )
{
    JsonValue *rtn = (JsonValue*)calloc(1, sizeof(JsonValue));

    rtn->type = STRING;

    rtn->key = (char*)calloc(strlen(key)+1, sizeof(char));
    strncpy(rtn->key, key, strlen(key));

    rtn->obj = NULL;
    rtn->string = (char*)calloc(strlen(string)+1, sizeof(char));
    strncpy(rtn->string, string, strlen(string));

    return rtn;
}

JsonValue *JsonValue_new_object( const char *key, const char *string )
{
    JsonValue *rtn = (JsonValue*)calloc(1, sizeof(JsonValue));

    rtn->type = OBJECT;

    rtn->key = (char*)calloc(strlen(key)+1, sizeof(char));
    strncpy(rtn->key, key, strlen(key));

    rtn->string = NULL;
    rtn->obj = (char*)calloc(strlen(string)+1, sizeof(char));
    strncpy(rtn->obj, string, strlen(string));

    return rtn;
}

JsonValue *JsonValue_new_number( const char *key, int number )
{
    JsonValue *rtn = (JsonValue*)calloc(1, sizeof(JsonValue));

    rtn->type = NUMBER;

    rtn->key = (char*)calloc(strlen(key)+1, sizeof(char));
    strncpy(rtn->key, key, strlen(key));

    rtn->number = number;

    return rtn;
}

JsonValue *JsonValue_new_boolean( const char *key, int boolean )
{
    JsonValue *rtn = (JsonValue*)calloc(1, sizeof(JsonValue));

    rtn->type = OBJECT;
    rtn->key = (char*)calloc(strlen(key), sizeof(char));
    strncpy(rtn->key, key, strlen(key));

    rtn->number = boolean;

    return rtn;
}

void JsonValue_free(JsonValue *value)
{
    free(value->string);
    value->string = NULL;
    free(value->key);
    value->key= NULL;
    free(value->obj);
    value->obj = NULL;

    free(value);
    value = NULL;
}

char *JsonValue_key( JsonValue *value )
{
    char *rtn = NULL;

    if(value != NULL) {
        rtn = value->key;
    }

    return rtn;
}

JsonValue *JsonValue_copy( JsonValue *value )
{
    JsonValue *rtn = NULL;

    if(value != NULL) {
        switch (value->type) {
            case STRING:
                rtn = JsonValue_new_string(value->key, value->string);
                break;
            case NUMBER:
                rtn = JsonValue_new_number(value->key, value->number);
                break;
            case OBJECT:
                rtn = JsonValue_new_object(value->key, value->obj);
                break;
            default:
                break;
        }
    }

    return rtn;
}

char *JsonValue_to_string( JsonValue *value ) {

    char *rtn = NULL;

    if(value != NULL) {
        char *key = JsonValue_key(value);

        if(key != NULL) {
            rtn = (char*)calloc(strlen(key)+4, sizeof(char));

            strncpy(rtn, "\"", 2);
            strncat(rtn, key, strlen(key));
            strncat(rtn, "\"", 2);
            strncat(rtn, ":", 2);

            switch (value->type) {
                case STRING: {
                    rtn = (char*)realloc(rtn, sizeof(char)*(strlen(rtn)+strlen(value->string)+3));
                    strncat(rtn, "\"", 2);
                    strncat(rtn, value->string, strlen(value->string));
                    strncat(rtn, "\"", 2);
                    break;
                }
                case NUMBER: {
                    char str[100];
                    sprintf(str, "%d", value->number);
                    rtn = (char*)realloc(rtn, sizeof(char)*(strlen(rtn)+strlen(str)+1));
                    strncat(rtn, str, strlen(str));
                    break;
                }
                case OBJECT: {
                    rtn = (char*)realloc(rtn, sizeof(char)*(strlen(rtn)+strlen(value->obj)+1));
                    strncat(rtn, value->obj, strlen(value->obj));
                    break;
                }
                default:
                    break;
            }
        }
    }
    return rtn;
}
