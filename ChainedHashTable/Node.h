#pragma once


namespace node
{
	typedef size_t Data;
	
	class Node
	{
	public:
		Node(const Data data);
		Node(const Node& rhs) = delete;
		Node& operator=(const Node& rhs) = delete;
		~Node();

		Node* GetNext() const;
		Node*& GetNext();
		const Data GetData() const;


	private:
		Node* mNext;
		Data mData;

	};
}