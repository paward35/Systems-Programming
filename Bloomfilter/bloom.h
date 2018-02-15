
#ifndef blooms	/* any suggestive variable name is fine */
#define blooms	


typedef struct bloom
{
	int size;
	bitset *pointerToBitsetArray;
} bloom;


// create a new, empty Bloom filter of 'size' items
struct bloom * bloom_new(int size);

// check to see if a string is in the set
int bloom_lookup(struct bloom * this, char * item);

// add a string to the set
// has no effect if the item is already in the set
void bloom_add(struct bloom * this, char * item);

// note that you cannot safely remove items from a Bloom filter

// place the union of src1 and src2 into dest
void bloom_union(struct bloom * dest, struct bloom * src1, struct bloom * src2);

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2);

#endif
