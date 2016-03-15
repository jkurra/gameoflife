#ifndef __JSM_H_
#define __JSM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../view.h"
#include "jsmn.h"

typedef enum {
	/* Success */
	JSM_OK = 1,
	/* NULL pointer error */
	JSM_NULL = -3,
	/* File read failed */
	JSM_ERROR_FREAD = -1,
	/* Memory allocation failed */
	JSM_ERROR_ALLOC = -2
} jsmrtn_t;

/** @brief get token from json string
 *
 * @param json
 * @param start
 * @param end
 * @return Newly allocated token.
 */
char *jsm_token(const char *json, int start, int end);

/** @brief get value from json string
 *
 * @param json
 * @param key
 * @param type
 * @return Found value as character strin, NULL if not found.
 */
char *jsm_value( const char *json, char *key, jsmntype_t type);


char *jsm_json( const char *json, char *key, char *value );

/*
 * Read content of a file to a string.
 */
char *jsm_read( const char *file );

/*
 * Write content of a json string into a file.
 */
jsmrtn_t jsm_write( char *json, const char *file );
/*
 * Updates cdefault values to file, creates if not exist
 */
jsmrtn_t jsm_default_model( view_model *model );

/*
 * Updates current to a settings file.
 */
jsmrtn_t jsm_update_model( view_model *model );

/*
 * Read content of a file to a string.
 */
jsmrtn_t jsm_read_file( char **json, const char *file );

/*
 * Write content of a json string into a file.
 */
jsmrtn_t jsm_write_file( char *json, const char *file );

/*
 *
 */
jsmrtn_t jsm_val( char *rtn, const char *json, const char *key );

/*
 *
 */
jsmrtn_t jsm_obj( char *result, const char *full_json, int start, int end );

#endif /* __JSM_H_ */
