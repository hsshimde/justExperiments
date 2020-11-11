#include <new>
#include "HashMap.h"

namespace hashmap
{

	template <typename K, typename V>
	HashMap<K, V>::HashMap(size_t size)
		: mCapacity{ size }
		, mSize{}
	{
		mStateArray = new eState[size];
		mData = new std::pair<K, V>[size];

		for (size_t i{}; i < mCapacity; ++i)
		{
			mStateArray[i] = eState::Available;
		}
	}

	template <typename K, typename V>
	HashMap<K, V>::HashMap(const HashMap& rhs)
		: mCapacity{ rhs.mCapacity }
		, mSize{ rhs.mSize }
	{
		mStateArray = new eState[mCapacity];
		mData = new std::pair<K, V>[mSize];

		for (size_t i{}; i < mCapacity; ++i)
		{
			mData[i] = rhs.mData[i];
			mStateArray[i] = rhs.mStateArray[i];
		}

	}

	template <typename K, typename V>
	HashMap<K, V>& HashMap<K, V>::operator=(const HashMap& rhs)
	{
		delete[] mStateArray;
		delete[] mData;

		mSize = rhs.mSize;
		mCapacity = rhs.mCapacity;

		mStateArray = new eState[mCapacity];
		mData = new std::pair<K, V>[mCapacity];

		for (size_t i{}; i < mCapacity; ++i)
		{
			mData[i] = rhs.mData[i];
			mStateArray[i] = rhs.mStateArray[i];
		}
	}

	template <typename K, typename V>
	HashMap<K, V>::~HashMap()
	{
		delete[] mData;
		delete[] mStateArray;
	}

	template <typename K, typename V>
	void HashMap<K, V>::Resize(size_t size)
	{
		eState* newStateArray = new eState[size];
		std::pair<K, V>* newDataArray = new std::pair<K, V>[size];

		for (size_t i{}; i < )
	}

	template <typename K, typename V>
	bool HashMap<K, V>::Insert(const std::pair<K, V>& element)
	{
		if (static_cast<float>(mSize + 1) / mCapacity >= mLoadFactor)
		{
			reHash();
		}

		size_t hashTryTimes{};
		K insertElementKeyValue{ element.first };

		size_t hashValue{ getHashValue(insertElementKeyValue, hashTryTimes) };


		while (mStateArray[hashValue] == eState::Used)
		{
			if (mData[hashValue].first == insertElementKeyValue)
			{
				return false;
			}

			hashTryTimes++;
			hashValue = getHashValue(insertElementKeyValue, hashTryTimes);
		}

		mStateArray[hashValue] = eState::Used;
		mData[hashValue] = element;

		return true;
	}

	template <typename K, typename V>
	bool HashMap<K, V>::Remove(const K& keyValue)
	{
		
	}
}