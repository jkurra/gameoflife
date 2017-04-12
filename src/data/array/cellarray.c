#include "cellarray.h"

CellArray *CellArray_new( int count )
{
    CellArray *arr = (CellArray*)calloc(1, sizeof(CellArray));
    arr->count =count;

    arr->c_array = (Cell**)calloc(count+1, sizeof(Cell*));
    for(int i=0; i<count; i++) {
        arr->c_array[i] = (Cell*)calloc(1, sizeof(Cell));
    //    arr->c_array[i]->state   = 0;
    //    arr->c_array[i]->checked = 0;
    }

    return arr;
}

void CellArray_free(CellArray *array)
{

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

CellArray *CellArray_copy( CellArray *toCopy )
{
    CellArray *arr = CellArray_new( toCopy->count ); //(CellArray*)calloc(arr->count+1, sizeof(CellArray));
    //arr->count =toCopy->count;
    for(int i=0; i<toCopy->count; i++) {
    //    arr->c_array[i] = (Cell*)calloc(1, sizeof(Cell));
        arr->c_array[i] = toCopy->c_array[i]->state   = 0;
        arr->c_array[i] = toCopy->c_array[i]->checked = 0;
    }

    return arr;
}
void CellArray_realloc( CellArray *array, size_t newSize )
{
    for(int i=array->count; i--; ) {
        Cell_free(array->c_array[i]);
    }
    free(array->c_array);
    array->c_array = NULL;

    array->c_array = (Cell**)calloc(newSize, sizeof(Cell*));
}

void CellArray_add( CellArray *array, Cell *cell )
{
    if(array) {
        array->c_array = (Cell**)realloc(array->c_array, (array->count+1)*sizeof(Cell*));
        array->c_array[array->count] = cell;
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

void CellArray_empty( CellArray *array )
{
    for(int i=0; i<array->count; i++) {
        array->c_array[i]->state = 0;
        array->c_array[i]->checked = 0;
    }
}
