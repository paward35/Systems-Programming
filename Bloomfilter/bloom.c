
#include "bitset.h"
#include "bloom.h"
#include <stdio.h>
#include <stdlib.h>

// create a new, empty Bloom filter of 'size' items
bloom * bloom_new(int size_new)
{
	bloom *newBloom;
	newBloom = malloc(sizeof(bloom));
	newBloom -> size = size_new;
	bitset *bitsetForBloom;
	bitsetForBloom = bitset_new( size_new );
	newBloom -> pointerToBitsetArray = bitsetForBloom ;
	return newBloom;
}

//translates a strig into a unique number
int hashOne( char *string, int bloomSize ) 
{
	int hash = 5381; 
	int c; 
	while ((c = *string++)) 
	{ 
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ 
	} 
	hash = hash%bloomSize;

	if ( hash < 0 )
	{
		hash = hash * -1;
	}	

    	return hash;




}

//translates a strig into a unique number
int hashTwo( char *item, int bloomSize ) 
{
	int hashValue = 0;
	int count = 0;
	int temp = 0;
	int hash = 0; 
	int n; 
	for (int i = 0; item[i] != '\0'; i++) 
	{ // alphabet case 
		if((item[i] >= 'A' && item[i] <= 'Z') || (item[i] >= 'a' && item[i] <= 'z')) 
		{ 
			n = item [i] - 'a' + 1; 
		} // comma case 
		else 
		{
			n = 27;
		}
 
		hash = ((hash << 3) + n) % bloomSize; 
	} 
	if ( hash < 0 )
	{
		hash = hash * -1;
	}
	return hash;
	
	//return hashValue;
}


// add a string to the set
// has no effect if the item is already in the set
// check to see if a string is in the set

int bloom_lookup(struct bloom * thisBloom, char * item)
{
//finds hash values from the string 
	int hashValueOne = hashOne( item, thisBloom -> size) ;
	int hashValueTwo = hashTwo( item, thisBloom -> size) ;
//checks if two hash values have been added to the bitset array
	if ( bitset_lookup( (thisBloom -> pointerToBitsetArray), hashValueOne ) == 1 && (bitset_lookup ( (thisBloom -> pointerToBitsetArray), hashValueTwo) ) == 1)
	{
		 
		return 1;
	}  
	else 
	{	
		return 0;
	}

	

}

//hashes string and adds it to the bitset array
void bloom_add(struct bloom * thisBloom, char * item)
{
	int hashValueOne = hashOne( item, thisBloom -> size) ;
	int hashValueTwo = hashTwo( item, thisBloom -> size) ;

	bitset_add( thisBloom -> pointerToBitsetArray, hashValueOne);
	bitset_add( thisBloom -> pointerToBitsetArray, hashValueTwo);
	

}

//calls union function on the bitset arrays of the src1 and src2 blooms and adds them into the bitset array for dest bloom
void bloom_union(struct bloom * dest, struct bloom * src1, struct bloom * src2)
{
	bitset_union( dest -> pointerToBitsetArray, src1 -> pointerToBitsetArray, src2 -> pointerToBitsetArray) ;
}
//calls union function on the bitset arrays of the src1 and src2 blooms and adds them into the bitset array for dest bloom

void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2)
{
	bitset_intersection( dest -> pointerToBitsetArray, src1 -> pointerToBitsetArray, src2 -> pointerToBitsetArray) ;
}
