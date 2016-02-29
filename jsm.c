#include "jsm.h"

jsmrtn_t jsm_read_file(char **json, const char *file)
{
	int rtn = JSM_OK;
	printf("JSM [OPEN] :%s:...", file);

	FILE *fptr = fopen(file, "r");

	if( fptr != 0) {
		printf("done.\n");
		fseek( fptr , 0L , SEEK_END);
		long flen = ftell( fptr ); /* how many characters in file */
        rewind( fptr );

		char **buffer = calloc( sizeof(char), flen+1 );
		if(!buffer) {
			//fputs("memory alloc fails",stderr);
			printf("JSM [ERROR] : Unable to allocate memory.", file);
			rtn = JSM_ERROR_ALLOC;
		}
		else {
			fread( buffer, flen, 1 , fptr);
		}
    fclose(fptr); /* close filestream */
		(*json) = buffer;
	}
	else {
		printf("failed.\n");
		rtn = JSM_ERROR_FREAD;
	}

	return rtn;
}

jsmrtn_t jsm_write_file(char *json, const char *file)
{
	int i=0, r = JSM_OK;
	printf("trying to open file : %s\n", file);

	FILE *fp = fopen(file, "rw");
	fwrite ( json , sizeof(char), sizeof(json) , fp );
	fclose(fp);

	return r;
}

jsmrtn_t jsm_val(char *rtn, const char *json, const char *key)
{
	printf("JSM [PARSE] : %s : ", key);
		/* Calculate lenght for the full json */
	int i=0, l=strlen(json);

	/* Parse all elements into an array */
	jsmn_parser parser;
	jsmntok_t 	tokens[256];
	jsmn_init(&parser);
	jsmn_parse(&parser, json, l, tokens, 256);
	int size = tokens->size; /* number of found json elements */
	//printf("searching tokens \n");
	for(i=0; i<size; i++) {
		jsmntok_t *tmp_t = &tokens[i];
		int size = tmp_t->end-tmp_t->start;

			if(tmp_t->type == 3) { /* Value is string */
				char nn[size];
				jsm_obj(nn, json, tmp_t->start, tmp_t->end);
				if(strcmp(nn, key) == 0) {
					//printf("found value: %s\n", nn);
					jsmntok_t *tmp1 = &tokens[i+1];// next value is the data
					int tmp1_size = tmp1->end-tmp1->start;
					char nn1[tmp1_size];
					jsm_obj( nn1, json, tmp1->start, tmp1->end );
					jsm_obj( rtn, json, tmp1->start, tmp1->end ); /* add to return data */
					//printf("found value: %s with data: %s\n", nn, nn1);
				}
			}

	}printf("%s done.\n", rtn);
}

jsmrtn_t jsm_obj(char *result, const char *full_json, int start, int end)
{
	int i=0, k=0, 		/* index for the result array */
		s=end-start; 	/* size of the string */
	result[s] = '\0';
	for(i=start; i<end; i++, k++)
		result[k] = full_json[i];
}
