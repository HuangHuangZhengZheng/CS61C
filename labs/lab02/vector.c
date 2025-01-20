/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
    /** 
    * v 是一个局部变量，当 bad_vector_new 函数返回后，v 的生命周期结束，其内存将不再有效。
    * 因此，返回的指针 retval 将指向一个已释放的内存区域，这会导致未定义行为。
    */
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new() {
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v;
    /** 
    * 返回局部变量：同样，v 是一个局部变量，当函数结束时，它的内存将被释放。返回该变量会导致调用者获得一个无效的结构体副本，无法安全使用。
    * 内存管理不当：虽然分配了 data 的内存，但在返回后，这个指针仍然有效，但它的生命周期与结构体 v 的生命周期相同，因此很容易导致内存泄漏或访问错误。
    */
}

/* Create a new vector with a size (length) of 1
   and set its single component to zero... the
   RIGHT WAY */
vector_t *vector_new() {
    /* Declare what this function will return */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    retval = malloc(sizeof(vector_t));/* YOUR CODE HERE */

    /* Check our return value to make sure we got memory */
    if (/* YOUR CODE HERE */!retval) {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    retval->size = 1 /* YOUR CODE HERE */;
    retval->data = malloc(sizeof(int))/* YOUR CODE HERE */;

    /* Check the data attribute of our vector to make sure we got memory */
    if (/* YOUR CODE HERE */!retval->data) {
        free(retval);				//Why is this line necessary?
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    /* YOUR CODE HERE */retval->data[0] = 0;

    /* and return... */
    return retval;
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    if (loc < /* YOUR CODE HERE */v->size) {
        return /* YOUR CODE HERE */v->data[loc];
    } else {
        return 0;
    }
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) {
    /* YOUR SOLUTION HERE */
    if (v) {
        free(v->data);
        free(v);
    }
}

/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */

    /* YOUR SOLUTION HERE */
    if (v == NULL) {
        fprintf(stderr, "vector_set: passed a NULL vector.\n");
        abort();
    }

    // If loc is greater than or equal to current size, resize the array
    if (loc >= v->size) {
        // Resize logic: Allocate new memory for larger array
        size_t new_size = loc + 1; // New size should be loc + 1
        int *new_data = realloc(v->data, new_size * sizeof(int)); // 数据保持：如果新分配的内存比原来的大，原有的数据会被保留；如果比原来的小，则仅保留前面部分的数据。
        
        if (!new_data) {
            allocation_failed(); // Handle allocation failure
        }

        // Initialize new elements to 0
        for (size_t i = v->size; i < new_size; i++) {
            new_data[i] = 0; // Set newly allocated space to 0
        }

        v->data = new_data; // Update pointer to new data
        v->size = new_size; // Update size of the vector
    }

    // Set the value at specified location
    v->data[loc] = value;    
}