#include <stdlib.h> /* malloc, realloc, free, strtod */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen*/
#include <ctype.h> /* isdigit() */
#include <math.h> /*pow() func */

#include "stack.h"

#define SC1 {{INVALID_SYMBOL, ERROR}, {END_SYMBOL, ERROR},\
	    {OPERAND, OPERAND_INPUT}, {OPERATOR, ERROR},\
	    {OPEN_PARAN, OPERATOR_INPUT}, {CLOSE_PARAN, ERROR},\
	    {MINUS, MINUS_INPUT}}}

#define SC2 {{INVALID_SYMBOL, ERROR}, {END_SYMBOL, CALCULATE},\
	    {OPERAND, ERROR}, {OPERATOR, OPERATOR_INPUT},\
	    {OPEN_PARAN, ERROR}, {CLOSE_PARAN, C_PARAN_INPUT},\
	    {MINUS, OPERATOR_INPUT}}}
#define STATECOUNT 7

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

enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};

enum symbol
{
    INVALID_SYMBOL = 0,
    END_SYMBOL,
    OPERAND,
    OPERATOR,
    OPEN_PARAN,
    CLOSE_PARAN,
    MINUS
};

typedef enum
{
    SYMBOL_EVAL = 0,
    OPERAND_INPUT,
    OPERATOR_INPUT,
    MINUS_INPUT,
    C_PARAN_INPUT,
    CALCULATE,
    ERROR
}state_t;

struct op_s {
	char op;
	int prec;
	int assoc;
	status_t (*handler)(double first, double second, double *out);
};

typedef struct op_s op_s_t;


typedef struct statechange
{
    const int in;
    const state_t out;

}st_change_t;


typedef struct FSM
{
    const state_t state;
    status_t (*Action)(double *out, stack_t *values, stack_t *operators);
    const st_change_t new_state[STATECOUNT];
} fsm_t;

/************* STATIC FUNCTIONS *******************/
status_t div_status_arr[2] = {SUCCESS, ILLEGAL_OPERATION};
static double multiplicator = -1;
static char mult = '*';
static char *curr_token;

static int GetNum(char a)
{
	a = (a == 0) +
	(a >= '0' && a <= '9') * 2 +
	((a == '*') || (a == '+') || (a == '^') || (a == '/') ) * 3 +
	(a == '(') * 4 +
	(a == ')') * 5 +
	(a == '-') * 6;

	return a;
}
/*
static status_t ReadSymbol(double *out, stack_t *values, stack_t *operators);
*/
static status_t PushNumber(double *out, stack_t *values, stack_t *operators);
static status_t HandleOp(double *out, stack_t *values, stack_t *operators);
static status_t HandlePar(double *out, stack_t *values, stack_t *operators);
static status_t UnaryOp(double *out, stack_t *values, stack_t *operators);
static status_t ErFunc(double *out, stack_t *values, stack_t *operators);
static status_t OneCalculation(double *out, stack_t *values, stack_t *operators);

static void FinalCheck(status_t *status, double *out, stack_t *values, stack_t *operators);
static op_s_t *GetOp(char ch);
static void SkipWhiteSpaces(char *str);

static status_t MultNum(double first, double second, double *out);
static status_t AddNum(double first, double second, double *out);
static status_t SubNum(double first, double second, double *out);
static status_t DivNum(double first, double second, double *out);
static status_t PowNum(double first, double second, double *out);
static status_t Dummy(double first, double second, double *out);

/************** VARIOUS TABLES **********************/

op_s_t ops[]={
	{'(', 0, ASSOC_NONE, Dummy},
	{')', 0, ASSOC_NONE, Dummy},
	{'^', 1, ASSOC_RIGHT, PowNum},
	{'*', 2, ASSOC_LEFT, MultNum},
	{'+', 3, ASSOC_LEFT, AddNum},
	{'-', 3, ASSOC_LEFT, SubNum},
	{'/', 2, ASSOC_LEFT, DivNum},
	{0,  10, ASSOC_NONE, Dummy}
};

fsm_t fsm[] =
   {
        {SYMBOL_EVAL, NULL,       SC1,
        {OPERAND_INPUT, PushNumber,     SC2,
        {OPERATOR_INPUT, HandleOp, 	SC1,
        {MINUS_INPUT, UnaryOp, 		SC1,
        {C_PARAN_INPUT, HandlePar, 	SC2,
        {CALCULATE, HandleOp, {{-1, SYMBOL_EVAL}}},
        {ERROR, ErFunc, {{-1, ERROR}}}
    };

/************* API FUNCTIONS *******************/

status_t Calculate(const char *exp, double *out)
{
	size_t size = strlen(exp);
	int num = 0;
	char dummy_op = '\0';

	status_t status = SUCCESS;
	state_t state = SYMBOL_EVAL;

	stack_t *values = NULL;
	stack_t *operators = NULL;

	curr_token = (char*)exp;

	assert(NULL != exp);
	assert(NULL != out);

	values = StackCreate(sizeof(double), size);
	operators = StackCreate(sizeof(char), size);

	if (NULL == values || NULL == operators )
	{
		free(values);
		return MALLOC_ERR;
	}

	StackPush(operators, &dummy_op);

	while(status == SUCCESS && state != ERROR && state != CALCULATE)
	{
		SkipWhiteSpaces(curr_token);
		num = GetNum(*curr_token);
		state = fsm[state].new_state[num].out;
		status = fsm[state].Action(out, values, operators);
	}

	FinalCheck(&status, out, values, operators);

	StackDestroy(values);
	StackDestroy(operators);

	return status;
}

/************* STATIC FUNCTIONS DEFINITION***********/

static status_t PushNumber(double *out, stack_t *values, stack_t *operators)
{
	double val = 0;
	char *ptr = NULL;
	(void)operators;
	(void)out;

	val = strtod(curr_token, &ptr);
	curr_token = ptr;

	StackPush(values, &val);

	return SUCCESS;
}

static status_t HandleOp(double *out, stack_t *values, stack_t *operators)
{
	status_t status = SUCCESS;
	char curr_op = 0;
	char top_op = 0;

	curr_op = *(curr_token);
	top_op = *(char*)StackPeek(operators);

	while( (top_op != 0 && GetOp(top_op)->prec < GetOp(curr_op)->prec
		&& status == SUCCESS && top_op != '(')
		|| ( GetOp(top_op)->assoc == GetOp(curr_op)->assoc && GetOp(top_op)->prec == ops[6].prec
		      && status == SUCCESS)
		|| (GetOp(top_op)->prec ==  GetOp(curr_op)->prec &&  GetOp(curr_op)->prec == 3 ) )
	{
		status = OneCalculation(out, values, operators);
		top_op = *(char*)StackPeek(operators);

	}
	StackPush(operators, &curr_op);

	++curr_token;

	return status;
}

static status_t HandlePar(double *out, stack_t *values, stack_t *operators)
{
	status_t status = SUCCESS;
	char top_op = *(char*)StackPeek(operators);

	while( top_op != '(' && top_op != 0)
	{
		status = OneCalculation(out, values, operators);
		top_op = *(char*)StackPeek(operators);
	}

	*out *= (top_op != 0);
	StackPop(operators);
	++curr_token;

	return ((status == SUCCESS) ? (top_op == 0)*SYNTAX_ERR : status) ;
}

static status_t UnaryOp(double *out, stack_t *values, stack_t *operators)
{
	(void)out;
	StackPush(values, &multiplicator);
	StackPush(operators, &mult);
	++curr_token;

	return SUCCESS;
}

static status_t ErFunc(double *out, stack_t *values, stack_t *operators)
{
	*out = 0;
	(void)values;
	(void)operators;
	return SYNTAX_ERR;
}

static void SkipWhiteSpaces()
{
	for ( ;*(curr_token)== ' '; ++curr_token)
	{
		/* empty body */
	}
}

static status_t OneCalculation(double *out, stack_t *values, stack_t *operators)
{
	status_t status = SUCCESS;
	char top_op = 0 ;
	double first_operand = 0;
	double second_operand = 0;

	assert(NULL != values);
	assert(NULL != operators);
	assert(NULL != out);

	top_op = *(char*)StackPeek(operators);
	StackPop(operators);
	second_operand = *(double*)StackPeek(values);
	StackPop(values);
	first_operand = *(double*)StackPeek(values);
	StackPop(values);

	status = GetOp(top_op)->handler(first_operand, second_operand, out);

	StackPush(values, out);

	return status;
}

static void FinalCheck(status_t *status, double *out, stack_t *values, stack_t *operators)
{
	assert(NULL != status);
	assert(NULL != out);
	assert(NULL != values);

	StackPop(values);
	StackPop(operators);
	while(*status == SUCCESS && (!StackIsEmpty(values) || *(char*)StackPeek(operators) != '\0' ))
	{
		*status = SYNTAX_ERR;
		*out = 0;
	}
}

static op_s_t *GetOp(char ch)
{
	size_t i = 0;
	for ( ;ops[i].op != ch && i < 8; ++i)
	{
		/* empty body*/
	}
	return ops+i;
}

static status_t MultNum(double first, double second, double *out)
{
	*out = first * second;
	assert(NULL != out);

	return SUCCESS;
}

static status_t AddNum(double first, double second, double *out)
{
	*out = first + second;
	assert(NULL != out);

	return SUCCESS;
}

static status_t SubNum(double first, double second, double *out)
{
	*out = first - second;
	assert(NULL != out);

	return SUCCESS;
}

static status_t DivNum(double first, double second, double *out)
{
	status_t status = SUCCESS;
	assert(NULL != out);

	status = div_status_arr[second == 0];
	*out = !(second==0) * first / ((second==0) + second);

	return status;
}

static status_t PowNum(double first, double second, double *out)
{
	status_t status = SUCCESS;
	double digit = 0;
	assert(NULL != out);

	status = div_status_arr[first == 0 && second < 0];
	digit = (first==0 && second < 0);
	*out = !digit * pow(digit + first, second);

	return status;
}

static status_t Dummy(double first, double second, double *out)
{
	(void)first;
	(void)second;
	(void)out;

	return SUCCESS;
}
