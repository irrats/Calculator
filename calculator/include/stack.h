#pragma once

#include <stddef.h> /* size_t */

typedef struct stack stack_t; 


/* 
 * Description: allocates memory for stack_t whose size is defined by the user (by means of element_size and num_of_elements)
 * Paramaters: size of an element and number of elements
 * Return Value: pointer to the allocated memory
 * Errors/Fail/Undefined: NULL on fail
 * Time Complexity: O(1)
 */
stack_t *StackCreate(size_t element_size, size_t num_of_elements);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function frees the memory space pointed to by stack.
 * Paramaters: a stack_t pointer.
 * Return Value: Returns no value. 
 * Errors/Fail/Undefined: None
 * Time Complexity: O(1)
 */
void StackDestroy(stack_t *stack);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function adds an element to the top of the stack
 * Paramaters: stack_t * (stack) - pointer to the stack, const void * (data) - data to be pushed to the stack
 * Return Value: No
 * Errors/Fail/Undefined: Undefined behavior when stack_t is full
 * Time complexity: O(1)
 */
void StackPush(stack_t *stack, const void *data);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function removes last element from the given stack that is pointed to by stack
 * Paramaters: stack_t * (stack) - pointer to the stack
 * Return Value: returns no value
 * Errors/Fail/Undefined: None
 * Time complexity: O(1)
 */
void StackPop(stack_t *stack);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function provides the address of the top element on the stack 
 * Paramaters: stack_t * (stack) - pointer to the stack
 * Return Value: pointer to the top element on the stack
 * Errors/Fail/Undefined: returns NULL if stack doesn't exist or empty
 * Time complexity: O(1)
 */
void *StackPeek(const stack_t *stack);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function to check whether the stack is empty or not
 * Paramaters: const stack_t * (stack) - pointer to the stack
 * Return Value: 1 if stack is empty, and 0 if not
 * Errors/Fail/Undefined: None
 * Time complexity: O(1)
 */
int StackIsEmpty(const stack_t *stack);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: function returns current amount of elements in the stack
 * Paramaters: const stack_t * (stack) - pointer to the stack
 * Return Value: size_t number of current elements in the stack
 * Errors/Fail/Undefined: None
 * Time complexity: O(1)
 */
size_t StackSize(const stack_t *stack);

/*_____________________________________________________________________________________________________________*/

/* 
 * Description: Returns the maximum number of elements (as size_t) that the stack can contain. This number is initially provided by the user on creation of a new stack instance. 
 * Paramaters: const stack_t * (stack) - pointer to the stack
 * Return Value: A size_t representation of the maximum amount of elements the stack can support.
 * Errors/Fail/Undefined: If the parameter passed points to an empty stack or the pointer is invalid/NULL, return zero;
 * Time complexity: O(1)
 */
size_t StackCapacity(const stack_t *stack);






