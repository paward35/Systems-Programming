

#ifndef bitsets	
#define bitsets	

typedef struct bitset
{
	int size;
	int sizeInBytes;
	char unsigned *data;	

} bitset;


// create a new, empty bit vector set of 'size' items
struct bitset * bitset_new(int size_new );

// check to see if an item is in the set
// returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
int bitset_lookup(struct bitset * thisBitset, int itemNumber);

// add an item, with number 'item' to the set
// (returns 0 if item is out of bounds, 1 otherwise)
// has no effect if the item is already in the set
int bitset_add(struct bitset * thisBitset, int itemNumber);

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(struct bitset * thisBitset, int itemNumber);

// place the union of src1 and src2 into dest
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2);

// place the intersection of src1 and src2 into dest
void bitset_intersection(struct bitset * dest, struct bitset * src1, struct bitset * src2);

#endif


