#pragma once
#include <utility>
namespace stack
{
	using Data = double;
	const size_t MAXSIZE = 30;

	using DataAndBool = std::pair<Data&, bool>;
	
	class Stack
	{
	public:
		Stack();
		Stack(size_t stackSize);
		~Stack();
		Stack(const Stack& stack) = delete;
		bool checkEmpty() const;
		bool checkFull() const;
		bool push(const Data& rhs);
		bool pop();
		bool peek(Data& rhs) const;

		Stack& operator==(const Stack& stack) = delete;


	private:
		size_t getMaxSize() const;
		size_t getStackSize() const;

		Data* mArray;
		size_t mSize;
		const size_t mMaxSize;

	};
}