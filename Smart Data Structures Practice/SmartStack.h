#pragma once
#include <stack>
#include <limits>
#include <cmath>

namespace project
{
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack() = default;
		~SmartStack() = default;
		SmartStack(const SmartStack& rhs) = default;
		SmartStack& operator=(const SmartStack& rhs) = default;

		void Push(const T& element);
		T& Peek();
		void Pop();

		T GetMax() const;
		T  GetMin() const;
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;

	private:
		std::stack<T> mMainStack;
		std::stack<T> mMaxStack;
		std::stack<T> mMinStack;
		size_t mSize;
		double mTotalSum;
		double mTotalSquaredSum;
		

	};
}

namespace project
{
	template <typename T>
	void SmartStack<T>::Push(const T& element)
	{
		if (mSize < 1)
		{
			mMaxStack.push(element);
			mMinStack.push(element);
		}

		else
		{
			if (element>=mMaxStack.top())
			{
				mMaxStack.push(element);
			}
			if (element <= mMinStack.top())
			{
				mMinStack.push(element);
			}
		}
		mMainStack.push(element);
		mTotalSum += element;
		mTotalSquaredSum += static_cast<double>(element * element);
		mSize++;
	}


	template <typename T>
	T& SmartStack<T>::Peek() 
	{
		return mMainStack.top();
	}

	template <typename T>
	void SmartStack<T>::Pop()
	{
		T& top = mMainStack.top();
		if (top>=mMaxStack.top())
		{
			mMaxStack.pop();
		}
		if (top<=mMinStack.top())
		{
			mMinStack.pop();
		}
		mTotalSum -= top;
		mTotalSquaredSum -= top * top;
		mSize--;
		return mMainStack.pop();
	}

	template <typename T>
	T SmartStack<T>::GetMax() const
	{
		if (mSize<1)
		{
			return std::numeric_limits<T>::lowest();
		}
		else
		{
			return mMaxStack.top();
		}
	}

	template <typename T>
	T SmartStack<T>::GetMin() const
	{
		if (mSize<1)
		{
			return std::numeric_limits<T>::max();
		}
		else
		{
			return mMinStack.top();
		}
	}

	template <typename T>
	double SmartStack<T>::GetAverage() const
	{
		return mTotalSum / static_cast<double>(mSize);
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		double average = GetAverage();
		double variance = mTotalSquaredSum / static_cast<double>(mSize) - average * average;
		return variance;
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		double variance = GetVariance();
		return std::sqrt(variance);
	}
}