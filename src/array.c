/**
 * Copyright (c) 2013 Ibrahim Abd Elkader <i.abdalkader@gmail.com> 
 * See the file COPYING for copying permission.
 */
#include <stdlib.h>
#include <string.h>
#include "array.h"
#define ARRAY_INIT_SIZE  10
struct array {
    int index;
    int length;
    void **data;
    array_dtor dtor;
};

void array_alloc(struct array **a, array_dtor dtor)
{
    struct array *array;
    array = malloc(sizeof(struct array));
    array->index  = 0;
    array->length = ARRAY_INIT_SIZE;
    array->dtor   = dtor;
    array->data   = malloc(array->length*sizeof(void*));
    *a = array;
}

void array_free(struct array *array)
{
    int i=0;
    for (i=0; i<array->index; i++){
        array->dtor(array->data[i]);
    }
    free(array->data);
    free(array);
}

int  array_length(struct array *array)
{
    return array->index;
}

void array_push_back(struct array *array, void *element)
{
    if (array->index == array->length-1) {
        array->length += ARRAY_INIT_SIZE;
        array->data    = realloc(array->data, array->length * sizeof(void*));
    }
    array->data[array->index++] = element;
}

void *array_at(struct array *array, int idx)
{
    return array->data[idx];
}

void array_erase(struct array *array, int idx)
{
    array->dtor(array->data[idx]);
    memmove(array->data+idx, array->data+idx+1, (array->index-idx-1) * sizeof(void*));
    array->index--;
}

void array_resize(struct array *array, int idx)
{
    while (array->index > idx) {
        array->dtor(array->data[array->index-1]);
        array->index--;
    }
}

void array_sort(struct array *array, array_comp comp)
{
    qsort(array->data, array->index, sizeof(void*), comp);
}

