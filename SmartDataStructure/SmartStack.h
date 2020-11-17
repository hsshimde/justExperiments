#pragma once
#include <stack>
#include <cmath>	
#include <cassert>

namespace project
{
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack();
		SmartStack(const SmartStack& rhs);
		virtual ~SmartStack();
		SmartStack& operator=(const SmartStack& rhs);

		T Peek() const;
		void Push(const T element);
		T Pop();
		T GetSum() const;
		T GetMax() const;
		T GetMin() const;
		size_t GetCount() const;
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;

	private:
		std::stack<T> mPrivateStack;
		std::stack<T> mMaxStack;
		std::stack<T> mMinStack;
		T mTotalSum;
		double mTotalSquaredSum;
	};



}


namespace project
{

	template <typename T>
	SmartStack<T>::SmartStack()
		: mPrivateStack{}
		, mMaxStack{}
		, mMinStack{}
		, mTotalSum{}
		, mTotalSquaredSum{}
	{

	}


	template <typename T>
	SmartStack<T>::SmartStack(const SmartStack& rhs)
		: mPrivateStack{ rhs.mPrivateStack }
		, mMaxStack{ rhs.mMaxStack }
		, mMinStack{ rhs.mMinStack }
		, mTotalSquaredSum{ rhs.mTotalSquaredSum }
		, mTotalSum{ rhs.mTotalSum }
	{

	}

	template <typename T>
	SmartStack<T>::~SmartStack()
	{

	}

	template <typename T>
	SmartStack<T>& SmartStack<T>::operator=(const SmartStack& rhs)
	{
		mPrivateStack = rhs.mPrivateStack;
		mMaxStack = rhs.mMaxStack;
		mMinStack = rhs.mMinStack;
		mTotalSquaredSum = rhs.mTotalSquaredSum;
		mTotalSum = rhs.mTotalSum;
	}

	template <typename T>
	T SmartStack<T>::Peek() const
	{
		assert(!mPrivateStack.empty());
		return mPrivateStack.top();
	}

	template <typename T>
	void SmartStack<T>::Push(const T element)
	{
		if (mPrivateStack.empty())
		{
			mMaxStack.push(element);
			mMinStack.push(element);
		}

		else
		{
			if (element >= mMaxStack.top())
			{
				mMaxStack.push(element);
			}

			if (element <= mMinStack.top())
			{
				mMinStack.push(element);
			}
		}

		mTotalSum += element;
		mTotalSquaredSum += static_cast<double>(element) * static_cast<double>(element);
		return mPrivateStack.push(element);

	}

	template <typename T>
	T SmartStack<T>::Pop()
	{
		assert(!mPrivateStack.empty());
		const T top{ mPrivateStack.top() };
		mPrivateStack.pop();

		if (top >= mMaxStack.top())
		{
			mMaxStack.pop();
		}

		if (top <= mMinStack.top())
		{
			mMinStack.pop();
		}

		mTotalSquaredSum -= static_cast<double>(top) * static_cast<double>(top);
		mTotalSum -= top;

		return top;
	}

	template <typename T>
	T SmartStack<T>::GetMax() const
	{
		if (mPrivateStack.empty())
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
		if (mPrivateStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		else
		{
			return mMinStack.top();
		}

	}


	template <typename T>
	size_t SmartStack<T>::GetCount() const
	{
		return mPrivateStack.size();
	}

	template <typename T>
	double SmartStack<T>::GetAverage() const
	{
		assert(!mPrivateStack.empty());
		double average{ static_cast<double>(mTotalSum) / mPrivateStack.size() };
		double averageRoundedAtFourth{ std::round(average * 1000.0) / 1000.0 };

		return averageRoundedAtFourth;
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		assert(!mPrivateStack.empty());
		double average{ static_cast<double>(mTotalSum) / mPrivateStack.size() };
		double variance{ mTotalSquaredSum / mPrivateStack.size() - average * average };
		double varianceRoundedAtFourth{ std::round(variance * 1000.0) / 1000.0 };

		return varianceRoundedAtFourth;
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		assert(!mPrivateStack.empty());
		double average{ static_cast<double>(mTotalSum) / mPrivateStack.size() };
		double variance{ mTotalSquaredSum / mPrivateStack.size() - average * average };
		double standardDeviation{ std::sqrt(variance) };
		double standardDeviationRoundedAtFourth{ std::round(standardDeviation * 1000.0) / 1000.0 };

		return standardDeviationRoundedAtFourth;
	}

	template <typename T>
	T SmartStack<T>::GetSum() const
	{
		return mTotalSum;
	}

}