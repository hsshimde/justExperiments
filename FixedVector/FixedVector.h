#pragma once

namespace lab8
{
	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		FixedVector(const FixedVector& rhs);
		FixedVector& operator=(const FixedVector& rhs);
		virtual ~FixedVector();

		bool Add(const T& element);
		bool Remove(const T& element);
		int GetIndex(const T& element) const;
		const T& Get(size_t) const;
		T& operator[](size_t index) const;
		
		size_t GetSize() const;
		size_t GetCapacity() const;


	private:
		T mArray[N];
		size_t mSize;
		size_t mCapacity;

	};
}

namespace lab8
{
	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mCapacity{N}
		, mArray{}
	{
		mSize = 0;
	}



	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector(const FixedVector& rhs)
		: mCapacity{ rhs.mCapacity }
		, mSize{ rhs.mSize }
	{
		for (size_t i{}; i < mSize; ++i)
		{
			mArray[i] = rhs.mArray[i];
		}

	}

	template <typename T, size_t N>
	FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector<T, N>& rhs)
	{
		if (this != &rhs)
		{
			mCapacity = rhs.mCapacity;
			mSize = rhs.mSize;
			for (size_t i{}; i < mSize; ++i)
			{
				mArray[i] = rhs.mArray[i];
			}

		}
		
		return *this;
	}

	template <typename T, size_t N>
	FixedVector<T, N>::~FixedVector()
	{

	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& element)
	{
		if (mSize >= mCapacity)
		{
			return false;
		}

		else
		{
			mArray[mSize++] = element;
			return true;
		}
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Remove(const T& element)
	{
		if (mSize < 1)
		{
			return false;
		}

		else
		{
			size_t i{};

			for (; i < mSize; ++i)
			{
				if (mArray[i] == element)
				{
					break;
				}
			}

			if (i >= mSize)
			{
				return false;
			}

			if (i != mCapacity - 1)
			{
				for (size_t j{ i + 1 }; j < mSize; ++j)
				{
					mArray[j - 1] = mArray[j];
				}
			}

			mSize--;

			return true;

		}
	}

	template <typename T, size_t N>
	int FixedVector<T, N>::GetIndex(const T& element) const
	{
		for (size_t i{}; i < mSize; ++i)
		{
			if (mArray[i] == element)
			{
				return static_cast<int>(i);
			}
		}

		return -1;

	}

	template <typename T, size_t N>
	const T& FixedVector<T, N>::Get(size_t index) const
	{
		return mArray[index];
	}

	template <typename T, size_t N>
	T& FixedVector<T, N>::operator[](size_t index) const
	{
		return mArray[index];
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity() const
	{
		return mCapacity;
	}

}