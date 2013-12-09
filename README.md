#Doubly Linked List C-API#
A doubly linked list C-API that can accept any data type that is wrapped within a struct and provides a set of requested methods.  
It is implemented with opaque pointers for abstraction and security. 

###Getting started with the API
1. You will need to copy the `DoublyLinkedList_ADT.c` and `DoublyLinkedList_ADT.h` files  to your project and include the header file to your source code
2. Implement the required functions for the API, stated [**here**](#requirements-for-the-data-type), in a source file and provide the prototypes in a header file
3. To use a list, declare a `dllistptr` variable and pass it to `dll_init` function
4. Declare and prepare a *Datatype* dummy variable, allocate it with your function and call any of the `dll_insert*` variants (depending on your needs)  


 > **N.B.:** To add other elements to the list, **don't allocate an object again**, just prepare the previous one to insert it
5. When you're done with your list, only then you call the *free_datatype* function you've written  
6. Finally, pass the dllistptr variable to `dll_destroy` function to deallocate the memory needed


---
###The API provides these functions: ###

 - init
 - size
 - isempty
 - print
 - insert_at_back
 - insert_at_front
 - insert_sorted
 - insert_before
 - insert_after
 - get_data
 - get_front
 - get_back
 - append
 - delete
 - delete_front
 - delete_back
 - destroy

The above names are the ones used in the API, all you need to do is prepend the _**dll**_ prefix (stands for *doubly linked list* ).  

---
###<a name="requirements-for-the-data-type"></a>Requirements for the data type###
####(with an example *int-type wrapper*) 
 - We have to define a struct `Datatype_int` into the header file and type-define a pointer to that struct (as shown below)
  
```
typedef struct Datatype_int *Data_int;  
struct Datatype_int  
{ int num; };
```
 - You have to implement functions with *these exact argument types and return values* along with your datatype (**where you see `int` replace with your type**, i.e. `Data_mytype allocate_datatype_mytype(void);` )

    1. `Data_int allocate_datatype_int(void);`   
    
      > Allocates a new Data_int object  

      **Return values**  
      - Upon successful allocation, the object is returned  
      - On error, NULL must be returned.  

    2. `void* duplicate_datatype_int(void* data);`  
    
      > Allocates a new `Data_int` object (that is an exact copy/replica of the given one)  

      **Arguments**  
          *@data*: The object that will be copied (type: pointer to struct `Data_int`, generic pointer (a.k.a. `void*` must be used))  
      **Return values**  
      - Upon successful allocation, the duplicate object is returned  
      - If something went wrong, NULL must be returned.  
   
    3. `void free_datatype_int(void* dataptr);`  
    
      > Responsible for freeing the Data_int object pointed by the `dataptr` pointer. It is a good practice to *nullify* the pointer afterwards.   
      
      **Arguments**  
          *@dataptr*: Pointer to a pointer to a struct (pointer to `Data_int`) 
    
    4. `void print_int(void* data);`
    
      > Provide a representation for your data (*a new line character is added by dll_print function after the call to your print function*)  
  
      **Arguments**  
          *@data*: Pointer to your struct (`Data_int`)  
        
    5. `int issmaller_int(void* current, void* given);`
    
      > Checks if the current element is smaller than the given one  
  
      **Arguments**  
          *@current, @given*: Both parameters are of type pointer to struct (`Data_int`)  
      **Return values (this must be the exact behavior)**
      - (current < given), 1 is returned
      - (current >= given), 0 is returned  
    
    6. `int is_equal_int(void* data, void* key);`
    
      > Checks if `vdata` object is equal to the `vkey` object  
  
      **Arguments**  
          *@data, @key*: Pointer to your struct (Data_int)  
      **Return values**
      - If the objects are equal, 1 is returned
      - else, 0 is returned
        
---
###API methods Documentation  
1. `int dll_init(dllistptr *listptr_addr)`
    > Initiallizes the Doubly Linked List ADT  

    **Arguments**  
    @listptr_addr: Pointer to a dllistptr  
    **Return values**
    - If successful, 1 is returned
    - On error, 0 is returned

2. `int dll_size(dllistptr list)`  
    > Accessor function for the size of the list  

    **Arguments**  
    *@list*: Your list  
    **Return values**:
    - Returns the size of the list

3. `int dll_isempty(dllistptr list)`  
    > Checking if the list is empty  

    **Arguments**  
    @list: Your list  
    **Return values**:  
    - On empty list, 1 is returned
    - else, 0 is returned

4. `void dll_print(const dllistptr list, void (*print_data)(void* data), int print_inline)`  
    > Prints the list elements inline or separating them with a new line

    **Arguments**  
    @list: Your list  
    @(*print_data)(void* data): Pointer to a function repsonsible for printing your element  
    @print_inline: boolean-like variable, 1 indicates that you want the elements to be printed in this fashion `element -> element -> element`, while passing 0, will print them like this:  
```
-> element
-> element  
-> element
```

5. `int dll_insert_at_back(dllistptr list, void* data, void* (*duplicate)(void*))`  
    > Insert the element data to the back of the list 

    <a name="insert-function-args"></a>**Arguments**  
    @list: Your list  
    @data: Pointer to your Data_type struct (`Data_int` in the included example)  
    @(*duplicate)(void*): Pointer to a function that returns an exact replica of the `data` object  
    **Return values**  
        - On success, 0 is returned
        - On failure, -1 is returned

6. `int dll_insert_at_front(dllistptr list, void* data, void* (*duplicate)(void*))`
    > Insert the element data to the front of the list  

    Arguments and return values, same as [here](#insert-function-args).
    
7. `int dll_insert_sorted(dllistptr list, void* data, int (*issmaller)(void*, void*), void* (*duplicate)(void*))`  
    > Inserts the element data to the list while keeping it sorted

    Arguments and return values, same as [here](#insert-function-args), with the addition of:  
    @(\*issmaller)(void\*,void\*): Pointer to a function acting as a binary predicate to check if an elemen is smaller than the other  
    
8. `int dll_insert_before(dllistptr list, void* data, void* (*duplicate)(void*), void* key, int (*is_equal)(void*, void*))`  
    > Insert the element data, before the element key in the list, if the key is not found then -1 is returned

    <a name="insert-before-after"></a>Arguments and return values, same as [here](#insert-function-args), with the addition of:  
    @key: Element that is used to find the spot for the element  
    @(\*is_equal)(void\*, void\*): Pointer to a function that checks if two elements are eaual  
    
9. `int dll_insert_after(dllistptr list, void* data, void* (*duplicate)(void*), void* key, int (*is_equal)(void*, void*))`  
    > Inserts the element data, after the element key in the list, if the key is not found then -1 is returned  

    Arguments and return values, same as above.
    
10. `void* dll_get_data(dllistptr list, void* key, int (*is_equal)(void*, void*))`
    > 
    



---

