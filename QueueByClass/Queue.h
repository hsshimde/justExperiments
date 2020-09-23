#pragma once
namespace queue
{
	
	using Data = double;

	struct Node
	{
		Data data{};
		Node* next;
	};

	using Nodeptr = Node*;
	const size_t QSIZE = 10;


	class Queue
	{

	public:
		Queue();
		Queue(size_t qSize);
		Queue(const Queue& rhs) = delete;
		Queue& operator=(const Queue& rhs) = delete;
		~Queue();
		bool CheckEmpty() const;
		bool CheckFull() const;
		size_t GetQueueCount() const;
		bool Enqueue(const Data& rhs);
		bool Dequeue(Data& rhs);

	private:
		Nodeptr mFront;
		Nodeptr mRear;
		size_t mDataCount;
		const size_t mQsize;
		
	};
}