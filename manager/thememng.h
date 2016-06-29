#ifndef THEMEMNG_H_INCLUDED
#define THEMEMNG_H_INCLUDED

typedef struct
{
   char *path;
   char *list;
} theme;

theme *theme_new( char *path );

void theme_free( theme *t );

void theme_update( theme *t );

void theme_select( theme *t );

char *theme_list( const char *path );

void thememng_select( const char * name );

void thememng_list( const char *path );

#endif
