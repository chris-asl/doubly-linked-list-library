/*
 *  Project: Doubly Linked List C-API
 *  File:   DoublyLinkedList_ADT.c
 *  Author: Chris Aslanoglou
 *  Github: https://github.com/chris-asl/doubly-linked-list-API
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "DoublyLinkedList_ADT.h"


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
    dllnodeptr *iteratorsArray; 
    int iteratorsCount;
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
    (*listptr_addr)->iteratorsArray = NULL;
    (*listptr_addr)->iteratorsCount = 0;
    return 0;
}


/*
 * Function returning the size of the list
 */
int dll_size(dllistptr list)
{
    return list->size;
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
    if (dll_size(list) == 0)
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
void dll_print(const dllistptr list, void (*print_data)(void* data), 
        int print_inline)
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
            if (print_inline) {
                (*print_data)(current->data);
                printf(" -> ");
            }
            else {
                printf(" -> ");
                (*print_data)(current->data);
                putchar('\n');
                
            }
            current = current->next;
        }
        //print tail element
        if (print_inline)
            (*print_data)(current->data);
        else {
            printf(" -> ");
            (*print_data)(current->data);
        }
            
        printf("\n====Done printing list====\n");
        return;
    }
}


/*
 * Function responsible for inserting an element at the end of the list
 * The 2nd and 3rd arguments are to be used in conjuction, as the data parameter
 * acts as a dummy object which is going to be duplicated as a new object of the
 * data member of the list node struct.
 * The duplicate function is responsible for allocating a new object and 
 * assigning the values of source to destination.
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 */
int dll_insert_at_back(dllistptr list, void* data, void* (*duplicate)(void*))
{
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_at_back - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_at_back - Error: Data given is NULL\n");
        return -1;
    }
    else if (dll_isempty(list)) {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_back - Empty list case, error: ");
            return -1;
        }
        list->head = elem;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->previous = NULL;
        elem->data = (*duplicate)(data);
        return 0;
    }
    else {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_back - Error: ");
            return -1;
        }       
        (list->tail)->next = elem;
        elem->previous = list->tail;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->data = (*duplicate)(data);
        return 0;
    }
}


/*
 * Function responsible for inserting an element at the start of the list
 * The 2nd and 3rd arguments are to be used in conjuction, as the data parameter
 * acts as a dummy object which is going to be duplicated as a new object of the
 * data member of the list node struct.
 * The duplicate function is responsible for allocating a new object and 
 * assigning the values of source to destination.
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 */
int dll_insert_at_front(dllistptr list, void* data, void* (*duplicate)(void*))
{
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_at_front - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_at_front - Error: Data given is NULL\n");
        return -1;
    }
    else if (dll_isempty(list)) {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_front - Empty list case, error: ");
            return -1;
        }
        list->head = elem;
        list->tail = elem;
        list->size++;
        elem->next = NULL;
        elem->previous = NULL;
        elem->data = (*duplicate)(data);
        return 0;
    }
    else {
        dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
        if (elem == NULL) {
            perror("dll_insert_at_front - Error: ");
            return -1;
        }
        (list->head)->previous = elem;
        elem->next = list->head;
        list->head = elem;
        elem->previous = NULL;
        list->size++;
        elem->data = (*duplicate)(data);
        return 0;
    }
}


/*
 * Function responsible for inserting an element into the list while keeping it
 * sorted by a comparison defined by the user with a function called 
 * issmaller(*). Elements are going to be inserted in ascending order starting 
 * from the head. 
 * The 4th argument (duplication function) is explained at the dll_insert_at_end
 * function.
 * Return values:
 *      [*] On success,  0 is returned
 *      [*] On failure,  -1 is returned
 * 
 * (*): issmaller must be a function that:
 *      [*] Returns 1, if (1st parameter < 2nd parameter)
 *      [*] Returns 0, if (1st parameter >= 2nd parameter) 
 */
int dll_insert_sorted(dllistptr list, void* data, 
        int (*issmaller)(void*, void*), void* (*duplicate)(void*))
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
        elem->data = (*duplicate)(data);
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
            elem->data = (*duplicate)(data);
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
            elem->data = (*duplicate)(data);
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
            elem->data = (*duplicate)(data);
            return 0;
        }
    }
}


/*
 * Inserts the element `data` before the `key` element provided. If the key is 
 * not found -1 is returned.
 * Return values:
 *      [*]: On success, 0 is returned
 *      [*]: On error or `on key not found`, -1 is returned
 */
int dll_insert_before(dllistptr list, void* data, void* (*duplicate)(void*),
        void* key, int (*is_equal)(void*, void*)) 
{
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_before - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_before - Error: Data given is NULL\n");
        return -1;
    }
    // 3. Key must not be NULL
    if (key == NULL) {
        fprintf(stderr, "dll_insert_before - Error: Key given is NULL\n");
        return -1;
    }
    //find the element (if it exits)
    dllnodeptr current = list->head;
    do {
        if ( (*is_equal)(key, current->data) ) {
            //found correct place
            //add the element before the current node
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL) {
                perror("dll_insert_sorted - Error: ");
                return -1;
            }
            elem->previous = current->previous;
            elem->next = current;
            if (current != list->head)
                (current->previous)->next = elem;
            else {
                list->head = elem;
                elem->previous = NULL;
            }
            current->previous = elem;
            elem->data = (*duplicate)(data);
            list->size++;
            return 0;
        }
        else {
            if (current == list->tail)
                return -1;
            else
                current = current->next;
        }
    }while(1);
}


/*
 * Inserts the element `data` after the `key` element provided. If the key is 
 * not found -1 is returned.
 * Return values:
 *      [*]: On success, 0 is returned
 *      [*]: On error or `on key not found`, -1 is returned
 */
int dll_insert_after(dllistptr list, void* data, void* (*duplicate)(void*),
        void* key, int (*is_equal)(void*, void*)) {
    // Safety checks firstly
    // 1. Dllist must be initialized
    if (list == NULL) {
        fprintf(stderr, "dll_insert_before - Error: DLList has not been initialized\n");
        return -1;
    }
    // 2. Data must not be NULL
    if (data == NULL) {
        fprintf(stderr, "dll_insert_before - Error: Data given is NULL\n");
        return -1;
    }
    // 3. Key must not be NULL
    if (key == NULL) {
        fprintf(stderr, "dll_insert_before - Error: Key given is NULL\n");
        return -1;
    }
    //find the element (if it exits)
    dllnodeptr current = list->head;
    do {
        if ( (*is_equal)(key, current->data) ) {
            //found correct place
            //add the element after the current node
            dllnodeptr elem = malloc(sizeof(struct DoublyLinkedListNode));
            if (elem == NULL) {
                perror("dll_insert_sorted - Error: ");
                return -1;
            }
            elem->next = current->next;
            elem->previous = current;
            if (current != list->tail)
                (current->next)->previous = elem;
            else {
                list->tail = elem;
                elem->next = NULL;
            }
            current->next = elem;
            elem->data = (*duplicate)(data);
            list->size++;
            return 0;
        }
        else {
            if (current == list->tail)
                return -1;
            else
                current = current->next;
        }
    }while(1);
}


/*
 * Function that enables accessing data at the list, identified by the 2nd
 * argument, with an is_equal type function as 3rd argument
 * Return values:
 *      [*] On success, the object is returned
 *      [*] On element not found or on error, NULL is returned
 */
void* dll_edit_data(dllistptr list, void* data, int (*is_equal)(void*, void*))
{
    if (list == NULL) {
        fprintf(stderr, "dll_edit_data - Error: DLList has not been initialized\n");
        return NULL;
    }
    if(dll_isempty(list)) {
        return NULL;
    }
    else {
        //find the element (if it exits)
        //search method
        dllnodeptr current = list->head;
        do {
            if ( (*is_equal)(data, current->data) )
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
 * Function that returns a copy of the data located at the front (Head) of 
 * the list
 */
void* dll_get_front(dllistptr list, void* (*duplicate)(void*)) {
    return (*duplicate)(list->head->data);
}


/*
 * Function that returns a copy of the data located at the back (Tail) of 
 * the list
 */
void* dll_get_back(dllistptr list, void* (*duplicate)(void*)) {
    return (*duplicate)(list->tail->data);
}


/*
 * Function responsible for appending `list b` to `list a`
 * Upon return, the second list pointer (a.k.a. dllistptr) is going to be freed
 * and nullified, so that it cannot longer be used
 */
void dll_append(dllistptr alist, dllistptr* listptrb)
{
    //make the tail of `list a` to point to the `list b` head
    (alist->tail)->next = (*listptrb)->head;
    //symmetrically
    ((*listptrb)->head)->previous = alist->tail;
    //update `list a` tail
    alist->tail = (*listptrb)->tail;
    //free `list b`
    free(*listptrb);
    (*listptrb)->head = NULL;
    (*listptrb)->tail = NULL;
    (*listptrb)->size = 0;
    listptrb = NULL;
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
            (current->previous)->next = current->next;
            (current->next)->previous = current->previous;
            list->size--;
            (*free_data)((void*)current->data);
            free(current);
            current = NULL;
        }
        return 0;
    }
}


/*
 * Deletes the tail element of the list
 */
void dll_delete_back(dllistptr list, void (*free_data)(void* data)) 
{
    dllnodeptr deletion = list->tail;
    list->tail = (list->tail)->previous;
    (list->tail)->next = NULL;
    
    (*free_data)(deletion->data);
    deletion->data = NULL;
    free(deletion);
    deletion->previous = NULL;
}


/*
 * Deletes the head element of the list
 */
void dll_delete_front(dllistptr list, void (*free_data)(void* data)) 
{
    dllnodeptr deletion = list->head;
    list->head = (list->head)->next;
    (list->head)->previous = NULL;
    
    (*free_data)(deletion->data);
    deletion->data = NULL;
    free(deletion);
    deletion->next = NULL;
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
        //free iterators, if there are any
        if ((*dllptr_addr)->iteratorsCount > 0) {
            free((*dllptr_addr)->iteratorsArray);
            (*dllptr_addr)->iteratorsArray = (void*)NULL;
            (*dllptr_addr)->iteratorsCount = 0;
        }
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
        //free iterators, if there are any
        if ((*dllptr_addr)->iteratorsCount > 0) {
            free((*dllptr_addr)->iteratorsArray);
            (*dllptr_addr)->iteratorsArray = (void*)NULL;
            (*dllptr_addr)->iteratorsCount = 0;
        }
        //free the doubly linked list structure
        free(*dllptr_addr);
        *dllptr_addr = NULL;
        return;
    }
}

/*
 *  Function responsible for allocating a new Iterator object
 *  assigning it to the head of the list and then returning its id 
 *  Return values:  
 *      [*] On success, the ID of the Iterator is returned 
 *      [*] On failure, -1 is returned
 */
IteratorID dll_iteratorRequest(dllistptr list)
{
    static IteratorID id = 0;
    list->iteratorsArray = realloc(list->iteratorsArray, (list->iteratorsCount + 1) * sizeof(dllnodeptr));
    if (list->iteratorsArray == NULL) {
        perror("dll_requestIterator - Error: Cannot allocate iterator");
        return -1;
    }
    list->iteratorsCount++;
    // set Iterator to point to the head
    if (dll_iteratorBegin(list, id) < 0) {
        fprintf(stderr, "dll_requestIterator - Error: Cannot set iterator to list head\n");
        return -1;
    }
    return id;
}

/*
 * Function responsible for bound checking for the array of the iterators
 * Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 */
 int dll_iteratorInBounds(dllistptr list, IteratorID iterID)
 {
    if (iterID >= list->iteratorsCount){
        fprintf(stderr, "dll_iteratorBounds - Error: IterID given is out of bounds.\nCurrent iteratorCount: %d\n", list->iteratorsCount);
        return -1;
    }
    return 0;
 }

/*
 *  Function responsible for setting the iterator with ID iterID 
 *  to point to the head of the list
 *  Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 */
int dll_iteratorBegin(dllistptr list, IteratorID iterID)
{
    // check if the iterID is within bounds
    if (dll_iteratorInBounds(list, iterID) < 0)
        return -1;
    list->iteratorsArray[iterID] = list->head;
    return 0;
}

/*
 *  Function responsible for setting the iterator with ID iterID 
 *  to point to the tail of the list
 *  Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 */
int dll_iteratorEnd(dllistptr list, IteratorID iterID)
{
    // check if the iterID is within bounds
    if (dll_iteratorInBounds(list, iterID) < 0)
        return -1;
    list->iteratorsArray[iterID] = list->tail;
    return 0;
}

/*
 *  Function responsible for returning the Object into the node
 *  pointed by the iterator
 *  Return values:
 *      [*] On success, the object is returned
 *      [*] On failure, NULL is returned
 */
 const void* dll_iteratorGetObj(dllistptr list, IteratorID iterID)
 {
    //check if the iterID is within bounds
    if (dll_iteratorInBounds(list, iterID) < 0)
        return NULL;
    return (const void*) list->iteratorsArray[iterID]->data;
 }

/*
 *  Function responsible for setting the iterator to the next node
 *  If by advancing, the iterator is requested to point after the tail
 *  of the list, 1 is returned
 *  Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 *      [*] On the case described above, 1 is returned
 */
 int dll_iteratorNext(dllistptr list, IteratorID iterID)
 {
    if (dll_iteratorInBounds(list, iterID) < 0)
        return -1;
    // check the case of calling this function on a iterator that points to the
    // tail of the list
    if (list->iteratorsArray[iterID] == list->tail) {
        return 1;
    }
    list->iteratorsArray[iterID] = list->iteratorsArray[iterID]->next;
    return 0;
 }

 /*
 *  Function responsible for setting the iterator to the previous node
 *  If by requesting the previous node, the iterator points before the head
 *  of the list, 1 is returned
 *  Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 *      [*] On the case described above, 1 is returned
 */
 int dll_iteratorPrev(dllistptr list, IteratorID iterID)
 {
    if (dll_iteratorInBounds(list, iterID) < 0)
        return -1;
    // check the case of calling this function on a iterator that points to the
    // head of the list
    if (list->iteratorsArray[iterID] == list->head) {
        return 1;
    }
    list->iteratorsArray[iterID] = list->iteratorsArray[iterID]->previous;
    return 0;
 }

/*
 *  Function responsible for deleting the iterator pointed by iterID
 *  Return values:
 *      [*] On success, 0 is returned
 *      [*] On failure, -1 is returned
 */
int dll_iteratorDelete(dllistptr list, IteratorID iterID)
{
    if (dll_iteratorInBounds(list, iterID) < 0)
        return -1;
    list->iteratorsCount--;
    memmove(list->iteratorsArray + iterID, list->iteratorsArray + iterID + 1, list->iteratorsCount - iterID);
    list->iteratorsArray = realloc(list->iteratorsArray, list->iteratorsCount * sizeof(dllnodeptr));
    if (list->iteratorsArray == NULL) {
        fprintf(stderr, "dll_iteratorDelete - Error: Error decreasing the size of the iterators array\n");
        return -1;
    }
    return 0;
}
