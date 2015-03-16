#Doubly Linked List C-API#
A doubly linked list C-API that can accept any data type that is wrapped within a struct and provides a set of requested methods.  
It is implemented with opaque pointers for abstraction and security. 

## Introducing version 2.1 - Iterators
**A brief changelog**  
1. Added support for iterators (look below for more info)  
2. Changed ugly `dllistptr` to a more [user and C]-friendly naming convention, that is `list_t` (**important**)  
3. Renamed the API files to a more C-like naming convention, like this: `doubly_linked_list_adt.c/h`  
4. Updated demo to include some of the iterator functionality  
5. This version was extensively tested with a multithreaded project, that used the list with about 10 datatypes  
6. Added a copy-constructor-like method to copy lists  
7. Binary search to access find the associated element in the list of iterators  
8. *In big programs, compile with -O2 or -O3 to see the magic*

## Changelog
~~~
[*] 2.1 - Upgraded search/ access of iterators (from linear to binary search)
[*] 2.0 - Iterators support
[*] 1.0 - Initial release
~~~

##Getting started with the API
1. You will need to copy the `doubly_linked_list_adt.c` and `doubly_linked_list_adt.h` files  to your project and include the header file to your source code
2. Implement the required functions for the API, stated [**here**](DATATYPE_REQUIREMENTS.md), in a source file and provide the prototypes in a header file
3. To use a list, declare a `list_t` variable and pass it to `dll_init` function
4. Declare and prepare a *Datatype* dummy variable, allocate it with your function and call any of the `dll_insert*` variants (depending on your needs) 

    > **N.B.:** To add other elements to the list, **don't allocate an object again**, just update the previous one to insert it

5. When you're done with your list, only then you call the *free_datatype* function you've written  
6. Finally, pass the `list_t` variable to `dll_destroy` function to deallocate the memory needed


##Documentation for each aspect of the project can be found here
- [**Core API**](API_METHODS.md)
- [**Iterators API**](ITER_METHODS.md)
- [**Datatype requirements**](DATATYPE_REQUIREMENTS.md)

---
**For anything you might need, suggestion, bug report, create a new issue or a pull-request**
