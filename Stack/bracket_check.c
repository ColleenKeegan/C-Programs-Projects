/*
Jason van Raamsdonk:
Program that checks for good use of brackets by way of stack.
"Good use", refers to a matching opening an closing brackets of same type((), {}. []).
e.g.      (a+b) = good
		  )a+b( = bad
*/



#include <stdlib.h>

#define SIZE 100

typedef struct 
{
	char item[SIZE];
	int top;
}Stack;

// Func. prototypes

// functions for stack operations
void push(Stack *, char);
char pop(Stack *);
int isEmpty(Stack *);
char stacktop(Stack *);

// functions required for applicatiom
int isOpeningMatch(char, char);
int checkExpr(char[]);

// push operation
void push(Stack *sp, char v)
{
	// checking overflow
	if (sp->top == SIZE - 1){
		printf("Stack Overflow, terminating program\n");
		exit(1);
	}
	// otherwise push
	sp->item[++sp->top] = v;
}

// pop operation
char pop(Stack *sp)
{
	if (isEmpty(sp)){
		printf("Stack Underflow, terminating program\n");
		exit(1);
	}
	return sp->item[sp->top--];
}

// returns 1 if stack is empty, otherwise 0
int isEmpty(Stack *sp){
	return sp->top == -1;// returns 1 if they are equal
}

char stacktop(Stack *sp)
{
	if (isEmpty(sp))
	{
		printf("Stack Underflow, terminating program\n");
		exit(1);
	}
	return sp->item[sp->top];
}

int isOpeningMatch(char left, char right)
{
	int match = 0;
	switch(left){
		case '(': if (right == ')')
					match = 1;
					break;
		case '{': if (right == '}')
					match = 1;
					break;
		case '[': if (right == ']')
					match = 1;
					break;
		default: printf("Invalid Symbol encountered, terminating program\n");
				 exit(1);
	}
	return match;
}

// implentation of the algorithm
int checkExpr(char expr[])
{
	Stack stack;
	stack.top = -1;

	int error = 0;
	int i = 0;
	while(expr[i] != '\0'){
		// get next character from expr
		char next_char = expr[i];
		if (next_char == '(' || next_char == '{' || next_char == '[')
		{
			push(&stack, next_char);
		}
		else if (next_char == ')' || next_char == '}' || next_char == ']')
		{
			if (isEmpty(&stack))
			{
				error = 1;
				break;
			}
			else if (isOpeningMatch(stacktop(&stack), next_char))
			{
				pop(&stack);
			}
			else
			{
				error = 1;
				break;
			}
		}

		++i;
		
	}
	if (!error && !isEmpty(&stack))
	{
		error = 1;
	}

	return error;
}


int main()
{
	char expr[SIZE];
	printf("Invalid Expression: ");
	scanf("%s", expr);

	if (checkExpr(expr))
	{
		printf("Does not contain well formed brackets\n");
	}
	else
	{
		printf("Contains well formed brackets\n");
	}
	return 0;
}
