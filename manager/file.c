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
