#ifndef __JSM_H_
#define __JSM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn/jsmn.h"

typedef enum {
	/* Success */
	JSM_OK = 1,
	/* File read failed */
	JSM_ERROR_FREAD = -1,
	/* Memory allocation failed */
	JSM_ERROR_ALLOC = -2
	//JSM_ERROR_PART = -3
} jsmrtn_t;

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
