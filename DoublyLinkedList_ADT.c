/*
 *  Project: DoublyLinkedList (Dllist) C API
 *  Author: Chris Aslanoglou
 */


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "DoublyLinkedList_ADT.h"
#include "datatype_int.h"


// Node type definition
typedef struct DoublyLinkedListNode *dllnodeptr;
struct DoublyLinkedListNode
{
    dllnodeptr previous, next;
    void* data;
};

// DLL ADT definition
struct DoublyLinkedList_ADT
{
    dllnodeptr head, tail;
    int size;
};


/*
 * Function responsible for initializing the Doubly Linked List ADT
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 */
int dll_init(dllistptr *listptr_addr)
{
    (*listptr_addr) = malloc(sizeof(struct DoublyLinkedList_ADT));
    if ((*listptr_addr) == NULL) {
        perror("dll_init - Error initializing DoublyLinkedList ADT");
        return -1;
    }
    (*listptr_addr)->head = NULL;
    (*listptr_addr)->tail = NULL;
    (*listptr_addr)->size = 0;
}

/*
 * Function responsible for checking if the list is empty
 * Return values:
 *      [*] on empty list, 1 is returned
 *      [*] on non empty list, 0 is returned
 */
int dll_isempty(dllistptr list)
{
    if (list == NULL) {
        fprintf(stderr, "dll_isempty - Error: DLList has not been initialized\n");
        return -1;
    }
    if (list->size == 0)
        return 1;
    else 
        return 0;
}


/*
 * Function responsible for printing the list in this fashion:
 *          "element -> element -> element" (delimiter "->")
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 */
void dll_print(const dllistptr list, void (*print_data)(void* data))
{
    if (list == NULL) {
        fprintf(stderr, "dll_print - Error: DLList has not been initialized\n");
        return;
    }
    if (dll_isempty(list)) {
        printf("List is empty\n");
        return;
    }
    else {
        printf("=======Printing list======\n");
        printf("List size: %d\n", list->size);
        dllnodeptr current = list->head;
        while (current != list->tail) {
            (*print_data)(current->data);
            printf(" -> ");
            current = current->next;
        }
        //print tail element
        (*print_data)(current->data);
        printf("\n====Done printing list====\n");
        return;
    }
}


/*
 * Function responsible for inserting an element at the end of the list
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 */
int dll_insert_at_end(dllistptr list, void* data, void* (*duplicate)(void*))
{
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_at_end - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_at_end - Error: Data given is NULL\n");
        return -1;
    }
    else if (dll_isempty(list)) {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_end - Empty list case, error: ");
            return -1;
        }
        list->head = elem;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->previous = NULL;
        elem->data = data;
        return 0;
    }
    else {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_end - Error: ");
            return -1;
        }
        (list->tail)->next = elem;
        elem->previous = list->tail;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->data = data;
        return 0;
    }
}


/*
 * Function responsible for inserting an element into the list while keeping it
 * sorted by a comparison defined by the user with a function called 
 * issmaller(*). Elements are going to be inserted in ascending order starting 
 * from the head
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 * 
 * (*): issmaller must be a function that:
 *      [*] Returns 1, if (1st parameter < 2nd parameter)
 *      [*] Returns 0, if (1st parameter >= 2nd parameter) 
 */
int dll_insert_sorted(dllistptr list, void* data,  int (*issmaller)(void*, void*) )
{
    /*
     * Scenarios:
     *      1. list is empty:
     *              a. head and tail pointers point to the new node
     *              b. next and previous pointers point to the node itself
     *      2. list isn't empty:
     *              find where in the list the element belongs (cases: )
     *                  i. element is to be inserted at the end (bigger than 
     */
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_sorted - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_sorted - Error: Data given is NULL\n");
        return -1;
    }
    if (dll_isempty(list))  {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_sorted: Empty Dllist case, error: ");
            return -1;
        }
        list->head = elem;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->previous = NULL;
        elem->data = data;
        return 0;
    }
    else {
        //find where the new element is bigger than the tail 
        //so as to avoid the search method
        if ( (*issmaller)((list->tail)->data, data) ) {
            //case in which the element is to be added into the end of the list
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL) {
                perror("dll_insert_sorted: Tail insertion case, error: ");
                return -1;
            }
            (list->tail)->next = elem;
            elem->previous = list->tail;
            elem->next = NULL;
            list->tail = elem;
            list->size++;
            elem->data = data;
            return 0;
        }
        //search method
        dllnodeptr current = list->head;
        do {
            if ( (*issmaller)(data, current->data) )
                break;
            else {
                if (current == list->tail)
                    break;
                else
                    current = current->next;
            }
        }while(1);
        //here we must identify which break occurred
        /*if (current == list->tail)
        {
            //case in which the element is to be added into the end of the list
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL)
            {
                perror("Sorted_insertion: tail insertion, error: ");
                return -1;
            }
            current->next = elem;
            elem->previous = current;
            elem->next = NULL;
            list->tail = elem;
            list->size++;
            copy_data(&(elem->data), data);
            return 0;
        }*/
        if (current == list->head) {
            //case in which the element is to be added into the start of the list
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL) {
                perror("dll_insert_sorted: Tail insertion case, error: ");
                return -1;
            }
            elem->next = list->head;
            elem->previous = NULL;
            (elem->next)->previous = elem;
            list->head = elem;
            list->size++;
            elem->data = data;
            return 0;
        }
        else {
            //add the element before the current node
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL) {
                perror("dll_insert_sorted - Error: ");
                return -1;
            }
            (current->previous)->next = elem;
            elem->previous = current->previous;
            current->previous = elem;
            elem->next = current;
            list->size++;
            elem->data = data;
            return 0;
        }
    }
}
/*
 * Function that enables accessing data at the list, identified by the 2nd
 * argument, with an is_equal type function as 3rd argument, and as last 
 * parameter a function returning a void pointer to the data of the node
 * Return values:
 *      [*] On success, the object is returned
 *      [*] On element not found or on error, NULL is returned
 */
void* dll_get_data(dllistptr list, void* key, int (*is_equal)(void*, void*))
{
    if (list == NULL) {
        fprintf(stderr, "dll_get_data - Error: DLList has not been initialized\n");
        return NULL;
    }
    if(dll_isempty(list)) {
        return NULL;
    }
    else {
        //find the element (if it exits and delete it)
        //search method
        dllnodeptr current = list->head;
        do {
            if ( (*is_equal)(key, current->data) )
                return current->data;
            else {
                if (current == list->tail)
                    return NULL;
                else
                    current = current->next;
            }
        }while(1);
    }
}

/*
 * Function responsible for deleting the element that contains the `key` 
 * given as a 2nd parameter
 * Also, two pointers to functions needed, the 1st for identifying the 
 * correct element and the second one for freeing it
 * Return values:
 *      [*] On success,             0 is returned
 *      [*] On element not found,   1 is returned
 *      [*] On error,               -1 is returned
 */
int dll_delete(dllistptr list, void* key, int (*is_equal)(void*, void*), 
                void (*free_data)(void*))
{
    if (list == NULL) {
        fprintf(stderr, "dll_delete - Error: DLList has not been initialized\n");
        return -1;
    }
    if (key == NULL) {
        fprintf(stderr, "dll_delete - Error: Key parameter is NULL\n");
        return -1;
    }
    if(dll_isempty(list)) {
        fprintf(stderr, "dll_delete - Error: DLList is empty\n");
        return 1;
    }
    else {
        //find the element (if it exits and delete it)
        //search method
        dllnodeptr current = list->head;
        do {
            if ( (*is_equal)(key, current->data) )
                break;
            else {
                if (current == list->tail)
                {
                    current = NULL;
                    break;
                }
                else
                    current = current->next;
            }
        }while(1);
        if (current == NULL) {
            //element wasn't found
            return 1;
        }
        else if (current == list->head) {
            if (current != list->tail) {
                //first node doesn't have previous
                (current->next)->previous = NULL;
                list->head = current->next;
                list->size--;
                (*free_data)((void*) current->data);
                free(current);
                current = NULL;
            }
            else {
                list->head = NULL;
                list->tail = NULL;
                list->size--;
                (*free_data)((void*) current->data);
                free(current);
                current = NULL;
            }
        }
        else if (current == list->tail) {
            list->tail = current->previous;
            //last node doesn't have next
            (current->previous)->next = NULL;
            list->size--;
            (*free_data)((void*)current->data);
            free(current);
            current = NULL;
        }
        else {
            //print_int(current->data); putchar('\n');
            (current->previous)->next = current->next;
            (current->next)->previous = current->previous;
            list->size--;
            (*free_data)((void*)current->data);
            free(current);
            current = NULL;
            //dll_print(list, &print_int);
        }
        return 0;
    }
}



/*
 * Function responsible for freeing all the allocated memory
 */
void dll_destroy(dllistptr *dllptr_addr, void (*free_data)(void* data))
{
    if (*dllptr_addr == NULL) {
        fprintf(stderr, "dll_destroy - Error: DLList has not been initialized\n");
        return;
    }
    if(dll_isempty(*dllptr_addr)) {
        //free doubly linked list structure
        free(*dllptr_addr);
        *dllptr_addr = NULL;
        return;
    }
    else {
        dllnodeptr current = (*dllptr_addr)->head;
        dllnodeptr to_be_deleted = NULL;
        while(1) {
            if (current == NULL)
                break;
            to_be_deleted = current;
            //avoid dangling pointers
            if (to_be_deleted == (*dllptr_addr)->head)
                (*dllptr_addr)->head = NULL;
            else if(to_be_deleted == (*dllptr_addr)->tail)
                (*dllptr_addr)->tail = NULL;
            current = current->next;
            (*free_data)(to_be_deleted->data);
            free(to_be_deleted);
            to_be_deleted = NULL;
        }
        //free the doubly linked list structure
        free(*dllptr_addr);
        *dllptr_addr = NULL;
        return;
    }
}

