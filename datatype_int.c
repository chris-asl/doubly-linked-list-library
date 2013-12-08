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
        duplicate->datum = ((Data_int)data)->datum;
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
    printf("Data: %d",  ((Data_int)data)->datum  );
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
    int cur = ((Data_int)current)->datum;
    int giv = ((Data_int)given)->datum;
    if (cur < giv)
        return 1;
    else 
        return 0;
}


int is_equal_int(void* vdata, void* vkey)
{
    Data_int data = (Data_int)vdata;
    Data_int key = (Data_int)vkey;
    if (data->datum == key->datum)
        return 1;
    else
        return 0;
}
