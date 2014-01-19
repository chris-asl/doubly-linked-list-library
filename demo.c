/*
 *  Project: Doubly Linked List C-API, client program example
 *  File:   demo.c
 *  Author: Chris Aslanoglou
 *  Github: https://github.com/chris-asl/doubly-linked-list-API
 */

#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList_ADT.h"
#include "datatype_int.h"

#define cneg(r) if(r == -1){return -1;}


int main(int argc, char** argv) {
    dllistptr list = NULL;
    cneg(dll_init(&list));
    

    
    Data_int data;
    // Inserting dummy data
    data = allocate_datatype_int();
    data->num = 5;
    Data_int retval = dll_edit_data(list, (void*)data, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else {
        printf("Found this element: ");
        print_int((void*)retval); putchar('\n');
    }
//    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->num = 2;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    IteratorID invalidationTest = dll_iteratorRequest(list);
    if (invalidationTest == -1) {
        dll_destroy(&list, &free_datatype_int);
        return -1;
    }
    dll_iteratorBegin(list, invalidationTest);
    Data_int returned = dll_iteratorGetObj(list, invalidationTest);
    if (returned) {
        printf("\t\t\t");print_int(returned); printf("\n");
    }
    data->num = -6;
    cneg(dll_insert_at_front(list, (void*)data, &duplicate_datatype_int));
    returned = dll_iteratorGetObj(list, invalidationTest);
    if (returned) {
        printf("\t\t\t");print_int(returned); printf("\n");
    }
    dll_print(list, &print_int, 1);
    dll_iteratorBegin(list, invalidationTest);
    returned = dll_iteratorGetObj(list, invalidationTest);
    if (returned) {
        printf("\t\t\t");print_int(returned); printf("\n");
    }
    //delete last element and check where the iterator points
    dll_delete_back(list, &free_datatype_int);
    returned = dll_iteratorGetObj(list, invalidationTest);
    if (returned) {
        printf("\t\t\t");print_int(returned); printf("\n");
    }
    //try deleting all elements
    printf("===============================================================\n");
    printf("Testing invalidation of iterator\n");
    // simple test of setting to Begin
    print_int(dll_iteratorGetObj(list, invalidationTest));
    dll_print(list, &print_int, 1);
    Data_int delthis = NULL;
    delthis = allocate_datatype_int();
    delthis->num = -6;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    dll_print(list, &print_int, 1);
    // test after deleting an element
//    print_int(dll_iteratorGetObj(list, invalidationTest));
    delthis->num = 2;
    printf("Deleting element (-2) result: %d\n",
            dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int));
    free_datatype_int(delthis);
    dll_print(list, &print_int, 1);
    // now let's see what happened with the iterator
    returned = dll_iteratorGetObj(list, invalidationTest);
    if (returned)
        print_int(returned);
    printf("===============================================================\n");
    printf("===============================================================\n");
    printf("===============================================================\n");
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->num = 200;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    data->num = 150;
    cneg(dll_insert_sorted(list, data, &issmaller_int, &duplicate_datatype_int));
    dll_print(list, &print_int, 0);
    printf("===============================================================\n");
    
    // Adding a new key 
    Data_int key = NULL;
    key = allocate_datatype_int();
    key->num = 5;
    // Using a search-like function to get the item with num == 5
    retval = dll_edit_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else {
        printf("Found this element: ");
        print_int((void*)retval); putchar('\n');
        retval->num = 10000;
    }
    // Freeing the key allocated data
    free_datatype_int((void*)key);
    
    
    // Creating a num that exists in the list and deleting this item from the list
    delthis = NULL;
    delthis = allocate_datatype_int();
    delthis->num = -6;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    dll_print(list, &print_int, 1);
 
    
    // Try and find the element that was deleted
    key = allocate_datatype_int();
    key->num = -6;
    retval = dll_edit_data(list, (void*)key, &is_equal_int);
    if (retval == NULL)
        printf("Element not found\n");
    else
        print_int((void*)retval);
    free_datatype_int((void*)key);
    
    
    // Delete another list item
    delthis->num = 150;
    dll_delete(list, (void*)delthis, &is_equal_int, &free_datatype_int);
    free_datatype_int(delthis);
    dll_print(list, &print_int, 0);
    printf("===============================================================\n");
    printf("dll_get_front: "); 
    retval = dll_get_front(list, &duplicate_datatype_int, 1);
    print_int(retval);
    free_datatype_int(retval);
    putchar('\n');
    printf("dll_get_back: "); 
    retval = dll_get_back(list, &duplicate_datatype_int, 1);
    print_int(retval);
    free_datatype_int(retval);
    retval = NULL;
    putchar('\n');
    printf("===============================================================\n");
    //testing insert at back/front
    data->num = 12345;
    cneg(dll_insert_at_back(list, data, &duplicate_datatype_int)); 
    data->num = 54321;
    cneg(dll_insert_at_front(list, data, &duplicate_datatype_int));
    dll_print(list, &print_int, 1);
    printf("===============================================================\n");
    //testing insert before/after
    data->num = 555;
    key = allocate_datatype_int();
    key->num = 54321;
    cneg(dll_insert_before(list, data, &duplicate_datatype_int, key, &is_equal_int));
    data->num = 444;
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
    data->num = 8;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    data->num = 9;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    data->num = 1992;
    cneg(dll_insert_at_back(blist, data, &duplicate_datatype_int));
    dll_print(blist, &print_int, 1);
    dll_append(list, &blist);
    dll_print(list, &print_int, 0);

    // iterators testing
    IteratorID iter = dll_iteratorRequest(list);
    if (iter < 0) {
        dll_destroy(&list, &free_datatype_int);
        return -1;
    }
    printf("Clients can implement their own print\n");
    printf("List contents (from head to tail): \n");
    Data_int temp = NULL;
    do {
        printf("\t");
        temp = dll_iteratorGetObj(list, iter);
        if (temp != NULL)
            print_int(temp);
        putchar('\n');
        int ret = dll_iteratorNext(list, iter);
        if (ret == -1) {
            fprintf(stderr, "Error printing my list\n");
            dll_destroy(&list, &free_datatype_int);
            return -1;
        }
        else if (ret == 2) //end of list
            break;
    }while(1);
    printf("List contents (from tail to head): \n");
    temp = NULL;
    IteratorID iter2 = dll_iteratorRequest(list);
    dll_iteratorEnd(list,iter2);
    do {
        printf("\t");
        temp = dll_iteratorGetObj(list, iter2);
        if (temp != NULL)
            print_int(temp);
        putchar('\n');
        int ret = dll_iteratorPrev(list, iter2);
        if (ret == -1) {
            fprintf(stderr, "Error printing my list\n");
            dll_destroy(&list, &free_datatype_int);
            return -1;
        }
        else if (ret == 2) //end of list
            break;
    }while(1);
    //test delete iterator
    dll_iteratorDelete(list, iter2);
    //test using the deleted
    dll_iteratorEnd(list, iter2);
    //test using the remaining one
    printf("List contents (from head to tail): \n");
    temp = NULL;
    dll_iteratorBegin(list, iter);
    do {
        printf("\t");
        temp = dll_iteratorGetObj(list, iter);
        if (temp != NULL)
            print_int(temp);
        putchar('\n');
        int ret = dll_iteratorNext(list, iter);
        if (ret == -1) {
            fprintf(stderr, "Error printing my list\n");
            dll_destroy(&list, &free_datatype_int);
            return -1;
        }
        else if (ret == 2) //end of list
            break;
    }while(1);
    printf("\n\nDone\n");
    
    //test deleting all iterators with dll_iteratorDelete
    dll_iteratorDelete(list, iter);
    // Destroy the list    
    dll_destroy(&list, &free_datatype_int);
    free_datatype_int(data);
    return (EXIT_SUCCESS);
}

