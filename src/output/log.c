#include "log.h"

char *log_timestamp()
{
    static char result[26];
    /*
     * Fetch current time and date info using functions from time manipulation
     * functions.
     */
    time_t rtime;
    struct tm* tinfo;
    time(&rtime); /* Get current time. */
    /* Convert time into struct containing both date and time */
    tinfo = localtime(&rtime);
    /*  Format and write time and date into result string. */
    sprintf( result, "%d-%d-%d %.2d:%.2d:%.2d",
             1900 + tinfo->tm_year, tinfo->tm_mon+1,
             tinfo->tm_mday, tinfo->tm_hour,
             tinfo->tm_min, tinfo->tm_sec );

    return result;
}

char *log_message(const char *key, const char* message)
{
    char *result = (char*)calloc(sizeof(char), 26 + strlen(key)+strlen(message)+6);
    strncpy(result, "[", 2);
    strcat(result, log_timestamp());
    strcat(result, "]");
    strcat(result, "[");
    strcat(result, key);
    strcat(result, "] ");
    strcat(result, message);

    return result;
}
