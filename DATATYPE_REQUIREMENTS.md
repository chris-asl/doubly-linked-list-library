#Doubly Linked List C-API#
###Requirements for the data type (with an example *int-type wrapper*) 
Bellow are simply some pointers on how to define your datatype.  

Define a struct `Datatype_int` into the header file and type-define a pointer to that struct (as shown below)
  
```
typedef struct Datatype_int *Data_int;  
struct Datatype_int  
{ int num; };
```
You have to implement functions with *these exact argument types and return values* along with your datatype (**where you see `int` replace with your type**, i.e. `Data_mytype allocate_datatype_mytype(void);` )

1. `Data_int allocate_datatype_int(void);`   
    <blockquote>
    <blockquote> Allocates a new Data_int object</blockquote>  

    **Return values**  
    - Upon successful allocation, the object is returned  
    - On error, NULL must be returned.  
    </blockquote>  

2. `void* duplicate_datatype_int(void* data);`  
    <blockquote>
    <blockquote> Allocates a new `Data_int` object (that is an exact copy/replica of the given one)</blockquote>  

    **Arguments**  
        *@data*: The object that will be copied (type: pointer to struct `Data_int`, generic pointer (a.k.a. `void*` must be used))  
    **Return values**  
    - Upon successful allocation, the duplicate object is returned  
    - If something went wrong, NULL must be returned.  
    </blockquote>  
  
3. `void free_datatype_int(void* dataptr);`  
    <blockquote>
    <blockquote> Responsible for freeing the Data_int object pointed by the `dataptr` pointer. It is a good practice to *nullify* the pointer afterwards.</blockquote>   
    
    **Arguments**  
        *@dataptr*: Pointer to a pointer to a struct (pointer to `Data_int`) 
    </blockquote>  
  
4. `void print_int(void* data);`
    <blockquote>
    <blockquote> Provide a representation for your data (*a new line character is added by dll_print function after the call to your print function*)</blockquote>  

    **Arguments**  
        *@data*: Pointer to your struct (`Data_int`)  
    </blockquote>  
    
5. `int issmaller_int(void* current, void* given);`
    <blockquote>
    <blockquote> Checks if the current element is smaller than the given one</blockquote>  

    **Arguments**  
        *@current, @given*: Both parameters are of type pointer to struct (`Data_int`)  
    **Return values (this must be the exact behavior)**
    - (current < given), 1 is returned
    - (current >= given), 0 is returned  
    </blockquote>  
  
6. `int is_equal_int(void* data, void* key);`
    <blockquote>
    <blockquote> Checks if `vdata` object is equal to the `vkey` object</blockquote>  

    **Arguments**  
        *@data, @key*: Pointer to your struct (Data_int)  
    **Return values**
    - If the objects are equal, 1 is returned
    - else, 0 is returned
    </blockquote>  
