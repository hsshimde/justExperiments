#pragma once

#include "SmartQueue.h"
#include "SmartStack.h"


namespace project
{	
	template <typename T>
	class QueueStack
	{
	public:
		QueueStack(size_t stackSize);
		QueueStack(QueueStack& rhs);
		//QueueStack(QueueStack&& rhs);
		~QueueStack();

		QueueStack& operator=(QueueStack& rhs);
		//QueueStack& operator=(QueueStack&& rhs);

		T GetMax();
		T GetMin();
		double GetAverage() const;

	private:
		std::queue<SmartStack<T>*> mQueueStack;
		size_t mMaxStackSize;
		size_t mSize;
		double mTotalSum;
	};
}

namespace project
{
	template <typename T>
	QueueStack<T>::QueueStack(size_t stackSize)
		: mQueueStack()
		, mMaxStackSize(stackSize)
		, mSize()
		, mTotalSum()
	{

	}

	template <typename T>
	QueueStack<T>::QueueStack(QueueStack& rhs)
		: mQueueStack()
		, mMaxStackSize(rhs.mMaxStackSize)
		, mSize(rhs.mSize)
		, mTotalSum(rhs.mTotalSum)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mQueueStack.push(new SmartStack<T>(*rhs.mQueueStack.front()));
			rhs.mQueueStack.push(rhs.mQueueStack.front());
			rhs.mQueueStack.pop();
		}
	}

	

	template <typename T>
	QueueStack<T>::~QueueStack()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			delete mQueueStack.front();
			mQueueStack.pop();
		}
	}

	template <typename T>
	QueueStack<T>& QueueStack<T>::operator=(QueueStack& rhs)
	{
		if (this != &rhs)
		{
			for (size_t i = 0; i < mSize; i++)
			{
				delete mQueueStack.front();
				mQueueStack.pop();
			}
			mSize = rhs.mSize;
			for (size_t i = 0; i < mSize; i++)
			{
				mQueueStack.push(new SmartStack<T>(*rhs.mQueueStack.front()));
				rhs.mQueueStack.pop();
			}
			mTotalSum = rhs.mTotalSum;
		}
		return *this;
	}

	template <typename T>
	T QueueStack<T>::GetMax()
	{
		T max = mQueueStack.front().GetMax();
		mQueueStack.push(mQueueStack.front());
		mQueueStack.pop();
		for (size_t i = 0; i < mSize-1; i++)
		{
			if (max < mQueueStack.front().GetMax())
			{
				max = mQueueStack.front().GetMax();
			}
			mQueueStack.push(mQueueStack.front());
			mQueueStack.pop();
		}
		return max;
	}

	template <typename T>
	T QueueStack<T>::GetMin()
	{
		T min = mQueueStack.front().GetMin();
		mQueueStack.push(mQueueStack.front());
		mQueueStack.pop();
		for (size_t i = 0; i < mSize-1; i++)
		{
			if (min > mQueueStack.front().GetMin())
			{
				min = mQueueStack.front().GetMin();
			}
			mQueueStack.push(mQueueStack.front());
			mQueueStack.pop();
		}
		return min;
	}

	template <typename T>
	double QueueStack<T>::GetAverage() const
	{
		return mTotalSum / mSize;
	}
}