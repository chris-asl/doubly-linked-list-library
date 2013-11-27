/* 
 * File:   main.c
 * Author: chris
 *
 * Created on May 17, 2013, 9:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList_ADT.h"
#include "datatype_int.h"

#define cneg(r) if(r == -1){return -1;}


int main(int argc, char** argv) {
    
    /*
     *  Another test case: 
     *      Add the same element twice
     *      Search for it
     *      Delete it once
     *      Search for it
     *      Delete it once
     *      Add it again
     *      Search for it
     *      Delete
     *      Search
     */
      
    
    
    dllistptr list = NULL;
    cneg(dll_init(&list));
    
    
    Data_int data;
    // Inserting dummy data
    data = allocate_datatype_int();
    if (data != NULL)
    {
        data->datum = 5;
        cneg(dll_insert_at_end(list, (void *)data, &duplicate_datatype_int));
    }
    data = allocate_datatype_int();
    if (data != NULL)
    {
        data->datum = 200;
        cneg(dll_insert_at_end(list, (void *)data, &duplicate_datatype_int));
    }
    data = allocate_datatype_int();
    if (data != NULL)
    {
        data->datum = 10;
        cneg(dll_insert_at_end(list, (void *)data, &duplicate_datatype_int));
    }
    data = allocate_datatype_int();
    if (data != NULL)
    {
        data->datum = 2;
        cneg(dll_insert_at_end(list, (void *)data, &duplicate_datatype_int));
    }
    data = allocate_datatype_int();
    if (data != NULL)
    {
        data->datum = -6;
        cneg(dll_insert_at_end(list, (void *)data, &duplicate_datatype_int));
    }
    dll_print(list, &print_int);
    printf("===============================================================\n");
    data = allocate_datatype_int();
    data->datum = 200;
    dll_print(list, &print_int);
    print_int((void*)data);
    cneg(dll_delete(list, data, &is_equal_int, &free_datatype_int)); 
    dll_print(list, &print_int);
    printf("===============================================================\n");
    
    
    
    
    // Adding a new key 
    Data_int key = NULL;
    key = allocate_datatype_int();
    key->datum = 5;
    // Using a search-like function to get the item with datum == 5
    Data_int retval = dll_get_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else
        print_int((void*)retval);
    
    // Freeing the key allocated data
    free_datatype_int((void*)key);
    
    // Creating a datum that exists in the list and deleting this item from the
    // list
    Data_int delthis = NULL;
    delthis = allocate_datatype_int();
    delthis->datum = -6;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    // Freeing the key of deletion, as well
    free_datatype_int(delthis);
    dll_print(list, &print_int);
 
    // Try and find the element that was deleted
    key = allocate_datatype_int();
    key->datum = -6;
    retval = dll_get_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else
        print_int((void*)retval);
    free_datatype_int((void*)key);
    
    // Delete another list item
    delthis = allocate_datatype_int();
    delthis->datum = 2;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    free_datatype_int(delthis);
    dll_print(list, &print_int);
     
    
   // Destroy the list    
    dll_destroy(&list, &free_datatype_int);
    
    return (EXIT_SUCCESS);
}

