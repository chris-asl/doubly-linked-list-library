#Doubly Linked List C-API :: Iterator Methods#
###The iterators methods are bellow: ###

 - iteratorRequest
 - iteratorDeleteAll
 - iteratorBegin
 - iteratorEnd
 - iteratorNext
 - iteratorPrev
 - iteratorCopy
 - iteratorDelete
 - iteratorGetObj
 - iteratorDeleteCurrentNode


The above names are the ones used in the API, all you need to do is prepend the _**dll**_ prefix (stands for *doubly linked list* ).  

For the distinction of the iterators an `IteratorID` type is used, which is simply an `int`.  

##Iterator Μethods Documentation  
This iterator-methods documentation breaks down into these sections:  
###[A - General methods (allocate(request), destroy)](#general-methods)  
###[B - Manipulate iterators (like next, begin, etc.)](#update-iter)  
###[C - Working with list elements (like get_object, delete current one)](#access-objects)  

##<a name="general-methods"></a>General methods
1. `IteratorID dll_iteratorRequest(List list);`
    <blockquote>
    <blockquote> Allocates a new Iterator object assigning it to the head of the list and then returning its id </blockquote>  

    **Arguments**  
    @list: The list in which the iterator will be added/allocated  
    **Return values**  
        - On success, the ID of the Iterator is returned    
        - On failure, -1 is returned  
    </blockquote> 

2. `int dll_iteratorDeleteAll(List list);`  
    <blockquote>
        <blockquote> 
            Deletes all the iterators 
        </blockquote>

    **Arguments**  
    *@list*: The list object  

    **Return values**  
        - On success, 0 is returned  
        - On failure, -1 is returned  
    </blockquote>

##<a name="update-iter"></a>Manipulate iterators
1. `int dll_iteratorBegin(List list, IteratorID iterID);`  
    <blockquote>
    <blockquote> Sets the iterator with ID iterID to point to the head of the list</blockquote>  

    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that will point to the head of the list  
    **Return values**:  
        - On success, 0 is returned  
        - On failure, -1 is returned  
    </blockquote>

2. `int dll_iteratorEnd(List list, IteratorID iterID);`  
    <blockquote>
    <blockquote> Sets the iterator with ID iterID to point to the tail of the list</blockquote>  

    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that will point to the tail of the list  
    **Return values**:  
        - On success, 0 is returned  
        - On failure, -1 is returned  
    </blockquote>



3. `int dll_iteratorNext(List list, IteratorID iterID);`  
    <blockquote>
    <blockquote> Sets the iterator to the next node  
     If by advancing, the iterator is requested to point after the tail of the list, 2 is returned**
    </blockquote>
    
    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that will be set to point to the next node   
    **Return values**  
            - On success, 0 is returned
            - On failure, -1 is returned
            - On empty list, 1 is returned to indicate invalidation of iterators
            - On the case described above, 2 is returned
    </blockquote>

4. `int dll_iteratorPrev(List list, IteratorID iterID);`  
    <blockquote>
    <blockquote> Sets the iterator to the previous node  
     If by requesting the previous node, the iterator points before the head of the list, 2 is returned**
    </blockquote>
    
    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that will be set to point to the next node   
    **Return values**  
            - On success, 0 is returned
            - On failure, -1 is returned
            - On empty list, 1 is returned to indicate invalidation of iterators
            - On the case described above, 2 is returned
    </blockquote>

5. `int dll_iteratorCopy(List list, const IteratorID src, IteratorID* dest);`  
    <blockquote>
        <blockquote> 
            *Acts both as a copy constructor and copy function*  
            **When you need copy constructor functionality**, dest IteratorID must be   
            NULL, and this function will allocate a new iterator, setting it   
            to point to the node that src Iterator points  
            **When you need simple copy functionality**, the function will copy the  
            address of the node that src Iterator points to the node of dest Iterator  
        </blockquote>

    **Arguments**  
    *@list*: The list object  
    *@src*: The iterator whose pointer-to a node, will be copied     
    *@dest*: The iterator that will be allocated (if set to NULL), and will set to point 
                    to the same node as the src iterator  

    **Return values**  
        - On success, 0 is returned  
        - On failure, -1 is returned  
        - On empty list, 1 is returned to indicate the invalidation of the iterators  
        - On iterator idx out of bounds error, 2 is returned
    </blockquote>

6. `int dll_iteratorDelete(List list, IteratorID iterID);`  
    <blockquote>
        <blockquote> 
            Deletes the iterator pointed by iterID and then invalidating the iterID
        </blockquote>

    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that will be removed from the iterators of the list  

    **Return values**  
        - On success, 0 is returned  
        - On failure, -1 is returned  
    </blockquote>

##<a name="access-objects"></a>Working with list elements
1. `void* dll_iteratorGetObj(List list, IteratorID iterID);`  
    <blockquote>
    <blockquote> Returns the object of the node that is pointed by the iterator</blockquote>

    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that points to the object whose data will be returned    
    **Return values**:  
        - On success, the object is returned  
        - On failure, NULL is returned  
    </blockquote>

2. `int dll_iteratorDeleteCurrentNode(List list, IteratorID iterID, void (*free_data)(void*))`  
    <blockquote>
        <blockquote> 
            Deletes the current node pointed by the iterator  
            After the deletion the iterator points to the next element of the list (towards the tail).   
            If the element to be destroyed is the last element of the list, which means that the list will be empty, all the iterators are 
            invalidated
        </blockquote>

    **Arguments**  
    *@list*: The list object  
    *@iterID*: The iterator that points to the node to be deleted  
    *@(\*free_data)*: Pointer to the free method of the provided datatype    

    **Return values**  
        - On success, 0 is returned  
        - On failure, -1 is returned  
        - On empty list, 1 is returned to indicate the invalidation of the iterators  
    </blockquote>





