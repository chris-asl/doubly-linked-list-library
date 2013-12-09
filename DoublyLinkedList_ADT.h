/* 
 * File:   DoublyLinkedList_ADT.h
 * Author: chris
 *
 * Created on May 18, 2013, 7:26 PM
 */

#ifndef DOUBLYLINKEDLIST_ADT_H
#define	DOUBLYLINKEDLIST_ADT_H

#ifdef	__cplusplus
extern "C"
{
#endif
    
    typedef struct DoublyLinkedList_ADT *dllistptr;

    /*
     * Function responsible for initializing the Doubly Linked List ADT
     * Return values:
     *      [*] On success,  0 is returned
     *      [*] On failure,  -1 is returned
     */
    int dll_init(dllistptr*);
    /*
    * Function returning the size of the list
    */
    int dll_size(dllistptr);
    /*
     * Function responsible for checking if the list is empty
     * Return values:
     *      [*] on empty list, 1 is returned
     *      [*] on non empty list, 0 is returned
     */
    int dll_isempty(dllistptr);
    /*
    * Function responsible for printing the list in this fashion:
    *          "element -> element -> element" (delimiter "->")
    * Return values:
    *      [*] On success,  0 is returned
    *      [*] On failure,  -1 is returned
    */
    void dll_print(const dllistptr, void (*print_data )( void* ), int);
    /*
     * Function responsible for inserting an element at the end of the list
     * Return values:
     *      [*] On success,  0 is returned
     *      [*] On failure,  -1 is returned
     */
    int dll_insert_at_back(dllistptr, void*, void* (*)(void*));
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
   int dll_insert_at_front(dllistptr, void*, void* (*)(void*));
    /*
     * Function responsible for inserting an element into the list keeping the list
     * sorted by a comparison defined by the user with a function called issmaller
     * Elements are going to be presented in ascending order starting from the head
     * Return values:
     *      [*] On success,  0 is returned
     *      [*] On failure,  -1 is returned
     */
    int dll_insert_sorted(dllistptr, void*, int (* )( void*, void* ), 
                            void* (*)(void*));
    /*
    * Inserts the element `data` before the `key` element provided. If the key is 
    * not found -1 is returned.
    * Return values:
    *      [*]: On success, 0 is returned
    *      [*]: On error or `on key not found`, -1 is returned
    */
   int dll_insert_before(dllistptr, void*, void* (*)(void*), void*, 
           int (*)(void*, void*));
   /*
    * Inserts the element `data` after the `key` element provided. If the key is 
    * not found -1 is returned.
    * Return values:
    *      [*]: On success, 0 is returned
    *      [*]: On error or `on key not found`, -1 is returned
    */
   int dll_insert_after(dllistptr, void*, void* (*)(void*),
           void*, int (*)(void*, void*));
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
    void* dll_edit_data(dllistptr, void*, int (*)(void*, void*));
    /*
    * Function that returns a copy of the data located at the front (Head) of 
    * the list
    */ 
    void* dll_get_front(dllistptr, void* (*)(void*));
    /*
    * Function that returns a copy of the data located at the back (Tail) of 
    * the list
    */ 
    void* dll_get_back(dllistptr, void* (*)(void*));
    /*
    * Function responsible for appending `list b` to `list a`
    * Upon return, the second list pointer (a.k.a. dllistptr) is going to be freed
    * and nullified, so that it cannot longer be used
    */
    void dll_append(dllistptr, dllistptr*);
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
    int dll_delete(dllistptr, void*, int (*)(void*, void*), void (*)(void*));
    /*
    * Deletes the tail element of the list
    */
    void dll_delete_back(dllistptr, void (*)(void*));
    /*
     * Deletes the head element of the list
     */
    void dll_delete_front(dllistptr, void (*)(void*));
    /*
     * Function responsible for freeing all the allocated memory
     */
    void dll_destroy(dllistptr*, void (*)(void*));


#ifdef	__cplusplus
}
#endif

#endif	/* DOUBLYLINKEDLIST_ADT_H */

