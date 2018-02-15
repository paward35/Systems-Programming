/* Program that reads in a text file of integers
   and outputs the numbers in sorted order. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitset.h"
#include "bloom.h"

//const int DEBUG 1;

const int MAX_STRING = 1024;
const int MAX_ASCII = 256;
const int MAX_BLOOMSIZE = 100000000;

//removes punctuation from words such as ',', ';' and '.' 
void tokinseString( char *x )
{
	int count = 0;
//find end of string
	while ( x[count] != '\0' )
	{
		count++;
	}
//check if last character is punctuatoin
	if ( x[count - 1] == '.' || x[count - 1] == ',' || x[count - 1] == ';')
	{
		x[count - 1] = '\0';
	}
}

//main takes in arguments
int main(int argc, char **argv)
{ 

	char * whichInput;
	whichInput = argv[1];
	

	char inputOne[MAX_STRING];
	char inputTwo[MAX_STRING];

//if second letter of second argument is l it can be assumed bloom was entered 
	if ( whichInput[1] == 'l' )
	{

//create and open files for reading
		FILE *fp1;
		FILE *fp2;

		char fileNameOne[MAX_STRING];
		char fileNameTwo[MAX_STRING];
		fp2 = fopen(argv[2], "r");
		fp1 = fopen(argv[3], "r");
//create and inizlise blooms
		bloom *seen = bloom_new( MAX_BLOOMSIZE );
		bloom_add( seen, "" );
		bloom *written = bloom_new( MAX_BLOOMSIZE );
		bloom_add( written, "" );
		bloom *unionBloom = bloom_new( MAX_BLOOMSIZE );
		bloom *intersectionBloom = bloom_new( MAX_BLOOMSIZE );
		
		char x[1024];
		int c = 0;
//read in words from files, remove punctuation and then add to bloom filter
    		while (fscanf(fp1, " %1023s", x) == 1) 
		{
			tokinseString( x );
			bloom_add( seen, x );
    		}
		c = 0;
//read it words from second file, check if is in seen or written blooms then print to screen and add to written
		while ( fscanf(fp2, " %1023s", x) == 1) 
		{
			tokinseString( x );
			if ( 1 == bloom_lookup( seen, x ) && 0 == bloom_lookup( written , x ) )
			{
				bloom_add( written, x );
				printf("\n%s", x);
			}

    		}

		
		printf("\n");
	}

	else 
	{
//create and inilize bitsets

		bitset *pointerForBitsetOne = bitset_new( MAX_ASCII ) ;
		bitset *pointerForBitsetTwo = bitset_new( MAX_ASCII );
		bitset *pointerForBitsetIntersection = bitset_new( MAX_ASCII );
		bitset *pointerForBitsetUnion = bitset_new( MAX_ASCII );
	
		printf("\nEnter set 1 as a string of ASCII characters : ");
		fgets(inputOne, MAX_STRING, stdin);
		int count = 0;
	
		char unsigned tempChar;	
		int charPosition;
// converts chars into their numerical value then adds to first bloom filter
		while( inputOne[count] != '\0' && inputOne[count] != '\n')
		{
			tempChar = (char unsigned) inputOne[count];
			charPosition = (int) tempChar;
			bitset_add( pointerForBitsetOne, charPosition ); 
			count++;
		}


	
		printf("\nEnter set 2 as a string of ASCII characters : ");
		fgets(inputTwo, MAX_STRING, stdin);

		count = 0;
// converts chars into their numerical value then adds to second bloom filter
		while( inputTwo[count] != '\0' && inputTwo[count] != '\n')
		{
			tempChar = (char unsigned) inputTwo[count];
			charPosition = (int) tempChar;
			bitset_add( pointerForBitsetTwo, charPosition ); 
			count++;
		}
// make union and intersection blooms
		bitset_union( pointerForBitsetUnion, pointerForBitsetOne, pointerForBitsetTwo);
		bitset_intersection( pointerForBitsetIntersection, pointerForBitsetOne, pointerForBitsetTwo);
		printf( "\nThere was union with ");
//check to see what character values have been added to the union bloom, if a value has been added print to screen
		for ( count = 0 ; count < MAX_ASCII; count++ )
		{
			if ( bitset_lookup( pointerForBitsetUnion , count) == 1 )
			{
				printf( ": '%c' ", count);
			}
		}

		printf( "\n");
		printf( "\nThere was intersection with ");
//check to see what character values have been added to the intersection bloom, if a value has been added print to screen
		for ( count = 0 ; count < MAX_ASCII; count++ )
		{
			if ( bitset_lookup( pointerForBitsetIntersection , count) == 1 )
			{
				printf( ": '%c' ", count);
			}
		}

		printf( "\n");


	}


	return 0;
}














