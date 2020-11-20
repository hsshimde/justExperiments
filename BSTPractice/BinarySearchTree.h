#pragma once

namespace bst
{
	template <typename T>
	class BinarySearchTree
	{
	public:
		void Insert(const T element);
		


	private:
		T* mRoot;
	};
}