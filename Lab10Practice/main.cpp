#include <cassert>

#include "DoubleLinkedList.h"
#include "Node.h"

using namespace lab10;

int main()
{
	DoublyLinkedList<int> myList{};
	
	myList.Insert(std::make_unique<int>(11));
	assert(myList.GetLength() == 1);
	myList.Insert(std::make_unique<int>(12));
	assert(myList.GetLength() == 2);
	myList.Insert(std::make_unique<int>(44));
	assert(myList.Search(44));
	assert(myList.Search(11));
	assert(!myList.Search(1));

	myList.Insert(std::make_unique<int>(19), 2);
	assert(*myList[2]->Data == 19);
	myList.Insert(std::make_unique<int>(22), 0);
	assert(*myList[0]->Data == 22);
	
	return 0;
}