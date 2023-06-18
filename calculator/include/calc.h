#pragma once

enum status {
	SUCCESS = 0,
	SYNTAX_ERR,
	ILLEGAL_OPERATION,
	MALLOC_ERR,
	STACK_OVERFLOW,
	DOUBLE_OVERFLOW,
	DOUBLE_UNDERFLOW
	/* ... */
};

typedef enum status status_t;

/*
* Description: The function calculate mathematical expression @exp and write answer to @out.
* Parameters: 
*  @exp is an mathematical expression 
*  @out result of calculation (memory pointed by @out should be allocated)
* Return: @status_t, that is 0 on success
* Complexity: 
*	 BC: O(n)
*    WC: O(n^m)
*    AVR: O(n)
*    Space: O(n)
*/
status_t Calculate(const char *exp, double *out);