#pragma once
#include <iostream>

namespace bst
{
	template <typename T>
	class TreeNode
	{
		TreeNode(const T element);
		TreeNode(T* parent, const T element);

		

		T Data;
		T* Parent;
		T* Right;
		T* Left;
	};

}