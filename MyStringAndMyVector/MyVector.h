#pragma once
#include <iostream>

namespace project
{
	template <typename T>
	class MyVector
	{	
	public:
		MyVector() = delete;
		MyVector(size_t elementCount);
		MyVector(const MyVector& rhs);
		MyVector(MyVector&& rhs);
		
		MyVector& operator=(const MyVector& rhs);
		MyVector& operator=(MyVector&& rhs);
		

		~MyVector();

		void resize(size_t elementCount);
		size_t size() const;


	private:
		T* mData;
		size_t mSize;
		size_t mCapacity;

	};
}


namespace project
{
	template <typename T>
	MyVector<T>::MyVector()
		: mData()
		, mSize()
		, mCapacity(15)
	{
		mData = new T[mCapacity];
	}

	template <typename T>
	MyVector<T>::MyVector(size_t elementCount)
		: mData()
		, mSize()
		, mCapacity(elementCount)
	{
		mData = new T[mCapacity];
	}

	template <typename T>
	MyVector<T>::~MyVector()
	{
		delete mData;
	}

	template <typename T>
	void MyVector<T>::resize(size_t elementCount)
	{
		if (mCapacity >= elementCount)
		{
			return;
		}
		else
		{
			T* newData = new T[elementCount];
			for (size_t i = 0; i < mSize; i++)
			{
				newData[i] = mData[i];
			}
			delete mData;
			mData = newData;
			return;
		}
	}

	template <typename T>
	size_t MyVector<T>::size() const
	{
		return mSize;
	}

}