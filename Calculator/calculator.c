/* Program that reads in a text file of integers
   and outputs the numbers in sorted order. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math.h>
#include <math.h>
#include <string.h>

 
const int MAX_STRING = 256;
const int NUMBER_OF_OPERATORS = 5;
char operators[] = {'^','X','/','+','-'};
  
//

typedef struct stack
{
	struct stack *pointerToNextNode;
	double data;
} stack;

int isEmpty(stack *pStack) 
{
	if(pStack == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
   
double pop( stack **ppStack) 
{
	double value;
	stack *newPointer;
	newPointer = *ppStack;
	*ppStack = newPointer -> pointerToNextNode;
	value = newPointer -> data;
	free(newPointer);
	return value;
}

void push(stack **ppStack , double data) 
{
	stack *nextPointer = malloc( sizeof(stack) );
	nextPointer -> data = data;
	nextPointer -> pointerToNextNode = *ppStack;
	*ppStack = nextPointer;
}

void printStack(stack *pStack)
{
	printf("\n");
	while ( pStack !=NULL)
	{
		printf("\n %f ", pStack->data);	
		pStack = pStack-> pointerToNextNode;
	}
} 


int getOperatorPresidenceFromStack(stack *stackPointerForOperators)
{
	int operator; 
	
	if ( !isEmpty(stackPointerForOperators) )
	{
		operator = stackPointerForOperators -> data ;
		if (operator == '^')
		{
			return 0;
		} else if (operator == 'X')
		{
			return 1;
		} else if (operator == '/')
		{
			return 2;
		} else if (operator == '+')
		{
			return 3;
		} else if (operator == '-')
		{
			return 4;
		}
	}
	return 5;
}

void initalizeStack( stack **ppStack)
{
	*ppStack = NULL;
}

//function for spliting a string into tokens 

int tokenise_ops(char str[], int start, char result[], char operators[])
{
	int resultIndex = 0;
	int isOperator = 0;
	int i = 0;
//remove any spaces before token
	while ( str[start] == ' ')
	{
		start = start + 1;
	}
//check for brackets
	if ( str[start] == '(')
	{
		result[resultIndex] = '(';
		result[resultIndex + 1] = '\0';
		start = start + 1;
		return start;
	}
	
	if ( str[start] == ')')
	{
		result[resultIndex] = ')';
		result[resultIndex + 1] = '\0';
		start = start + 1;
		return start;
	}  
//check for operator as token	
	for ( i = 0; i < NUMBER_OF_OPERATORS; i++ )
	{
		
		if ( str[start] == operators[i])
		{
			result[resultIndex] = operators[i];
			result[resultIndex + 1] = '\0';
			start = start + 1;
			return start;
		} 
			
	}
	i = 0;

//add in number to result
	while ( str[start] != ' ' && str[start] != '\0' && str[start] != ')' && str[start] != '(' )
	{
		for ( i = 0; i < NUMBER_OF_OPERATORS; i++ )
		{
			if ( str[start] == operators[i])
			{
				result[resultIndex] = '\0';
				return start;
			} 
		}
		i = 0;
//removes new line character
		if ( str[start] == '\n')
		{		
			start = start + 1;
		}
		result[resultIndex] = str[start];		
		resultIndex = resultIndex + 1;
		start = start + 1;
	}
//terminate string
	result[resultIndex] = '\0';
//remove spaces at end 
	while ( str[start] == ' ')
	{
		start = start + 1;
	}
//terminate if input string is over 
	if ( str [start] == '\0' && resultIndex == 0  ) 
	{
		return -1;
	}
//return next index for token
	return start;
}

//fuction for checking if a char is an opperator
int findIsOperator( char charToBeChecked )
{
	for ( int i = 0; i < NUMBER_OF_OPERATORS; i++ )
	{
		if ( charToBeChecked == operators[i])
		{
			return 1;			
		} 
			
	}
	return 0;
}

//fuction for checking precendence of opperators
int checkOpperatorPrecedence( char operatorToBeChecked )
{
	for ( int i = 0; i < NUMBER_OF_OPERATORS; i++ )
	{
		if ( operatorToBeChecked == operators[i])
		{
			return  i;			
		} 
			
	}
	return  5;
}

int checkForNegitiveNumber( int start, char input[]) 
{
	start--;
	while ( input[start] == ' ' && start >= 0) 
	{
		start--;
	}
	
	return findIsOperator(input[start]);
}

/* read in a file of numbers, sort them, and
   write them out to the screen */
void convertToPostfix(char input[], char operators[])
{
	int start = 0;
	char token[MAX_STRING];
	char newInputStream[MAX_STRING];
	int indexForInputStream = 0;
	int isNegitiveNumber = 0;
	stack *stackPointerForOperators;
	initalizeStack(&stackPointerForOperators);
	start = tokenise_ops (input, start, token, operators);	
	double numberIn = 0;
	while (start != -1) 
	{
		numberIn = 0;
		numberIn = atof(token);
		int isOperator = 0;
		int currentOperatorPrecedence = 0;
		int topOperatorPresdence = 0;
//to check if token is operator

		if ( numberIn == 0.0)
		{
			isOperator = findIsOperator( token[0] );
			if ( isOperator)
			{
				currentOperatorPrecedence = checkOpperatorPrecedence(token[0]);
			}
		}
//algorithm for creating postfix string (as taken from lab3 worksheet)

		if ( numberIn != 0.0)
		{
			if ( isNegitiveNumber == 1 )
			{
				newInputStream[indexForInputStream] = '-';
				indexForInputStream++;	
				isNegitiveNumber = 0;
			}
			int i = 0;
			while( token[i] != '\0')
			{
				newInputStream[indexForInputStream] = token[i];
				indexForInputStream++;	
				i++;
			}
			numberIn = 0;
			newInputStream[indexForInputStream] = ' '; 
			indexForInputStream++;
		}
		else if ( token[0] == '(')
		{
			push(&stackPointerForOperators, '(');
		}
		else if (isOperator)
		{
			

			
				if ( !isEmpty(stackPointerForOperators) )
				{
					topOperatorPresdence = getOperatorPresidenceFromStack(stackPointerForOperators);
					while ( currentOperatorPrecedence > topOperatorPresdence)
					{
						char operator = pop( &stackPointerForOperators);
						newInputStream[indexForInputStream] = operator;
						indexForInputStream++; 
						newInputStream[indexForInputStream] = ' '; 
						indexForInputStream++;
						topOperatorPresdence = getOperatorPresidenceFromStack(stackPointerForOperators);
					}
				}
				push(&stackPointerForOperators, token[0]);
			
			
		} else if ( token[0] ==')' )
		{
			while ( stackPointerForOperators -> data != '(' )
			{
				char operatorAsChar = pop( &stackPointerForOperators);
				newInputStream[indexForInputStream] = operatorAsChar; 
				indexForInputStream++;
				newInputStream[indexForInputStream] = ' '; 
				indexForInputStream++;
				topOperatorPresdence = getOperatorPresidenceFromStack(stackPointerForOperators);
			}
			int poppedThingy = (int)pop(&stackPointerForOperators);
		}

		for ( int i = 0; i < MAX_STRING; i++)
		{
			token[i] = '\0';
		}
			
		start = tokenise_ops (input, start, token, operators);	

		
	}		
	while ( !isEmpty(stackPointerForOperators) )
	{
		char operator = (char)pop( &stackPointerForOperators);
		newInputStream[indexForInputStream] = operator;
		indexForInputStream++;
		newInputStream[indexForInputStream] = ' '; 
		indexForInputStream++;
	}
	newInputStream[indexForInputStream + 1] = '\0'; 
//copy new input stream over old and reset new input
	for ( int i = 0; i < MAX_STRING; i++)
		{
			input[i] = newInputStream[i];
			newInputStream[i] = '\0';
		}	
}


int main()
{
	char operators[] = {'^','X','/','+','-'};
	char result[MAX_STRING];
	int start = 0;
	double numberOne = 0;
	double resultOfOperations = 0;
	double numberTwo = 0;
	
	while( 1 != 2 )
	{
	
	char input[MAX_STRING];
	printf("Enter your calculation in infix notation : ");
	fgets(input, MAX_STRING, stdin);
	convertToPostfix(input, operators);

	stack *stackPointerForNumbers;
	initalizeStack(&stackPointerForNumbers);
	printStack(stackPointerForNumbers);
//gets tokens from postix string and performs opperations
	while ( start != -1 )
	{
//gets tokens
		start = tokenise_ops (input, start, result, operators);
		double numberIn = atof(result);
		
		if ( start != -1 )
		{
//algorithm for computing a postfix string as taken from the lab worksheet
			if (numberIn != 0 )
			{
				push(&stackPointerForNumbers, numberIn);
			} 
			else
			{
				numberOne = pop(&stackPointerForNumbers);
				numberTwo = pop(&stackPointerForNumbers);
				if (result[0] == '^' )
				{
					int count = 1;
					resultOfOperations = numberTwo;
					while ( numberOne != count )
					{
						resultOfOperations = resultOfOperations * numberTwo;
						count++;
						
					}
					/*resultOfOperations = pow(numberTwo, numberOne);//fhfghf
					  pow gave error "undefined reference despite math.h 						  being included
					*/
				}
				else if (result[0] == 'X' )
				{
					resultOfOperations = numberTwo * numberOne;
				}
				else if (result[0] == '/' )
				{
					resultOfOperations = numberTwo/numberOne;
				}
				else if (result[0] == '+' )
				{
					resultOfOperations = numberTwo + numberOne;
				}
				else
				{
					resultOfOperations = numberTwo - numberOne;
				}
				push(&stackPointerForNumbers, resultOfOperations);
			} 
		}

		for ( int i = 0; i < MAX_STRING; i++)
		{
			result[i] = '\0';
		}

		
	}
	for ( int i = 0; i < MAX_STRING; i++)
		{

			input[i] = '\0';
		}
	
	printf("FINAL result of operations is : %f\n", resultOfOperations);

	start = 0;
	}
	
	return 0;
}


