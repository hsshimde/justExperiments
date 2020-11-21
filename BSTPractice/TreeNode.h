#pragma once
#include <iostream>

namespace bst
{
	template <typename T>
	class TreeNode
	{
		TreeNode(const T& element);
		TreeNode(T* parent, const T& element);

		

		T Data;
		T* Parent;
		T* Right;
		T* Left;
	};


	template <typename T>
	TreeNode<T>::TreeNode(const T& element)
		: Parent{nullptr}
		, Right{nullptr}
		, Left{nullptr}
	{
		Data = element;
	}

	template <typename T>
	TreeNode<T>::TreeNode(T* parent, const T& element)	
		: Parent{parent}
		, Right{ nullptr }
		, Left{ nullptr }
	{
		Data = element;
	}

}