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
    data->datum = 5;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->datum = 2;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->datum = -6;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->datum = 200;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->datum = 150;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    dll_print(list, &print_int, 0);
    printf("===============================================================\n");
    
    // Adding a new key 
    Data_int key = NULL;
    key = allocate_datatype_int();
    key->datum = 5;
    // Using a search-like function to get the item with datum == 5
    Data_int retval = dll_edit_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else {
        printf("Found this element: ");
        print_int((void*)retval); putchar('\n');
    }
    retval->datum = 10000;
    // Freeing the key allocated data
    free_datatype_int((void*)key);
    
    
    // Creating a datum that exists in the list and deleting this item from the
    // list
    Data_int delthis = NULL;
    delthis = allocate_datatype_int();
    delthis->datum = -6;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    dll_print(list, &print_int, 1);
 
    
    // Try and find the element that was deleted
    key = allocate_datatype_int();
    key->datum = -6;
    retval = dll_edit_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else
        print_int((void*)retval);
    free_datatype_int((void*)key);
    
    
    // Delete another list item
    delthis->datum = 150;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    free_datatype_int(delthis);
    dll_print(list, &print_int, 0);
    printf("===============================================================\n");
    printf("dll_get_front: "); 
    retval = dll_get_front(list, &duplicate_datatype_int);
    print_int(retval);
    free_datatype_int(retval);
    putchar('\n');
    printf("dll_get_back: "); 
    retval = dll_get_back(list, &duplicate_datatype_int);
    print_int(retval);
    free_datatype_int(retval);
    retval = NULL;
    putchar('\n');
    printf("===============================================================\n");
    //testing insert at back/front
    data->datum = 12345;
    cneg(dll_insert_at_back(list, data, &duplicate_datatype_int)); 
    data->datum = 54321;
    cneg(dll_insert_at_front(list, data, &duplicate_datatype_int));
    dll_print(list, &print_int, 1);
    printf("===============================================================\n");
    //testing insert before/after
    data->datum = 555;
    key = allocate_datatype_int();
    key->datum = 54321;
    cneg(dll_insert_before(list, data, &duplicate_datatype_int, key, &is_equal_int));
    data->datum = 444;
    cneg(dll_insert_after(list, data, &duplicate_datatype_int, key, &is_equal_int));
    free_datatype_int(key);
    dll_print(list, &print_int, 0);
    printf("===============================================================\n");
    //testing delete back/front
    dll_delete_front(list, &free_datatype_int);
    dll_print(list, &print_int, 1);
    dll_delete_back(list, &free_datatype_int);
    dll_print(list, &print_int, 1);
    printf("===============================================================\n");
    dllistptr blist = NULL;
    cneg(dll_init(&blist));
    data->datum = 8;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    data->datum = 9;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    data->datum = 1992;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    dll_print(blist, &print_int, 1);
    dll_append(list, &blist);
    dll_print(list, &print_int, 0);
    // Destroy the list    
    dll_destroy(&list, &free_datatype_int);
    return (EXIT_SUCCESS);
}

