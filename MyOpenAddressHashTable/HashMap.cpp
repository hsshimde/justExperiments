//#include <new>
//#include <functional>
//
//#include "HashMap.h"
//
//namespace hashmap
//{
//
//	template <typename K, typename V>
//	HashMap<K, V>::HashMap()
//		: mCapacity{ 16 }
//		, mSize{}
//	{
//		mStateArray = new eState[mCapacity];
//		mData = new std::pair<K, V>[mCapacity];
//
//		for (size_t i{}; i < mCapacity; ++i)
//		{
//			mStateArray[i] = eState::Available;
//		}
//	}
//	template <typename K, typename V>
//	HashMap<K, V>::HashMap(size_t size)
//		: mCapacity{ size }
//		, mSize{}
//	{
//		mStateArray = new eState[mCapacity];
//		mData = new std::pair<K, V>[mCapacity];
//
//		for (size_t i{}; i < mCapacity; ++i)
//		{
//			mStateArray[i] = eState::Available;
//		}
//	}
//
//	template <typename K, typename V>
//	HashMap<K, V>::HashMap(const HashMap& rhs)
//		: mCapacity{ rhs.mCapacity }
//		, mSize{ rhs.mSize }
//	{
//		mStateArray = new eState[mCapacity];
//		mData = new std::pair<K, V>[mSize];
//
//		for (size_t i{}; i < mCapacity; ++i)
//		{
//			mData[i] = rhs.mData[i];
//			mStateArray[i] = rhs.mStateArray[i];
//		}
//
//	}
//
//	template <typename K, typename V>
//	HashMap<K, V>& HashMap<K, V>::operator=(const HashMap& rhs)
//	{
//		delete[] mStateArray;
//		delete[] mData;
//
//		mSize = rhs.mSize;
//		mCapacity = rhs.mCapacity;
//
//		mStateArray = new eState[mCapacity];
//		mData = new std::pair<K, V>[mCapacity];
//
//		for (size_t i{}; i < mCapacity; ++i)
//		{
//			mData[i] = rhs.mData[i];
//			mStateArray[i] = rhs.mStateArray[i];
//		}
//	}
//
//	template <typename K, typename V>
//	HashMap<K, V>::~HashMap()
//	{
//		delete[] mData;
//		delete[] mStateArray;
//	}
//
//	template <typename K, typename V>
//	bool HashMap<K, V>::Resize(size_t newCapacity)
//	{
//
//		if (mLoadFactor >= static_cast<float>(newCapacity) / mSize)
//		{
//			return false;
//		}
//
//		else
//		{
//			std::pair<K, V>* newDataArray = new std::pair<K, V>[newCapacity];
//			eState newStateArray = new eState[newCapacity];
//
//			for (size_t i{}; i < newCapacity; ++i)
//			{
//				newStateArray[i] = eState::Available;
//			}
//
//			for (size_t i{}; i < mCapacity; ++i)
//			{
//				if (mStateArray[i] == eState::Used)
//				{
//					size_t hashTime{};
//					K insertElementKeyVal{ mData[i].first };
//					size_t hashValue{ getHashValue(insertElementKeyVal, hashTime) };
//
//					while (newStateArray[hashValue] != eState::Available)
//					{
//						hashValue = getHashValue(insertElementKeyVal, ++hashTime);
//					}
//
//					newDataArray[hashValue] = mData[i];
//
//				}
//			}
//
//			mCapacity = newCapacity;
//			delete mData;
//			delete mStateArray;
//
//			mData = newDataArray;
//			mStateArray = newStateArray;
//
//			return true;
//
//		}
//
//	}
//
//	template <typename K, typename V>
//	bool HashMap<K, V>::Insert(const std::pair<K, V>& element)
//	{
//		if (static_cast<float>(mSize + 1) / mCapacity >= mLoadFactor)
//		{
//			reHash();
//		}
//
//		size_t hashTryTimes{};
//		K insertElementKeyValue{ element.first };
//
//		size_t hashValue{ getHashValue(insertElementKeyValue, hashTryTimes) };
//
//
//		while (true)
//		{
//			if (mStateArray[hashValue] == eState::Available || mStateArray[hashValue] == eState::Deleted)
//			{
//				mStateArray[hashValue] = eState::Used;
//				mData[hashValue] = element;
//				return true;
//			}
//
//			else
//			{
//				if (mData[hashValue].first == element.first)
//				{
//					return false;
//				}
//				else
//				{
//					hashValue = getHashValue(insertElementKeyValue, ++hashTryTimes);
//				}
//			}
//		}
//
//
//		return true;
//	}
//
//	template <typename K, typename V>
//	bool HashMap<K, V>::Remove(const K& keyValue)
//	{
//		size_t hashTryTime{};
//		size_t hashValue{ getHashValue(keyValue, hashTryTime) };
//
//		while (true)
//		{
//			if (mStateArray[hashValue] == eState::Used)
//			{
//				if (mData[hashValue].first == keyValue)
//				{
//					mStateArray[hashValue] = eState::Deleted;
//					return true;
//				}
//
//				hashValue = getHashValue(keyValue, ++hashTryTime);
//			}
//
//			else if (mStateArray[hashValue] == eState::Deleted)
//			{
//				hashValue = getHashValue(keyValue, ++hashTryTime);
//			}
//
//			else
//			{
//				return false;
//			}
//		}
//	}
//
//	template <typename K, typename V>
//	V* HashMap<K, V>::FindNullable(const K& keyValue) const
//	{
//		size_t hashTryTime{};
//		size_t hashValue{ getHashValue(keyValue, hashTryTime) };
//
//		while (true)
//		{
//			if (mStateArray[hashValue] == eState::Available)
//			{
//				return nullptr;
//			}
//
//
//			else if (mStateArray[hashValue] == eState::Deleted)
//			{
//				hashValue = getHashValue(keyValue, ++hashTryTime);
//			}
//
//			else
//			{
//				if (mData[hashValue].first == keyValue)
//				{
//					return &mData[hashValue].second;
//				}
//
//				else
//				{
//					hashValue = getHashValue(keyValue, ++hashTryTime);
//				}
//			}
//
//		}
//	}
//
//	template <typename K, typename V>
//	V& HashMap<K, V>::operator[](const K& keyValue)
//	{
//		size_t hashTryTime{};
//		size_t hashValue{ getHashValue(keyValue, hashTryTime) };
//
//		while (true)
//		{
//			if (mStateArray[hashValue] == eState::Available)
//			{
//				return mData[hashValue].second;
//			}
//
//
//			else if (mStateArray[hashValue] == eState::Deleted)
//			{
//				hashValue = getHashValue(keyValue, ++hashTryTime);
//			}
//
//			else
//			{
//				if (mData[hashValue].first == keyValue)
//				{
//					return mData[hashValue].second;
//				}
//
//				else
//				{
//					hashValue = getHashValue(keyValue, ++hashTryTime);
//				}
//			}
//
//		}
//	}
//
//	template <typename K, typename V>
//	bool HashMap<K, V>::SetLoadFactor(float loadFactor)
//	{
//		if (loadFactor >= 0.5)
//		{
//			return false;
//		}
//
//		else
//		{
//			mLoadFactor = loadFactor;
//			return true;
//		}
//
//	}
//
//	template <typename K, typename V>
//	void HashMap<K, V>::reHash()
//	{
//		Resize(2 * mCapacity);
//		return;
//	}
//
//	template <typename K, typename V>
//	size_t HashMap<K, V>::getHashValue(const K& keyValue, size_t hashTime) const
//	{
//
//		return (std::hash<K>()(keyValue) + std::hash<K>()(keyValue + 1) % mCapacity) % mCapacity;
//	}
//
//
//	template <typename K, typename V>
//	std::ostream& operator<<(std::ostream& os, const HashMap<K, V>& hashMap)
//	{
//		for (size_t i{}; i < hashMap.mCapacity; ++i)
//		{
//			if (hashMap.mStateArray[i] == eState::Used)
//			{
//				os << "{ " << hashMap.mData[i].first << ", " << hashMap.mData[i].second << " }\n";
//			}
//		}
//
//		return os;
//	}
//}