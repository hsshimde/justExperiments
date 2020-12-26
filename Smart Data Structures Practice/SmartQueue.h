#pragma once

#include <queue>
#include <limits>
#include <cmath>
#include <cassert>

namespace project
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue() = default;
		~SmartQueue() = default;
		SmartQueue(const SmartQueue& rhs) = default;
		SmartQueue& operator=(const SmartQueue& rhs) = default;

		SmartQueue(SmartQueue&& rhs) = default;
		SmartQueue& operator=(SmartQueue&& rhs) = default;

		void Push(const T& element);
		T Peek() const;
		void Pop();

		T GetMax();
		T GetMin();
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;
		
		size_t GetSize() const;

	private:
		std::queue<T> mQueue;
		double mTotalSum;
		double mTotalSquaredSum;
	};
}

namespace project
{
	template <typename T>
	void SmartQueue<T>::Push(const T& element)
	{
		mTotalSquaredSum += static_cast<double>(element * element);
		mTotalSum += static_cast<double>(element);
		mQueue.push(element);
	}

	template <typename T>
	T SmartQueue<T>::Peek() const
	{
		assert(!mQueue.empty());
		return mQueue.front();
	}

	template <typename T>
	void SmartQueue<T>::Pop()
	{
		assert(!mQueue.empty());
		T frontElement = mQueue.front();
		return mQueue.pop();
	}

	template <typename T>
	T SmartQueue<T>::GetMax()
	{
		T max = mQueue.front();
		mQueue.push(max);
		mQueue.pop();
		for (size_t i = 0; i < mQueue.size()-1; i++)
		{
			if (max < mQueue.front())
			{
				max = mQueue.front();
			}
			mQueue.push(mQueue.front());
			mQueue.pop();
		}
		return max;
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		T min = mQueue.front();
		mQueue.push(min);
		mQueue.pop();
		for (size_t i = 0; i < mQueue.size()-1; i++)
		{
			if (min<mQueue.front())
			{
				min = mQueue.front();
			}
			mQueue.push(mQueue.front());
			mQueue.pop();
		}
		return min;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		return static_cast<double>(mTotalSum) / mQueue.size();
	}

	template <typename T>
	double SmartQueue<T>::GetVariance() const
	{
		double average = GetAverage();
		return mTotalSquaredSum / mQueue.size() - average * average;
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		double variance = GetVariance();
		return std::sqrt(variance);
	}

	template <typename T>
	size_t SmartQueue<T>::GetSize() const
	{
		return mQueue.size();
	}

	
}