#pragma once
#include <utility>

namespace hashmap
{
	enum class eState{Available, Used, Deleted};

	template <typename K, typename V>
	class HashMap
	{
	public:
		HashMap(size_t tableSize);	
		HashMap(const HashMap& rhs);
		virtual ~HashMap();
		HashMap& operator=(const HashMap& rhs);

		void Resize(size_t size);
		bool Insert(const std::pair<K, V>& element);
		bool Remove(const K& keyValue);
		std::pair<K, V>* FindNullable(const K& keyValue);
		std::pair<K, V>& operator[](const K& keyValue);

		bool SetLoadFactor(float loadFactor);



	private:
		size_t getHashValue(const K& keyValue, size_t hashTimes) const;
		void reHash();


		eState* mStateArray;
		std::pair<K, V>* mData;
		size_t mCapacity;
		size_t mSize;
		float mLoadFactor;


	};

	
}