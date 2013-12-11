/*
 *  Project: Doubly Linked List C-API, example data type
 *  File:   data_type.c
 *  Author: Chris Aslanoglou
 *  Github: https://github.com/chris-asl/doubly-linked-list-API
 */

#include "datatype_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Data_int allocate_datatype_int(void)
{
    Data_int data = NULL;
    data = malloc(sizeof(struct Datatype_int));
    if (data == NULL)
    {
        perror("Error allocating datatype_int");
        return NULL;
    }
    else
        return data;
}


void* duplicate_datatype_int(void* data)
{
    Data_int duplicate = NULL;
    duplicate = allocate_datatype_int();
    if (duplicate == NULL)
        return NULL;
    else {
        duplicate->num = ((Data_int)data)->num;
        return duplicate;
    }
}


void free_datatype_int(void* dataptr)
{
    free((Data_int)dataptr);
    dataptr = NULL;
}


void print_int(void* data)
{
    printf("Data: %d",  ((Data_int)data)->num  );
}


/*
 * Function responsible for checking if the current element is smaller than the 
 * given one
 * (Comparison is to be defined by the user)
 * Return values:
 *      [*] if (current < given),   1 is returned
 *      [*] if (current >= given),  0 is returned
 */
int issmaller_int(void* current, void* given)
{
    int cur = ((Data_int)current)->num;
    int giv = ((Data_int)given)->num;
    if (cur < giv)
        return 1;
    else 
        return 0;
}


int is_equal_int(void* data, void* key)
{
    if ( ((Data_int)data)->num == ((Data_int)key)->num)
        return 1;
    else
        return 0;
}
