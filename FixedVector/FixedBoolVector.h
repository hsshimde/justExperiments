#pragma once
#include "FixedVector.h"

namespace lab8
{
	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		FixedVector(const FixedVector& rhs);
		virtual ~FixedVector();
		FixedVector& operator=(const FixedVector& rhs);

		bool Add(bool bData);
		bool Remove(bool bData);
		bool Get(size_t index) const;
		bool operator[](size_t index) const;

		int GetIndex(bool bData) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t mSize;
		size_t mCapacity;
		size_t mData[N / 32 + 1];
		static constexpr size_t BYTE_COUNT{ 32 };


	};
}

namespace lab8
{
	template <size_t N>
	FixedVector<bool, N>::FixedVector()
		: mSize{}
		, mCapacity{ N }
		, mData{}
	{

	}

	template <size_t N>
	FixedVector<bool, N>::FixedVector(const FixedVector& rhs)
		: mSize{ rhs.mSize }
		, mCapacity{ rhs.mCapacity }
		, mData{}
	{
		for (size_t i{}; i < mSize / BYTE_COUNT + 1; ++i)
		{
			mData[i] = rhs.mData[i];
		}



	}

	template <size_t N>
	FixedVector<bool, N>::~FixedVector()
	{

	}

	template <size_t N>
	bool FixedVector<bool, N>::Add(bool bData)
	{

		if (mSize >= mCapacity)
		{
			return false;
		}

		else
		{
			if (bData)
			{
				size_t arrayIndex{ mSize / BYTE_COUNT };
				size_t bitIndex{ mSize % BYTE_COUNT };
				size_t bit{ 1 << bitIndex };


				mData[arrayIndex] |= bit;
			}

			mSize++;

			return true;
		}
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(bool bData)
	{
		if (bData)
		{
			size_t firstTrueIndex{};
			while (!(mData[firstTrueIndex / BYTE_COUNT] & (1 << firstTrueIndex)) && firstTrueIndex < mSize)
			{
				firstTrueIndex++;
			}

			if (firstTrueIndex >= mSize)
			{
				return false;
			}

			if (firstTrueIndex % BYTE_COUNT == 0)
			{

				for (size_t i{ firstTrueIndex / BYTE_COUNT }; i <= mSize / BYTE_COUNT; ++i)
				{
					mData[i] >>= 1;
				}

			}

			else
			{
				for (size_t i{ firstTrueIndex / BYTE_COUNT }; i <= mSize / BYTE_COUNT; ++i)
				{

					mData[i] >>= 1;

					if (i + 1 <= mSize / BYTE_COUNT)
					{
						if (mData[i + 1] & 1)
						{
							mData[i] |= (1 << BYTE_COUNT - 1);
						}
					}
				}

				mData[firstTrueIndex % BYTE_COUNT - 1] &= ~(1 << (firstTrueIndex % BYTE_COUNT - 1));

				mSize--;

				return true;

			}

		}

		else
		{
			size_t firstFalseIndex{};

			while ((mData[firstFalseIndex / BYTE_COUNT] & (1 << firstFalseIndex) && firstFalseIndex < mSize))
			{
				firstFalseIndex++;
			}

			if (firstFalseIndex >= mSize)
			{
				return false;
			}


			for (size_t i{ firstFalseIndex / BYTE_COUNT }; i <= mSize / BYTE_COUNT; ++i)
			{
				mData[i] >>= 1;
				if (i + 1 <= mSize / BYTE_COUNT)
				{
					if (mData[i + 1] & 1)
					{
						mData[i] |= (1 << BYTE_COUNT - 1);
					}
				}
			}

			if (firstFalseIndex % BYTE_COUNT != 0)
			{
				mData[firstFalseIndex / BYTE_COUNT] |= (1 << firstFalseIndex % BYTE_COUNT - 1);
			}

			mSize--;

			return true;
		}
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(bool bData) const
	{
		if (bData)
		{
			size_t firstTrueIndex{};

			while (!(mData[firstTrueIndex / BYTE_COUNT] & (1 << firstTrueIndex) && firstTrueIndex < mSize))
			{
				firstTrueIndex++;
			}

			if (firstTrueIndex >= mSize)
			{
				return -1;
			}

			else
			{
				return static_cast<int>(firstTrueIndex);
			}
		}

		else
		{
			size_t firstFalseIndex{};

			while (mData[firstFalseIndex / BYTE_COUNT] & (1 << firstFalseIndex) && firstFalseIndex < mSize)
			{
				firstFalseIndex++;
			}

			if (firstFalseIndex >= mSize)
			{
				return -1;
			}

			else
			{
				return static_cast<int>(firstFalseIndex);
			}

		}
	}
}

