#pragma once


namespace chainedhash
{
	typedef size_t Data;
	
	class Node
	{
	public:
		Node(const Data data);
		Node(const Node& rhs) = delete;
		Node& operator=(const Node& rhs) = delete;
		~Node();


	private:
		Node* mNext;
		Data mData;

	};
}

namespace chainedhash
{
	
	Node::Node(const Data data)
		: mNext{ nullptr }
		, mData{ data }
	{

	}

	Node::~Node()
	{
		if (mNext != nullptr)
		{
			delete mNext;
		}
	}

}