#pragma once
#include <stack>

namespace smartstack
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
		T& Peek() const;
		void Pop();

		const T& GetMax() const;
		const T& GetMin() const;
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;

	private:
		std::stack<T> mMainStack;
		std::stack<T> mMaxStack;
		std::stack<T> mMinStack;
		size_t mSize;
		

	};
}

namespace smartstack
{
	template <typename T>
	void SmartStack<T>::Push(const T& element)
	{
		if (mSize < 1)
		{
			mMaxStack.push(element);
			mMinStack.push(element);
		}
		mMainStack.push(element);
		mSize++;
	}
}