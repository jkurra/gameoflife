#include "cellarray.h"

CellArray *CellArray_new()
{
    CellArray *arr = (CellArray*)calloc(1, sizeof(CellArray));

    arr->base.count = 0;
    arr->c_array = NULL;

    return arr;
}

void CellArray_free(CellArray *array)
{
    if(array) {
        for(int i=0; i<array->base.count; i++) {
            Cell_free(array->c_array[i]);
        }
        free(array->c_array);
        array->c_array = NULL;

        array->base.count = 0;

        free(array);
        array = NULL;
    }
}
typedef struct
{
    /** @brief Pointer to array of cells.
     *
     *  Provides access to array, which may be used to store cell pointers.
     *  Array is created, deleted, accessed and dynamically resized
     *  using member functions and only member functions. This is done in
     *  order to ensure safe and efficient memory management.
     */
    CellArray *toCopy;
    CellArray *dest;
    int i;
} CellArraystr;

void *setValues( void *arg )
{
    CellArraystr *toCo = (CellArraystr *)arg;
    toCo->dest->c_array[ toCo->i]->state = toCo->toCopy->c_array[ toCo->i]->state;
    toCo->dest->c_array[ toCo->i]->checked = toCo->toCopy->c_array[ toCo->i]->checked;

}

void *setValues1( void *arg )
{
    CellArraystr *toCo = (CellArraystr*)arg;
//    toCo->dest->c_array[ toCo->i]->state = toCo->toCopy->c_array[ toCo->i]->state;
//    toCo->dest->c_array[ toCo->i]->checked = toCo->toCopy->c_array[ toCo->i]->checked;
    /*printf("copy to index %d, with array size: %d\n", toCo->i, toCo->toCopy->base.count);
    int k = toCo->i;
    int row = toCo->toCopy->c_array[toCo->i]->row;*/
    toCo->dest->c_array[toCo->i] = Cell_new(toCo->toCopy->c_array[toCo->i]->row, toCo->toCopy->c_array[toCo->i]->col);
    toCo->dest->c_array[toCo->i]->state = toCo->toCopy->c_array[ toCo->i]->state;
    toCo->dest->c_array[toCo->i]->checked = toCo->toCopy->c_array[ toCo->i]->checked;
}

CellArray *CellArray_copy( CellArray *toCopy )
{
    CellArray *arr = CellArray_new(); //(CellArray*)calloc(arr->count+1, sizeof(CellArray));
    /*
    arr->c_array = (Cell**)calloc(toCopy->base.count, sizeof(Cell*));*/
    CellArraystr *toCo = (CellArraystr *)calloc(1, sizeof(CellArraystr));
    arr->c_array = (Cell**)calloc(toCopy->base.count, sizeof(Cell*));

    //arr->c_array;
    //toCo->dest = arr;


/*
    pthread_t thread1[toCopy->base.count];
    for(int i=0; i<toCopy->base.count; i++) {
        toCo->i = i;
        pthread_create(&thread1[i], NULL, setValues1, toCo);
    }
    for(int i=0; i<toCopy->base.count; i++) {
        if(thread1[i]) {
        pthread_join(thread1, NULL);
    }*/


    for(int i=0; i<toCopy->base.count; i++) {
        arr->c_array[i] = Cell_new(toCopy->c_array[i]->row, toCopy->c_array[i]->col);
        arr->c_array[i]->state = toCopy->c_array[i]->state;
        arr->c_array[i]->checked = toCopy->c_array[i]->checked;
    }
    arr->base.count= toCopy->base.count;
    return arr;
}

void CellArray_copy_values( CellArray *dest, CellArray *toCopy )
{
    CellArraystr *toCo;
    toCo->dest = dest;
    toCo->toCopy = toCopy;

    pthread_t thread1[toCopy->base.count];
    for(int i=0; i<toCopy->base.count; i++) {
        toCo->i = i;
        pthread_create(&thread1[i], NULL, setValues, toCo);
    }
    for(int i=0; i<toCopy->base.count; i++) {
        pthread_join(thread1, NULL);
    }
}

void CellArray_clear( CellArray *array )
{
    for(int i=0; i<array->base.count; i++) {
        Cell_free(array->c_array[i]);
    }
    free(array->c_array);
    array->c_array = NULL;
    //array->c_array = (Cell**)calloc(1, sizeof(Cell*));

    array->base.count = 0;
}



void CellArray_empty( CellArray *array )
{
    for(int i=0; i<array->base.count; i++) {
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
    /*
    for(int i=array->count; i--; ) {
        Cell_free(array->c_array[i]);
    }
    free(array->c_array);
    array->c_array = NULL;

    array->c_array = (Cell**)calloc(newSize, sizeof(Cell*));*/
//}

int CellArray_has( CellArray *array, Cell *cell )
{
    int rtn = 0;
    int row = cell->row, col = cell->col;
    //printf("Checking array started.\n" );
    for(int i=0; i<array->base.count; i++) {
        if(array->c_array[i]->row == row && array->c_array[i]->col == col) {
            rtn = 1;
            break;
        }
    }
    //printf("Checking array: DONE.\n" );

    return rtn;
}

void CellArray_add( CellArray *array, Cell *cell )
{
    //printf("Adding to array\n" );
    if(array && cell) {
    /*    if(check_doubles == 1) {
            if(CellArray_has(array, cell) == 0) {
                array->c_array = (Cell**)realloc(array->c_array, (array->count+1)*sizeof(Cell*));
                array->c_array[array->count] = cell;
                //printf("add cell: %d\n", array->c_array[array->count]->state);
                //array->c_array = addCell1( array->c_array, cell, array->count );
                array->count++;
            }
        } else {*/
            array->c_array = (Cell**)realloc(array->c_array, (array->base.count+1)*sizeof(Cell*));
            array->c_array[array->base.count] = cell;
            //printf("add cell: %d\n", array->c_array[array->count]->state);
            //array->c_array = addCell1( array->c_array, cell, array->count );
            array->base.count++;
        //}
    }
    //printf("Adding to array:: DONE.\n" );
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

    for(int i=0; i<array->base.count; i++) {
        //printf("size: %d, %d\n", i, array[i]->x);
        if(array->c_array[i]->row == cell->row && array->c_array[i]->col == cell->col) {
            remElem1(array->c_array, i, array->base.count);
            array->c_array = realloc(array->c_array, (array->base.count-1)*sizeof(Cell*));
            array->base.count--;
            break;
        }
    }
}


Cell *CellArray_get( CellArray *array, int index )
{
    Cell *rtn = NULL;

    if(array && index < array->base.count && index >= 0) {
        rtn = array->c_array[index];
    }

    return rtn;
}
