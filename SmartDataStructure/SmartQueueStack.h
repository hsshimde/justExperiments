#pragma once
#include <cassert>
#include <queue>
#include "SmartStack.h"

namespace project
{
	template <typename T>
	class SmartQueueStack
	{
	public:
		SmartQueueStack(size_t maxStackSize);
		SmartQueueStack(SmartQueueStack& rhs);
		virtual ~SmartQueueStack();
		SmartQueueStack& operator=(SmartQueueStack& rhs);


		void Enqueue(const T element);
		T Peek() const;
		T Dequeue();
		T GetMax();
		T GetMin();
		size_t GetCount() const;
		size_t GetStackCount() const;
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;

	private:
		std::queue<SmartStack<T>*> mPrivateSmartQueueStack;
		size_t mMaxStackSize;
		T mTotalSum;
		double mTotoalSquaredSum;
		size_t mElementCount;

	};
}

namespace project
{
	template <typename T>
	SmartQueueStack<T>::SmartQueueStack(size_t maxStackSize)
		: mPrivateSmartQueueStack{}
		, mTotalSum{}
		, mElementCount{}
		, mMaxStackSize{ maxStackSize }
		, mTotoalSquaredSum{}
	{

	}

	template <typename T>
	SmartQueueStack<T>::SmartQueueStack(SmartQueueStack& rhs)
		: mPrivateSmartQueueStack{}
		, mTotalSum{ rhs.mTotalSum }
		, mMaxStackSize{ rhs.mMaxStackSize }
		, mElementCount{ rhs.mElementCount }
		, mTotoalSquaredSum{ rhs.mTotoalSquaredSum }
	{
		size_t stackCount{ rhs.mPrivateSmartQueueStack.size() };

		for (size_t i{}; i < stackCount; ++i)
		{
			mPrivateSmartQueueStack.push(new SmartStack<T>(*rhs.mPrivateSmartQueueStack.front()));
			rhs.mPrivateSmartQueueStack.push(rhs.mPrivateSmartQueueStack.front());
			rhs.mPrivateSmartQueueStack.pop();
		}
	}

	template <typename T>
	SmartQueueStack<T>::~SmartQueueStack()
	{
		size_t stackCount{ mPrivateSmartQueueStack.size() };

		for (size_t i{}; i < stackCount; ++i)
		{
			delete mPrivateSmartQueueStack.front();
			mPrivateSmartQueueStack.pop();
		}
	}

	template <typename T>
	SmartQueueStack<T>& SmartQueueStack<T>::operator=(SmartQueueStack& rhs)
	{
		if (this != &rhs)
		{
			mMaxStackSize = rhs.mMaxStackSize;
			mTotalSum = rhs.mTotalSum;
			mElementCount = rhs.mElementCount;
			mTotoalSquaredSum = rhs.mTotoalSquaredSum;

			size_t stackCount{ mPrivateSmartQueueStack.size() };

			for (size_t i{}; i < stackCount; ++i)
			{
				mPrivateSmartQueueStack.push(new SmartStack<T>(*rhs.mPrivateSmartQueueStack.front()));
				rhs.mPrivateSmartQueueStack.push(rhs.mPrivateSmartQueueStack.front());
				rhs.mPrivateSmartQueueStack.pop();
			}
		}
	}

	template <typename T>
	void SmartQueueStack<T>::Enqueue(const T element)
	{
		if (mPrivateSmartQueueStack.empty() || mPrivateSmartQueueStack.back()->GetCount() >= mMaxStackSize)
		{
			mPrivateSmartQueueStack.push(new SmartStack<T>());
		}

		mPrivateSmartQueueStack.back()->Push(element);
		mTotalSum += element;
		mTotoalSquaredSum += element * element;
		mElementCount++;
		return;
	}

	template <typename T>
	T SmartQueueStack<T>::Peek() const
	{
		assert(!mPrivateSmartQueueStack.empty());
		return mPrivateSmartQueueStack.front()->Peek();
	}

	template <typename T>
	T SmartQueueStack<T>::Dequeue()
	{
		assert(!mPrivateSmartQueueStack.empty());
		mElementCount--;
		const T frontTop{ mPrivateSmartQueueStack.front().Pop() };

		mTotalSum -= frontTop;
		mTotoalSquaredSum -= frontTop * frontTop;

		return frontTop;
	}

	template <typename T>
	size_t SmartQueueStack<T>::GetCount() const
	{
		return mElementCount;
	}

	template <typename T>
	size_t SmartQueueStack<T>::GetStackCount() const
	{
		return mPrivateSmartQueueStack.size();
	}

	template <typename T>
	T SmartQueueStack<T>::GetMax()
	{
		if (mPrivateSmartQueueStack.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		else
		{
			T max{ mPrivateSmartQueueStack.front()->GetMax() };
			mPrivateSmartQueueStack.push(mPrivateSmartQueueStack.front());
			mPrivateSmartQueueStack.pop();

			size_t queueSize{ mPrivateSmartQueueStack.size() };

			for (size_t i{}; i < queueSize - 1; ++i)
			{
				T compareElement{ mPrivateSmartQueueStack.front()->GetMax() };

				if (max < compareElement)
				{
					max = compareElement;
				}

				mPrivateSmartQueueStack.push(mPrivateSmartQueueStack.front());
				mPrivateSmartQueueStack.pop();
			}

			return max;
		}
	}

	template <typename T>
	T SmartQueueStack<T>::GetMin()
	{
		if (mPrivateSmartQueueStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		else
		{
			T min{ mPrivateSmartQueueStack.front()->GetMin() };

			mPrivateSmartQueueStack.push(mPrivateSmartQueueStack.front());
			mPrivateSmartQueueStack.pop();

			size_t queueSize{ mPrivateSmartQueueStack.size() };

			for (size_t i{}; i < queueSize - 1; ++i)
			{
				T compareElement{ mPrivateSmartQueueStack.front()->GetMin() };

				if (min > compareElement)
				{
					min = compareElement;
				}

				mPrivateSmartQueueStack.push(mPrivateSmartQueueStack.front());
				mPrivateSmartQueueStack.pop();
			}

			return min;

		}

	}

	template <typename T>
	double SmartQueueStack<T>::GetAverage() const
	{
		double average{ static_cast<double>(mTotalSum) / mElementCount };
		double averageRounded{ std::round(average * 1000.0) / 1000.0 };

		return averageRounded;
	}

	template <typename T>
	double SmartQueueStack<T>::GetVariance() const
	{
		assert(!mPrivateSmartQueueStack.empty());
		double average{ static_cast<double>(mTotalSum) / mElementCount };
		double variance{ mTotoalSquaredSum / mElementCount - average * average };
		double varianceRoundedAtFourth{ std::round(variance * 1000.0) / 1000.0 };

		return varianceRoundedAtFourth;

	}

	template <typename T>
	double SmartQueueStack<T>::GetStandardDeviation() const
	{
		assert(!mPrivateSmartQueueStack.empty());
		double average{ static_cast<double>(mTotalSum) / mElementCount };
		double variance{ mTotoalSquaredSum / mElementCount - average * average };
		double standardDeviation{ std::sqrt(variance) };
		double standardDeviationRoundedAtFourth{ std::round(standardDeviation * 1000.0) / 1000.0 };

		return standardDeviationRoundedAtFourth;
	}


}