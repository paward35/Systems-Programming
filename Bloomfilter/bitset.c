
#include "bitset.h"
#include <stdio.h>
#include <stdlib.h>

//inilise new bitsets
bitset * bitset_new( int size_new )
{
//clear memory for new bitset structure
	bitset *newBitset;
	newBitset = malloc (sizeof(bitset));
//calculate needed for bitset array in bytes
	int sizeInBytes_new = size_new/8;
	if ( size_new % 8 != 0 )
	{	
		sizeInBytes_new++;
	}
//clear memory for new bit array
	char unsigned  *newPointer = calloc( sizeInBytes_new, sizeof(char) );
//assign new variables to new bitset structure and return pointer to new struture 
	newBitset -> size = size_new;
	newBitset -> sizeInBytes = sizeInBytes_new;
	newBitset -> data = newPointer;
	return newBitset;
}

//find if a particular location in a bitset array has 0 or 1 stored
int bitset_lookup( bitset * thisBitset, int itemNumber)
{
//if location is larger than bitset array return -1
	if ( (thisBitset -> size) < itemNumber )
	{
		return -1;
	}
//calculates byte and bit index in bitset array
	int byteIndex = itemNumber/8;
	int bitIndex = itemNumber%8;
//isolates byte with desired entry number
	char arrayEntery = thisBitset -> data[byteIndex];
//shifts desired bit into first location and 'ands' it with 1 (0000 0001) 
	return ( arrayEntery >> bitIndex ) & 1;
}

//adds item at given location in bitset array
int bitset_add(struct bitset *thisBitset, int itemNumber)
{
//if location is larger than bitset array return 0
	if ( (thisBitset -> size) < itemNumber )
	{
		return 0;
	}
//if item has already been added at that location return 1
	if ( bitset_lookup(thisBitset, itemNumber) != 0 )
	{
		return 1;
	}
//calculates byte and bit index in bitset array
	int byteIndex = itemNumber/8;
	int bitIndex = itemNumber%8;
//replaces relevent byte in bitset array with  ( 1 << bitIndex ) | thisBitset -> data[byteIndex]
//( 1 << bitIndex ) | thisBitset -> data[byteIndex] works by shifting 1 to the desired bit and then 'or'ing it with the current byte in the bit array
	thisBitset -> data[byteIndex] = ( 1 << bitIndex ) | thisBitset -> data[byteIndex];
	return 1;	 

}

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(struct bitset * thisBitset, int itemNumber)
{
//if location is larger than bitset array return 0
	if ( (thisBitset -> size) < itemNumber )
	{
		return 0;
	}
//calculates the relevent bit any byte index of the item  
	int byteIndex = itemNumber/8;
	int bitIndex = itemNumber%8;
//replaces relevent byte in bitset array with  ~( 1 << bitIndex ) & (thisBitset -> data[byteIndex]) 
//~( 1 << bitIndex ) & (thisBitset -> data[byteIndex]) this works by getting shifting 1 into the deisred bit, then flipping the bits so there's a zero in the desired bit and one everywhere else, then 'and'ing this with the  relevent byte from the bitset
	thisBitset -> data[byteIndex] = ~( 1 << bitIndex ) & (thisBitset -> data[byteIndex])  ; 
	return 1;
}

// place the intersection of src1 and src2 into dest
void bitset_intersection(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
//calculates which of the two bitsets is smaller
	int sizeInBytesOfSmallerset = ( src1 -> sizeInBytes < src2 -> sizeInBytes ) ? ( src1 -> sizeInBytes ) : ( src2 -> sizeInBytes ) ;
//iterates over the dest bitset with the relevent results of 'and'ing the two bitsets being intersected
	for ( int count = 0; count < sizeInBytesOfSmallerset; count++)
	{
		dest -> data[count] = src1 -> data[count] & src2 -> data[count] ; 
	}
}

//// place the union of src1 and src2 into dest
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
//calculates which of the two bitsets is smaller
	int sizeInBytesOfSmallerset = ( src1 -> sizeInBytes < src2 -> sizeInBytes ) ? ( src1 -> sizeInBytes ) : ( src2 -> sizeInBytes ) ;
//iterates over the dest bitset with the relevent results of 'or 'ing the two bitsets being unionised
	for ( int count = 0; count < sizeInBytesOfSmallerset; count++)
	{
		dest -> data[count] = src1 -> data[count] | src2 -> data[count] ; 
	}
}











