#include "Stack.h"

namespace stack
{
	Stack::Stack()
		:mMaxSize{ MAXSIZE }
		, mSize{ 0 }
	{
		mArray = new Data[mMaxSize];
	}

	Stack::Stack(size_t stackSize)
		:mMaxSize{ stackSize }
		, mSize{ 0 }
	{
		mArray = new Data[mMaxSize];
	}

	Stack::~Stack()
	{
		delete[] mArray;
	}

	bool Stack::checkEmpty() const
	{
		if (getStackSize() <= 0)
		{
			return true;
		}

		else
		{
			return false;
		}

	}

	bool Stack::checkFull() const
	{
		if (getStackSize() >= getMaxSize())
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool Stack::push(const Data& rhs)
	{
		if (checkFull())
		{
			return false;
		}

		mArray[mSize++] = rhs;
		return true;

	}

	bool Stack::pop()
	{
		if (checkEmpty())
		{
			return false;
		}

		--mSize;
		return true;
	}

	bool Stack::peek(Data& rhs) const
	{
		if (checkEmpty())
		{
			return false;
		}

		rhs = mArray[mSize - 1];
		return true;

	}

	size_t Stack::getMaxSize() const
	{
		return mMaxSize;
	}

	size_t Stack::getStackSize() const
	{
		return mSize;
	}


}