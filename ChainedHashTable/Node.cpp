#include "Node.h"

namespace node
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


	Node* Node::GetNext() const
	{
		return mNext;
	}

	Node*& Node::GetNext()
	{
		return mNext;
	}

	const Data Node::GetData() const
	{
		return mData;
	}

}