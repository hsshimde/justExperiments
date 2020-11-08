#include <cassert>

#include "chainedHash.h"



int main()
{

	using namespace chainedhash;

	ChainedHashTable hashTable(211);

	hashTable.AddData(1.39);
	assert(hashTable.GetElementCount() == 1);
	hashTable.AddData(2.145);
	hashTable.AddData(1.67);
	assert(hashTable.AddData(1.67) == false);
	assert(hashTable.GetElementCount() == 3);
	assert(hashTable.RemoveData(1.39) == true);
	assert(hashTable.RemoveData(4.567) == false);

	assert(hashTable.AddData(1.17) == true);
	assert(hashTable.AddData(-8.65) == true);

	assert(hashTable.RemoveData(1.17) == true);

	assert(hashTable.GetElementCount() == 3);


	return 0;


}