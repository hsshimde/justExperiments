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
		QueueStack(const QueueStack& rhs);
		QueueStack(QueueStack&& rhs);
		~QueueStack();
		QueueStack& operator=(const QueueStack& rhs);
		QueueStack& operator=(QueueStack&& rhs);

		T GetMax();
		T GetMin();
		double GetAverage();

	private:
		std::queue<SmartStack<T>> mQueueStack;
		size_t mMaxStackSize;
		size_t mSize;
		
		
		
		
	};
}