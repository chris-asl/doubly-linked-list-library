#Doubly Linked List C-API :: Core API#
###The Core API provides these functions: ###

 - init
 - size
 - isempty
 - print
 - insert_at_back
 - insert_at_front
 - insert_sorted
 - insert_before
 - insert_after
 - edit_data
 - get_front
 - get_back
 - append
 - delete
 - delete_front
 - delete_back
 - destroy

The above names are the ones used in the API, all you need to do is prepend the _**dll**_ prefix (stands for *doubly linked list* ).  

##Core API Μethods Documentation  
The API-methods documentation breaks down into these sections:  
###[A - General methods (like init, destroy, size, etc.)](#general-methods)  
###[B - Insert variants (like insert_at_back, insert_sorted, etc.)](#insert-variants)  
###[C - Accessing list elements (like get_front, search(edit_data) etc.)](#get-access)  
###[D - Deleting elements (like delete_back, find and delete(delete) etc.)](#delete-sth)  

####For the iterators, look [here](#ITER_METHODS.md)

##<a name="general-methods"></a>General methods
1. `int dll_init(list_t *listptr_addr)`
    <blockquote>
    <blockquote> Initiallizes the Doubly Linked List ADT</blockquote>  

    **Arguments**  
    @listptr_addr: Pointer to a List  
    **Return values**
    - If successful, 1 is returned  
    - On error, 0 is returned
    </blockquote> 

2. `int dll_size(list_t list)`  
    <blockquote>
    <blockquote> Accessor function for the size of the list</blockquote>  

    **Arguments**  
    *@list*: Your list  
    **Return values**:
    - Returns the size of the list
    </blockquote>

3. `int dll_isempty(list_t list)`  
    <blockquote>
    <blockquote> Checking if the list is empty</blockquote>  

    **Arguments**  
    @list: Your list  
    **Return values**:  
    - On empty list, 1 is returned
    - else, 0 is returned
    </blockquote>

4. `void dll_print(const list_t list, void (*print_data)(void* data), int print_inline)`  
    <blockquote>
    <blockquote> Prints the list elements inline or separating them with a new line</blockquote>

    **Arguments**  
    @list: Your list  
    @(*print_data)(void* data): Pointer to a function repsonsible for printing your element  
    @print_inline: boolean-like variable, 1 indicates that you want the elements to be printed in this fashion `element -> element -> element`, while passing 0, will print them like this:  

         -> element1  
         -> element2    
         -> element3  
    </blockquote>

5. `int dll_copy(list_t src, list_t dest, void* (*duplicate)(void*), 
        void (*free_data)(void*)) `  
    <blockquote>
    <blockquote> Function that is responsible for copying src list to dest list.   
    **Destination list, must be initialized and empty**
    </blockquote>
    
    **Arguments**  
    @src: The source list, whose elements will be copied   
    @dest: The destination list  
    @(\*duplicate): pointer to the function responsible for duplicating the datatype, *more info [here](DATATYPE_REQUIREMENTS.md)*  
    @(\*free_data): pointer to the function responsible for freeing the allocated memory from your datatype, *more info [here](DATATYPE_REQUIREMENTS.md)*  

    **Return values**  
            - On success, 0 is returned
            - On failure, -1 is returned
            - On destination list not empty, 2 is returned  
            - On empty source list, 1 is returned  
    </blockquote>

6. `void dll_append(list_t alist, list_t* listptrb)`  
    <blockquote>
    <blockquote> Appends list B at the end of list A. Also, listptrb is NULL upon return</blockquote>
    
    **Arguments**  
    @alist: Plain old list   
    @listptrb: Pointer to a list  
    </blockquote>

7. `void dll_destroy(list_t *dllptr_addr, void (*free_data)(void* data))`  
    <blockquote>
    <blockquote> Deallocates the memory used by the list. Also, upon return dllptr_addr (pointer to your list) is NULL.</blockquote>

    **Arguments**  
    @dllptr_addr: Pointer to your list  
    @(\*free_data)(void\*): Pointer to a function for freeing the allocated memory of your type
    </blockquote>

##<a name="insert-variants"></a>Insert variants
1. `int dll_insert_at_back(list_t list, void* data, void* (*duplicate)(void*))`  
    <blockquote>
    <blockquote> Insert the element data to the back of the list </blockquote>

    <a name="insert-function-args"></a>**Arguments**  
    @list: Your list  
    @data: Pointer to your Data_type struct (`Data_int` in the included example)  
    @(*duplicate)(void*): Pointer to a function that returns an exact replica of the `data` object  
    **Return values**  
        - On success, 0 is returned
        - On failure, -1 is returned
    </blockquote>

2. `int dll_insert_at_front(list_t list, void* data, void* (*duplicate)(void*))`
    <blockquote>
    <blockquote> Insert the element data to the front of the list</blockquote>  

    Arguments and return values, same as [here](#insert-function-args).
    </blockquote>

3. `int dll_insert_sorted(list_t list, void* data, int (*issmaller)(void*, void*), void* (*duplicate)(void*))`  
    <blockquote>
    <blockquote> Inserts the element data to the list while keeping it sorted</blockquote>

    Arguments and return values, same as [here](#insert-function-args), with the addition of:  
    @(\*issmaller)(void\*,void\*): Pointer to a function acting as a binary predicate to check if an elemen is smaller than the other  
    </blockquote>

4. `int dll_insert_before(list_t list, void* data, void* (*duplicate)(void*), void* key, int (*is_equal)(void*, void*))`  
    <blockquote>
    <blockquote> Insert the element data, before the element key in the list, if the key is not found then -1 is returned</blockquote>

    <a name="insert-before-after"></a>Arguments and return values, same as [here](#insert-function-args), with the addition of:  
    @key: Element that is used to find the spot for the element  
    @(\*is_equal)(void\*, void\*): Pointer to a function that checks if two elements are eaual  
    </blockquote>

5. `int dll_insert_after(list_t list, void* data, void* (*duplicate)(void*), void* key, int (*is_equal)(void*, void*))`  
    <blockquote>
    <blockquote> Inserts the element data, after the element key in the list, if the key is not found then -1 is returned</blockquote>  

    Arguments and return values, same as above.
    </blockquote>

##<a name="get-access"></a>Getting data from the list
1. `void* dll_edit_data(list_t list, void* data, int (*is_equal)(void*, void*))`
    <blockquote>
    <blockquote> Gives you access to the `data` element in the list. You can prepare the element `data` to contain just a single member (which you want to be the key of the search) and implement the is_equal function to check that member only!</blockquote>

    **Arguments**  
    @list: Your list  
    @data: Pointer to a struct (`Data_int`) which is used in a search function as a key  
    @(\*is_equal)(void\*, void\*): Pointer to a function that is used for finding the element required  
    **Return values**  
      - If element is found, its address is returned
      - If not, NULL is returned
    </blockquote>
    
2. `void* dll_get_front(list_t list, void* (*duplicate)(void*))`  
    <blockquote>
    <blockquote> Returns the head element of the list</blockquote>  

    **Arguments**
    @list: Your list   
    @(*duplicate)(void*): Pointer to a function that returns an exact replica of the `data` object   
    </blockquote>
    
3. `void* dll_get_back(list_t list, void* (*duplicate)(void*))`  
    <blockquote>
    <blockquote> Returns the tail element of the list</blockquote>  

    **Arguments**
    @list: Your list   
    @(*duplicate)(void*): Pointer to a function that returns an exact replica of the `data` object   
    </blockquote>
    

##<a name="delete-sth"></a>Delete some element(s)
1. `int dll_delete(list_t list, void* key, int (*is_equal)(void*, void*), void (*free_data)(void*))`  
    <blockquote>
    <blockquote> Deletes the element pointed by the key. Again you can prepare only one member of the key element and write an `is_equal` function that uses only that member</blockquote>  

    **Arguments**  
    @list: Your list  
    @key: Element used as a key for the search  
    @(\*is_equal)(void\*, void\*): Pointer to a function (binary predicate) that checks equality of two elements  
    @(\*free_data)(void\*): Pointer to a function that deallocates the space allocated by the element

     **Return values**  
      - On success, 0 is returned
      - On element not found, 1 is returned
      - On error, -1 is returned
    </blockquote>
    
2. `void dll_delete_back(list_t list, void (*free_data)(void* data))`  
    <blockquote>
    <blockquote> Deletes the tail element of the list</blockquote>

    Arguments are as described above
    </blockquote>
    
3. `void dll_delete_front(list_t list, void (*free_data)(void* data))`  
    <blockquote>
    <blockquote> Deletes the head element of the list</blockquote>

    Arguments are as described above
    </blockquote>
    

    
