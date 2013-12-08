/* 
 * File:   data_type.h
 * Author: chris
 *
 * Created on May 8, 2013, 11:13 AM
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
        int datum;
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

