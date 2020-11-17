#pragma once
#include <queue>
#include <cmath>	
#include <cassert>

namespace project
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		SmartQueue(const SmartQueue& rhs);
		virtual ~SmartQueue();
		SmartQueue& operator=(const SmartQueue& rhs);

		void Enqueue(const T element);
		T Peek() const;
		T Dequeue();
		T GetSum() const;
		T GetMax();
		T GetMin();
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;

	private:
		std::queue<T> mPrivateQueue;
		T mTotalSum;
		double mTotoalSquaredSum;
	};
}

namespace project
{
	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mPrivateQueue{}
		, mTotalSum{}
		, mTotoalSquaredSum{}
	{

	}

	template <typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue& rhs)
		: mPrivateQueue{ rhs.mPrivateQueue }
		, mTotalSum{ rhs.mTotalSum }
		, mTotoalSquaredSum{ rhs.mTotoalSquaredSum }
	{

	}

	template <typename T>
	SmartQueue<T>::~SmartQueue()
	{

	}

	template <typename T>
	SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue& rhs)
	{
		if (mPrivateQueue != rhs.mPrivateQueue)
		{
			mPrivateQueue = rhs.mPrivateQueue;
			mTotalSum = rhs.mTotalSum;
			mTotoalSquaredSum = rhs.mTotoalSquaredSum;
		}
		return *this;
	}

	template <typename T>
	T SmartQueue<T>::Peek() const
	{
		assert(!mPrivateQueue.empty());
		return mPrivateQueue.front();
	}

	template <typename T>
	void SmartQueue<T>::Enqueue(const T element)
	{
		mTotalSum += element;
		mTotoalSquaredSum += static_cast<double>(element) * static_cast<double>(element);
		return mPrivateQueue.push(element);
	}

	template <typename T>
	T SmartQueue<T>::Dequeue()
	{
		assert(!mPrivateQueue.empty());
		const T frontElement{ mPrivateQueue.front() };
		mPrivateQueue.pop();

		mTotalSum -= frontElement;
		mTotoalSquaredSum -= static_cast<double>(frontElement) * static_cast<double>(frontElement);

		return frontElement;
	}

	template <typename T>
	T SmartQueue<T>::GetSum() const
	{
		return mTotalSum;
	}

	template <typename T>
	T SmartQueue<T>::GetMax()
	{
		if (mPrivateQueue.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		else
		{
			T max{ mPrivateQueue.front() };
			mPrivateQueue.push(mPrivateQueue.front());
			mPrivateQueue.pop();

			size_t queueSize{ mPrivateQueue.size() };

			for (size_t i{}; i < queueSize - 1; ++i)
			{
				T compareElement{ mPrivateQueue.front() };

				if (max < compareElement)
				{
					max = compareElement;
				}

				mPrivateQueue.push(compareElement);
				mPrivateQueue.pop();
			}
			return max;
		}
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mPrivateQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		else
		{
			T min{ mPrivateQueue.front() };
			mPrivateQueue.push(min);
			mPrivateQueue.pop();

			size_t queueSize{ mPrivateQueue.size() };

			for (size_t i{}; i < queueSize - 1; ++i)
			{
				T compareElement{ mPrivateQueue.front() };

				if (min > compareElement)
				{
					min = compareElement;
				}

				mPrivateQueue.push(compareElement);
				mPrivateQueue.pop();
			}

			return min;
		}
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		assert(!mPrivateQueue.empty());
		double average{ static_cast<double>(mTotalSum) / mPrivateQueue.size() };
		double averageRoundedAtFourth{ std::round(average * 1000.0) / 1000.0 };

		return averageRoundedAtFourth;
	}

	template <typename T>
	double SmartQueue<T>::GetVariance() const
	{
		assert(!mPrivateQueue.empty());
		size_t elementCount{ mPrivateQueue.size() };
		double average{ static_cast<double>(mTotalSum) / elementCount };
		double variance{ mTotoalSquaredSum / elementCount - average * average };
		double varianceRoundedAtFourth{ std::round(variance * 1000.0) / 1000.0 };

		return varianceRoundedAtFourth;
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mPrivateQueue.empty());
		size_t elementCount{ mPrivateQueue.size() };
		double average{ static_cast<double>(mTotalSum) / elementCount };
		double variance{ mTotoalSquaredSum / elementCount - average * average };
		double standardDeviation{ std::sqrt(variance) };
		double standardDeviationRoundedAtFourth{ std::round(standardDeviation * 1000.0) / 1000.0 };

		return standardDeviationRoundedAtFourth;

	}
}