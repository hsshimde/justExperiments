#pragma once

#include <memory>

namespace bst
{
	template<typename T>
	class TreeNode final
	{
	public:
		TreeNode(std::unique_ptr<T> data);
		TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);

		std::unique_ptr<T> Data;
		std::shared_ptr<TreeNode<T>> Left;
		std::shared_ptr<TreeNode<T>> Right;
		std::weak_ptr<TreeNode<T>> Parent;
	};

	template<typename T>
	TreeNode<T>::TreeNode(std::unique_ptr<T> data)
		: Left{}
		, Right{}
		, Parent{}
	{
		Data = std::move(data);
	}

	template<typename T>
	TreeNode<T>::TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data)
		: Parent{ }
		, Right{ nullptr }
		, Left{ nullptr }
	{
		Parent = std::weak_ptr<TreeNode<T>>(parent);
		Data = std::move(data);
	}
}