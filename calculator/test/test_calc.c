#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "calc.h"
#include "tests.h"

void TestOperators();
void TestExpression();
void TestSyntaxError();
void TestIllegalOperation();


int main(void)
{
    TestOperators();
    TestExpression();
    TestSyntaxError();
    TestIllegalOperation();
    PASS;
    return 0;
}

void TestOperators()
{
    status_t status = SUCCESS;
    char *exp = NULL;
    double res = 0.0;

    exp = "3 - 2";
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #1", res, 1);
    TEST("Outcome of function #1", status, SUCCESS);

	exp = "2 - 302";
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #2", res, -300);
    TEST("Outcome of function #2", status, SUCCESS);

	exp = "3*2";
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #3", res, 6);
    TEST("Outcome of function #3", status, SUCCESS);
	
	exp = "8/2";
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #4", res, 4);
    TEST("Outcome of function #4", status, SUCCESS);
	
	exp = "2^4";
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #5", res, 16);
    TEST("Outcome of function #5", status, SUCCESS);

	exp = "2 ^ 2 ^ 3";	
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #6", res, 256);
    TEST("Outcome of function #6", status, SUCCESS);
	
	exp =  "3 + 230 / 10";	
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #7", res, 26);
    TEST("Outcome of function #7", status, SUCCESS);

	exp = "20 + 10 * 80 / 5";	
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #8", res, 180);
    TEST("Outcome of function #8", status, SUCCESS);
	
	exp = "110 + 2 ^ 4 / 8";	
	status = Calculate(exp, &res);
    TEST("Outcome of expression #9", res, (double)112.0);
    TEST("Outcome of function #9", status, SUCCESS);

	exp = "1 + 2^5 + 2";	
	status = Calculate(exp, &res);
    TEST("Outcome of expression #10", res, (double)35.0);
    TEST("Outcome of function #10", status, SUCCESS);
	
	exp = "2 * 8 + 40 / 10 - 6";	
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #11", res, 14);
    TEST("Outcome of function #11", status, SUCCESS);
	
	exp = "2 * 8 + 100 / 5 ^ 2 - 6";	
	status = Calculate(exp, &res);
    TEST_D("Outcome of expression #12", res, 14);
    TEST("Outcome of function #12", status, SUCCESS);

	exp = "2^3^2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #13", res == 512, 1);
    TEST("Outcome of function #13", status, SUCCESS);

	exp = "5 - 1 + 2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #14", res, (double)6.0);
    TEST("Outcome of function #14", status, SUCCESS);

	exp = "5 + 1 - 2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #15", res, (double)4.0);
    TEST("Outcome of function #15", status, SUCCESS);

	exp = "2^2^3";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #16", res, (double)256.0);
    TEST("Outcome of function #16", status, SUCCESS);

	exp = "5 - 1 + 2 + 2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #17", res, (double)8.0);
    TEST("Outcome of function #17", status, SUCCESS);

	exp = "5 - -1 + 2 + 2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #18", res, (double)10.0);
    TEST("Outcome of function #18", status, SUCCESS);

    exp = "-3 + 1";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #19", res, (double)-2.0);
    TEST("Outcome of function #19", status, SUCCESS);

	exp = "5 + -2";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #20", res, (double)3.0);
    TEST("Outcome of function #20", status, SUCCESS);
	
	exp = "5 - -2";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #21", res, (double)7.0);
    TEST("Outcome of function #21", status, SUCCESS);

	exp = "5  ^ - 2";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #22", res, (double) 0.04);
    TEST("Outcome of function #22", status, SUCCESS);
	
	exp = "2 + (-2)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #23", res, (double)0.0);
    TEST("Outcome of function #23", status, SUCCESS);

   	exp = "2 *  4 * 5   - 7 + 1";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #24", res, (double)34.0);
    TEST("Outcome of function #24", status, SUCCESS);
	
    exp = "  2 ^ 2 ^ 3   - 7 + 1";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #25", res, (double)250.0);
    TEST("Outcome of function #25", status, SUCCESS);
	
    exp = "2 ^ 2 * 5   * 2 + 1"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #26", res, (double)41.0);
    TEST("Outcome of function #26", status, SUCCESS);
	
    exp = "4+2*2^2^3*2+1";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #27", res, (double)1029.0);
    TEST("Outcome of function #27", status, SUCCESS);

    exp = "4 + 1 + 2 ^ 2 ^ 3  * 2 + 1";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #28", res, (double)518.0);
    TEST("Outcome of function #28", status, SUCCESS);
	
    exp = "  4 * 2";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #29", res, (double)8.0);
    TEST("Outcome of function #29", status, SUCCESS);
    
    exp = "4 + 2 * 3";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #30", res, (double)10.0);
    TEST("Outcome of function #30", status, SUCCESS);

	exp = "1+1*2*3+256*4/2^3^2+4/2^2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #31", res, (double)10.0);
    TEST("Outcome of function #31", status, SUCCESS);

	exp = "2 -  -1";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #32", res, (double)3.0);
    TEST("Outcome of function #32", status, SUCCESS);

    exp = "4 /                             3"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #33", res, (double)1.33333333333333333);
    TEST("Outcome of function #33", status, SUCCESS);
    
    exp = "4 / 2 * 2"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #34", res, (double)4.0);
    TEST("Outcome of function #34", status, SUCCESS);

    exp = "2+4+ - 3*2";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #35", res, (double)0.0);
    TEST("Outcome of function #35", status, SUCCESS);

	exp = "2*10^-2";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #36", res, (double)2e-2);
    TEST("Outcome of function #36", status, SUCCESS);
}

void TestExpression()
{
    status_t status = SUCCESS;
    char *exp = NULL;
    double res = 0.0;

	exp = "1 + 2^(5 + 2)";	
	status = Calculate(exp, &res);
    TEST("Outcome of expression #1", res, (double)129.0);
    TEST("Outcome of function #1", status, SUCCESS);

    exp = "-5 * 2 + (10 - 5^-2) / 4 + -2.5^(3)";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #2", (int)res == (int)-23.135000, 1);
    TEST("Outcome of function #2", status, SUCCESS);

	exp = "2+-(3-2)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #3", res == 1, 1);
    TEST("Outcome of function #3", status, SUCCESS);

	exp = "(((25 * (2 + 2))))";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #4", res, (double)100.0);
    TEST("Outcome of function #4", status, SUCCESS);
		
	exp = "(25 * (2 + 2))";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #5", res, (double)100.0);
    TEST("Outcome of function #5", status, SUCCESS);
	
	exp = "25 + 48/(2 + 2)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #6", res, (double)37.0);
    TEST("Outcome of function #6", status, SUCCESS);

	exp = "(1048 - 1046) ^ 3 / (2 + 2)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #7", res, (double)2.0);
    TEST("Outcome of function #7", status, SUCCESS);
	
	exp = "(1046 - 1048) ^ 3 / (2 + 2)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #8", res, (double)-2.0);
    TEST("Outcome of function #8", status, SUCCESS);

	exp = "((44 - 46) + 3 ^ 3 * (12  - 6 / 2) ^ 2) + (100/10)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #9", res, (double)2195.0);
    TEST("Outcome of function #9", status, SUCCESS);

	exp = "- (2 + 3)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #10", res, (double)-5.0);
    TEST("Outcome of function #10", status, SUCCESS);

	exp = "((64 - -46) + 3 ^ 3 * (12  - 6 / 2) ^ 2) + (-100/10)";	
	status = Calculate(exp, &res);
	TEST("Outcome of expression #11", res, (double) 2287.0);
    TEST("Outcome of function #11", status, SUCCESS);

    exp = "4 +2 *    2 ^ 2 ^     (8  / 2) + 1"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #12", res, (double)131077);
    TEST("Outcome of function #12", status, SUCCESS);

	exp = "2^(2-(2-(2^2)))";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #13", res, (double)16.0);
    TEST("Outcome of function #13", status, SUCCESS);

	exp = "(4 + 2 + 1) ^ 3 ^ (1 + 2)";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #14", res, (double)65712362363534278918144.0);
    TEST("Outcome of function #14", status, SUCCESS);

    exp = "( 4 ) + 2 * (10-8)^2";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #15", res, (double)12.0);
    TEST("Outcome of function #15", status, SUCCESS);

    exp = "10^2^3 + 2^(1*(4-2))";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #16", res, (double)100000004.0);
    TEST("Outcome of function #16", status, SUCCESS);

    exp = "(11-1) * (5+5)^3";
	status = Calculate(exp, &res);
	TEST("Outcome of expression #17", res, (double)10000.0);
    TEST("Outcome of function #17", status, SUCCESS);

	exp = "10+0 -(3+1)";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #18", res, (double)6.0);
    TEST("Outcome of function #18", status, SUCCESS);

	exp = "10*2 -(3+1)";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #19", res, (double)16.0);
    TEST("Outcome of function #19", status, SUCCESS);

	exp = "-10*2 -(3-1)";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #20", res, (double)-22.0);
    TEST("Outcome of function #20", status, SUCCESS);

	exp = "2*10^-(1+1)";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #21", res, (double)2e-2);
    TEST("Outcome of function #21", status, SUCCESS);

	exp = "2^(2-(2-(2^2)))";
	status = Calculate(exp, &res);
    TEST("Outcome of expression #22", res, (double)16.0);
    TEST("Outcome of function #22", status, SUCCESS);

    exp = "-(2 - 4)"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #23", res, (double)2.0);
    TEST("Outcome of function #23", status, SUCCESS);

    exp = "2 - -(2 - 4)"; 
    status = Calculate(exp, &res);
	TEST("Outcome of expression #24", res, (double)0.0);
    TEST("Outcome of function #24", status, SUCCESS);

	exp = "((100-20)-(30-50))/2";
    status = Calculate(exp, &res);
	TEST("Outcome of expression #24", res, (double)50.0);
    TEST("Outcome of function #24", status, SUCCESS);
}

void TestSyntaxError()
{
    status_t status = SUCCESS;
    char *exp = NULL;
    double res = 0.0;

	exp = "-5 * 2 + (10 - 5^-2) (/ 4 + -2.5^(3)))";
	status = Calculate(exp, &res);
    TEST("Outcome of function #1", status, SYNTAX_ERR);

	exp = "2++-(3-2)";
	status = Calculate(exp, &res);
    TEST("Outcome of function #2", status, SYNTAX_ERR);


	exp = "z + 1";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #4", status, SYNTAX_ERR);
	
	exp = "2 - k + 1";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #5", status, SYNTAX_ERR);
	
	exp = "2 -  + 1";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #7", status, SYNTAX_ERR);

	exp = "2 -  / 1";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #7", status, SYNTAX_ERR);

	exp = "2 -  ^ 1";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #8", status, SYNTAX_ERR);

    exp = "(11-1)*(5+5)^3)";
	status = Calculate(exp, &res);
    TEST("Outcome of function #9", status, SYNTAX_ERR);

    exp = "(11-1)*((5+5)^3";
	status = Calculate(exp, &res);
    TEST("Outcome of function #10", status, SYNTAX_ERR);

    exp = "n+1";
	status = Calculate(exp, &res);
    TEST("Outcome of function #11", status, SYNTAX_ERR);

    exp = "1/n";
	status = Calculate(exp, &res);
    TEST("Outcome of function #12", status, SYNTAX_ERR);

	exp = "2 ^    * 2";
	status = Calculate(exp, &res);
    TEST("Outcome of function #14", status, SYNTAX_ERR);

	exp = "2 ^ 2 +";
	status = Calculate(exp, &res);
    TEST("Outcome of function #15", status, SYNTAX_ERR);

	exp = "-2 + 15^(3 + -(1))";
	status = Calculate(exp, &res);
	TEST("Outcome of expression:", res, (double)223);
    TEST("Outcome of function #15", status, SUCCESS);
}

void TestIllegalOperation()
{
    status_t status = SUCCESS;
    char *exp = NULL;
    double res = 0.0;

	exp = "(2) / 0";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #2", status, ILLEGAL_OPERATION);

	exp = "-(((-2)^2)^3) / 0";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #3", status, ILLEGAL_OPERATION);

    exp = "3 + 2 / 0";
	status = Calculate(exp, &res);
    TEST("Outcome of function #4", status, ILLEGAL_OPERATION);

	exp = "2+3/0.0";	
	status = Calculate(exp, &res);
    TEST("Outcome of function #5", status, ILLEGAL_OPERATION);
}

