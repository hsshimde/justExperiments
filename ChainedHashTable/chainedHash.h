#pragma once
#include "Node.h"

namespace chainedhash
{
	using namespace node;

	class ChainedHashTable
	{
	public:
		ChainedHashTable(size_t tableSize);
		ChainedHashTable(const ChainedHashTable& rhs);
		ChainedHashTable& operator=(const ChainedHashTable& rhs);
		~ChainedHashTable();

		bool AddData(const Data data);
		bool RemoveData(const Data data);
		size_t GetElementCount() const;

	private:
		size_t getHashValue(const Data& data) const;
		Node** mTable;
		size_t mTableSize;
		size_t mElementCount;
		
	};
}

