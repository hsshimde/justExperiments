#pragma once

#include <memory>

namespace lab11
{
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length);
		Storage(unsigned int length, const T& initialValue);
		Storage(const Storage& rhs);

		Storage& operator=(const Storage& rhs);
		Storage(Storage&& rhs);
		Storage& operator=(Storage&& rhs);

		bool Update(unsigned int index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		unsigned int GetSize() const;

	private:
		std::unique_ptr<T[]> mData;
		size_t mSize;
	};

	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mData(std::make_unique<T[]>(length))
		, mSize(length)
	{
		
	}

	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mData(std::make_unique<T[]>(length))
		, mSize(length)
	{
		for (size_t i = 0; i < length; i++)
		{
			mData[i] = initialValue;
		}
	}

	template <typename T>
	Storage<T>& Storage<T>::operator=(const Storage& rhs)
	{
		if (this != &rhs)
		{
			mData.reset(nullptr);
			mSize = rhs.mSize;
			mData = std::make_unique<T[]>(mSize);
			for (size_t i = 0; i < mSize; i++)
			{
				mData[i] = rhs.mData[i];
			}
		}
		return *this;
		
	}

	template <typename T>
	Storage<T>::Storage(Storage&& rhs)
	{
		mSize = rhs.mSize;
		rhs.mSize = 0;
		mData = std::move(rhs.mData);
	}

	template <typename T>
	Storage<T>& Storage<T>::operator=(Storage&& rhs)
	{
		if (this != &rhs)
		{
			mData.reset(nullptr);
			mSize = rhs.mSize;
			rhs.mSize = 0;
			mData = std::move(rhs.mData);
		}
		return	*this;
	}

	template <typename T>
	Storage<T>::Storage(const Storage& rhs)
		: mData()
		, mSize(rhs.mSize)
	{
		mData.reset(nullptr);
		mData = std::make_unique<T[]>(mSize);

		for (size_t i = 0; i < mSize; i++)
		{
			mData[i] = rhs.mData[i];
		}
	}

	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize)
		{
			return false;
		}

		else
		{
			mData[index] = data;
			return true;
		}
	}

	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return std::move(mData);
	}

	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize;
	}
}
