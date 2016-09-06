#include "log.h"

char *log_timestamp()
{
    time_t rawtime;
    struct tm * timeinfo;
    static char result[26];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf(result, "%d-%d-%d %.2d:%.2d:%.2d",
        1900 + timeinfo->tm_year, timeinfo->tm_mon+1,
        timeinfo->tm_mday, timeinfo->tm_hour,
        timeinfo->tm_min, timeinfo->tm_sec
    );

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
