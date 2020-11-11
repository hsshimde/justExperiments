#include "HashMap.h"

namespace hashmap
{
	/*eState* mStateArray;
	std::pair<K, V>* mData;
	size_t mCapacity;
	size_t mSize;*/
	template <typename K, typename V>
	HashMap<K, V>::HashMap(size_t size)
		: mCapacity{size}
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
		: mCapacity{rhs.mCapacity}
		, mSize{rhs.mSize}
	{
		mStateArray = new eState[mCapacity];
		mData = new std::pair<K, V>[mSize];

		for (size_t i{}; i < mCapacity; ++i)
		{
			if (i < mSize)
			{
				mData[i] = rhs.mData[i];
			}

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
			if (i < mSize)
			{
				mData[i] = rhs.mData[i];
			}
			
			mStateArray[i] = rhs.mStateArray[i];
		}
	}
}