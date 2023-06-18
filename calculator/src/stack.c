#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "stack.h"

struct stack
{
	size_t n_memb;
	size_t size_el;
	size_t top_el;
	void *data_el;
};


stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	stack_t *stack_ptr = (stack_t*)malloc(sizeof(stack_t));
	if (NULL != stack_ptr)
	{
		stack_ptr -> data_el = malloc(element_size * num_of_elements);
		if (NULL != stack_ptr->data_el)
		{
			stack_ptr -> n_memb = num_of_elements;
			stack_ptr -> size_el = element_size;
			stack_ptr -> top_el = 0;
		}
		else
		{
			free(stack_ptr);
			stack_ptr = NULL;
		}
	}
	return stack_ptr;
}


void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	memcpy((char*)stack->data_el + stack->size_el * stack->top_el, data, stack->size_el);
	++stack->top_el;

}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	--stack->top_el;

}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	return (char*)stack-> data_el + stack->size_el * (stack->top_el - 1) ; 
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return !(stack->top_el);
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->top_el;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->n_memb;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack -> data_el );
	stack -> data_el = NULL;
	free(stack);
	stack = NULL;
}

