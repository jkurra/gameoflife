#include "cellarray.h"

CellArray *CellArray_new()
{
    CellArray *arr = (CellArray*)calloc(1, sizeof(CellArray));

    arr->count = 0;
    arr->c_array = NULL;

    return arr;
}

void CellArray_free(CellArray *array)
{
    if(array) {
        for(int i=0; i<array->count; i++) {
            Cell_free(array->c_array[i]);
        }
        free(array->c_array);
        array->c_array = NULL;

        array->count = 0;

        free(array);
        array = NULL;
    }
}

CellArray *CellArray_copy( CellArray *toCopy )
{
    CellArray *arr = CellArray_new(); //(CellArray*)calloc(arr->count+1, sizeof(CellArray));

    arr->c_array = (Cell**)calloc(toCopy->count, sizeof(Cell*));
    for(int i=0; i<toCopy->count; i++) {
        arr->c_array[i] = Cell_new(toCopy->c_array[i]->row, toCopy->c_array[i]->col);
        arr->c_array[i]->state = toCopy->c_array[i]->state;
        arr->c_array[i]->checked = toCopy->c_array[i]->checked;
    }
    arr->count= toCopy->count;
    return arr;
}

void CellArray_clear( CellArray *array )
{
    for(int i=0; i<array->count; i++) {
        Cell_free(array->c_array[i]);
    }
    free(array->c_array);
    array->c_array = NULL;
    //array->c_array = (Cell**)calloc(1, sizeof(Cell*));

    array->count = 0;
}

void CellArray_empty( CellArray *array )
{
    for(int i=0; i<array->count; i++) {
        array->c_array[i]->state   = 0;
        array->c_array[i]->checked = 0;
    }
}

void CellArray_set( CellArray *array, int val, int index, int new_state )
{
    switch (val) {
        case STATE:
            array->c_array[index]->state = new_state;
            break;
        case CHECK:
            array->c_array[index]->checked = new_state;
            break;
    }
}
/*
void CellArray_realloc( CellArray *array, size_t newSize )
{
    for(int i=array->count; i--; ) {
        Cell_free(array->c_array[i]);
    }
    free(array->c_array);
    array->c_array = NULL;

    array->c_array = (Cell**)calloc(newSize, sizeof(Cell*));
}*/

void CellArray_add( CellArray *array, Cell *cell )
{
    if(array && cell) {
        array->c_array = (Cell**)realloc(array->c_array, (array->count+1)*sizeof(Cell*));
        array->c_array[array->count] = cell;
        //printf("add cell: %d\n", array->c_array[array->count]->state);
        //array->c_array = addCell1( array->c_array, cell, array->count );
        array->count++;
    }
}

void remElem1( Cell** array, int index, int len )
{
    int i=0;
    for(i=index; i<len-1; i++) {
        Cell_free(array[i]);
        array[i] = NULL;
        array[i] = array[i+1];
    }
}

void CellArray_rem( CellArray *array, Cell *cell ) {

    for(int i=0; i<array->count; i++) {
        //printf("size: %d, %d\n", i, array[i]->x);
        if(array->c_array[i]->row == cell->row && array->c_array[i]->col == cell->col) {
            remElem1(array->c_array, i, array->count);
            array->c_array = realloc(array->c_array, (array->count-1)*sizeof(Cell*));
            array->count--;
            break;
        }
    }
}


Cell *CellArray_get( CellArray *array, int index )
{
    Cell *rtn = NULL;

    if(array && index < array->count && index >= 0) {
        rtn = array->c_array[index];
    }

    return rtn;
}
