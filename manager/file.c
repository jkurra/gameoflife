#include "file.h"

int file_count( const char *d_path, int mode )
{
    int count = 0;


    switch (mode) {
        case 1: /* count directories and files */

            break;
        case 2: /* Count files */ {
            DIR *dir;
            if((dir = opendir(d_path)) != NULL) {
                struct dirent *ent;
                while ((ent = readdir(dir)) != NULL) {
                    if (ent->d_type == DT_REG) {
                        count++;
                    }
                }
                closedir (dir);
            }
            break;}
        case 3: /* Count directories */
            break;
        default:
            break;
    }

    return count;
}

void file_write( char *str, const char *file )
{
	if(str && file) {
		FILE *src = fopen(file, "w");
		if(src) {
			fputs(str, src);
			fclose(src);
		}
	}
}

char *file_read( const char *file )
{
    char *json = NULL;
	if(file) {
		FILE *src = fopen(file, "r");
		if(src) {
			printf("JSM [READ] : File opened : %s\n", file);
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
