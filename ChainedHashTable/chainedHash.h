#pragma once
#include "Node.h"

namespace chainedhash
{
	using namespace node;

	class ChainedHashTable
	{
		ChainedHashTable(size_t tableSize);
		ChainedHashTable(const ChainedHashTable& rhs);
		ChainedHashTable& operator=(const ChainedHashTable& rhs);
		~ChainedHashTable();

		bool AddData(const Data data);
		bool RemoveData(const Data data);
		

	private:
		size_t getHashValue(const Data& data) const;
		Node** mTable;
		size_t mTableSize;
		
	};
}

