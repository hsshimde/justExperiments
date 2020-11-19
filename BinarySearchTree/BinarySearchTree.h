#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;
		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		static void traverseInOrderRecursive(const std::shared_ptr<TreeNode<T>>, std::vector<T>& v);
		std::shared_ptr<TreeNode<T>> mRoot;
		

	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(data);
			return;
		}

		auto targetNode{ mRoot };
		auto left{ targetNode.Left };
		auto right{ targetNode.Right };

		while (true)
		{
			if (*data <= *(*targetNode).Data)
			{
				if (left == nullptr)
				{
					(*targetNode).Left = std::make_shared<TreeNode<T>>(targetNode, data);
					return;
				}

				else
				{
					targetNode = (*targetNode).Left;
					left = (*targetNode).Left;
					right = (*targetNode).Right;
				}


			}

			else
			{
				if (right == nullptr)
				{
					(*targetNode).Right = std::make_shared<TreeNode<T>>(targetNode, data);
					return;
				}

				else
				{
					targetNode = (*targetNode).Right;
					left = (*targetNode).Left;
					right = (*targetNode).Right;
				}

			}
		}

	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return std::weak_ptr<TreeNode<T>>(mRoot);
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		if (mRoot == nullptr)
		{
			return false;
		}

		auto targetNode{ mRoot };
		auto left{ targetNode.Left };
		auto right{ targetNode.Right };

		while (true)
		{
			if (data == *(*targetNode).Data)
			{
				return true;
			}

			else if (data < *(*targetNode).Data)
			{
				if (left == nullptr)
				{
					return false;
				}

				else
				{
					targetNode = (*targetNode).Left;
					left = (*targetNode).Left;
					right = (*targetNode).Right;
				}
			}

			else
			{
				if (right == nullptr)
				{
					return false;
				}

				else
				{
					targetNode = (*targetNode).Right;
					left = (*targetNode).Left;
					right = (*targetNode).Right;
				}

			}
		}
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		return false;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{

		std::vector<T> v;
		if (mRoot != nullptr)
		{
			traverseInOrderRecursive(std::make_shared<TreeNode<T>>(mRoot), v);
		}

		return v;
	}

	template <typename T>
	void BinarySearchTree<T>::traverseInOrderRecursive(const std::shared_ptr<TreeNode<T>> node, std::vector<T>& v)
	{
		if ((*node).Left != nullptr)
		{
			traverseInOrderRecursive((*node).Left, v);
		}

		v.push_back(*(*node).Data);

		if ((*node).Right != nullptr)
		{
			traverseInOrderRecursive((*node).Right, v);
		}

	}
}