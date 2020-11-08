#include "chainedHash.h"


namespace chainedhash
{


	ChainedHashTable::ChainedHashTable(size_t tableSize)
		: mTableSize{tableSize}
		, mElementCount{0}
	{
		
		mTable = new Node * [mTableSize];

		for (size_t i{}; i < mTableSize; ++i)
		{
			mTable[i] = nullptr;
		}
	}

	ChainedHashTable::ChainedHashTable(const ChainedHashTable& rhs)
		: mTableSize{ rhs.mTableSize }
		, mElementCount{rhs.mElementCount}
	{
		mTable = new Node * [mTableSize];

		for (size_t i{}; i < mTableSize; ++i)
		{
			if (rhs.mTable[i] != nullptr)
			{
				mTable[i] = new Node{ rhs.mTable[i]->GetData() };

				Node* tempRhs{ rhs.mTable[i] };
				Node* tempLhs{ mTable[i] };

				while (tempRhs->GetNext() != nullptr)
				{
					tempRhs = tempRhs->GetNext();
					tempLhs->GetNext() = new Node{ tempRhs->GetData() };
					tempLhs = tempLhs->GetNext();
				}
			}
		}
	}

	ChainedHashTable::~ChainedHashTable()
	{
		for (size_t i{}; i < mTableSize; ++i)
		{
			if (mTable[i] != nullptr)
			{
				delete mTable[i];
			}
		}
	}

	ChainedHashTable& ChainedHashTable::operator=(const ChainedHashTable& rhs)
	{
		if (this != &rhs)
		{
			for (size_t i{}; i < mTableSize; ++i)
			{
				if (mTable[i] != nullptr)
				{
					delete mTable[i];
				}
			}

			mTableSize = rhs.mTableSize;

			for (size_t i{}; i < mTableSize; ++i)
			{
				if (rhs.mTable[i] != nullptr)
				{
					mTable[i] = new Node{ rhs.mTable[i]->GetData() };

					Node* tempRhs{ rhs.mTable[i] };
					Node* tempLhs{ mTable[i] };

					while (tempRhs->GetNext() != nullptr)
					{
						tempLhs->GetNext() = new Node{ tempRhs->GetNext()->GetData() };
						tempLhs = tempLhs->GetNext();
						tempRhs = tempRhs->GetNext();
					}
				}
			}
		}

		return *this;

	}

	size_t ChainedHashTable::getHashValue(const Data& data) const
	{
		size_t integerData{ static_cast<size_t>(data) };

		return integerData % mTableSize;
	}

	bool ChainedHashTable::AddData(const Data data)
	{
		size_t hashValue{ getHashValue(data) };

		if (mTable[hashValue] != nullptr)
		{
			Node* formerHead{ mTable[hashValue] };
			Node* temp{ mTable[hashValue] };
			while (temp != nullptr)
			{
				if (temp->GetData() == data)
				{
					return false;
				}

				temp = temp->GetNext();
			}

			mTable[hashValue] = new Node{ data };
			mTable[hashValue]->GetNext() = formerHead;
		}

		else
		{
			mTable[hashValue] = new Node{ data };
		}

		mElementCount++;
		return true;
	}

	bool ChainedHashTable::RemoveData(const Data data)
	{
		size_t hashValue{ getHashValue(data) };

		if (mTable[hashValue] != nullptr)
		{
			Node* temp{ mTable[hashValue] };

			if (mTable[hashValue]->GetData() == data)
			{

				Node** formerHead = &mTable[hashValue];
				*formerHead = temp->GetNext();
				temp->GetNext() = nullptr;
				delete temp;
				mElementCount--;
				return true;
			}

			else
			{
				while (temp->GetNext()->GetData() != data && temp != nullptr)
				{
					temp = temp->GetNext();
				}

				if (temp == nullptr)
				{
					return false;
				}

				else
				{
					Node* deleteTarget{ temp->GetNext() };
					temp->GetNext() = deleteTarget->GetNext();
					deleteTarget->GetNext() = nullptr;
					delete deleteTarget;

					mElementCount--;
					return true;
				}
			
				
			}

		}

		else
		{
			return false;
		}
	}

	size_t ChainedHashTable::GetElementCount() const
	{
		return mElementCount;
	}
}