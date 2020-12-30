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
		QueueStack(QueueStack&& rhs);
		~QueueStack();

		QueueStack& operator=(const QueueStack& rhs);
		QueueStack& operator=(QueueStack&& rhs);

		T GetMax();
		T GetMin();
		double GetAverage();

	private:
		std::queue<SmartStack<T>*> mQueueStack;
		size_t mMaxStackSize;
		size_t mSize;
		
	};
}

namespace project
{
	template <typename T>
	QueueStack<T>::QueueStack(size_t stackSize)
		: mQueueStack()
		, mMaxStackSize(stackSize)
		, mSize()	
	{

	}

	template <typename T>
	QueueStack<T>::QueueStack(QueueStack& rhs)
		: mQueueStack()
		, mMaxStackSize(rhs.mMaxStackSize)
		, mSize(rhs.mSize)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mQueueStack.push(new SmartStack<T>(*rhs.mQueueStack.front()));
			rhs.mQueueStack.push(rhs.mQueueStack.front());
			rhs.mQueueStack.pop();
		}
	}

	template <typename T>
	QueueStack<T>::QueueStack(QueueStack&& rhs)
		: mQueueStack()
		, mMaxStackSize(rhs.mMaxStackSize)
		, mSize(rhs.mSize)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mQueueStack.push(std::move(rhs.mQueueStack.front()));
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
	QueueStack<T>& QueueStack<T>::operator=(const QueueStack& rhs)
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
			}
		}
	}
}