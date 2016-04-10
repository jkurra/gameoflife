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

/* Json functions */
/*
 *
 */
char *jsm_json_tok( char *json, int start, int end );

/*
 *
 */
char *jsm_json_val( char *json, char *key, jsmntype_t type );

/*
 *
 */
char *jsm_json_add( char *json, char *key, char *value );

/*
 * Read content of a file to a string.
 */
char *jsm_read( const char *file );

/*
 * Write content of a json string into a file.
 */
jsmrtn_t jsm_write( char *json, const char *file );

#endif /* __JSM_H_ */
