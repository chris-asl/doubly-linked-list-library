/* 
 *  Project: Doubly Linked List C-API, example data type
 *  File:   data_type.h
 *  Author: Chris Aslanoglou
 *  Github: https://github.com/chris-asl/doubly-linked-list-API
 */

#ifndef DATA_TYPE_H
#define	DATA_TYPE_H

#ifdef	__cplusplus
extern "C"
{
#endif

    typedef struct Datatype_int *Data_int;
    struct Datatype_int
    {
        int num;
    };

    Data_int allocate_datatype_int(void);
    void* duplicate_datatype_int(void*);
    void free_datatype_int(void*);
    void print_int(void*);
    int issmaller_int(void*, void*);
    int is_equal_int(void*, void*);

#ifdef	__cplusplus
}
#endif

#endif	/* DATA_TYPE_H */

