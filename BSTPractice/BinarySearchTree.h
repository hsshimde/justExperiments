#pragma once
#include <vector>	
#include "TreeNode.h"
namespace bst
{
	template <typename T>
	class BinarySearchTree
	{
	public:
		void Insert(const T& element);
		bool Delete(const T& element);
		bool Search(const T& element);
		std::vector<T> GetDataInOrder(const T& element);



	private:
		TreeNode* insertRecursive(const T& element, TreeNode* parent, TreeNode* node);
		TreeNode* searchRecursiveNullable(const T& element, const TreeNode* node);
		//bool deleteRecursive(TreeNode* targetNode);
		void traverseInOrderRecursive(const TreeNode<T>* node, std::vector<T>& v);

		TreeNode* mRoot;
	};
}

namespace bst
{
	template <typename T>
	void BinarySearchTree<T>::Insert(const T& element)
	{
		mRoot = insertRecursive(element, nullptr, mRoot);
	}

	template <typename T>
	TreeNode<T>* BinarySearchTree<T>::insertRecursive(const T& element, TreeNode<T>* parent, TreeNode<T>* node)
	{
		if (node == nullptr)
		{
			return new TreeNode<T>(parent, node);
		}

		else if (element <= node->Data)
		{
			node->Left = insertRecursive(element, node, node->Left);
		}

		else
		{
			node->Right = insertRecursive(element, node, node->Right);
		}

		return node;
	}

	template <typename T>
	bool BinarySearchTree<T>::Search(const T& element)
	{
		TreeNode<T>* target{ searchRecursiveNullable(element, mRoot) };

		if (target != nullptr)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	template <typename T>
	TreeNode<T>* BinarySearchTree<T>::searchRecursiveNullable(const T& element, const TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			if (element == node->Data)
			{
				return node;
			}

			else if (element < node->Data)
			{
				return searchRecursiveNullable(element, node->Left);
			}

			else
			{
				return searchRecursiveNullable(element, node->Right);
			}
		}

		else
		{
			return nullptr;
		}
	}

	template <typename T>
	std::vector<T> BinarySearchTree<T>::GetDataInOrder(const T& element)
	{
		std::vector<T> v{};
		TreeNode<T>* startNode{ searchRecursiveNullable(element, mRoot) };

		if (startNode != nullptr)
		{
			traverseInOrderRecursive(startNode, v);
		}

		return v;

	}

	template <typename T>
	void BinarySearchTree<T>::traverseInOrderRecursive(const TreeNode<T>* node, std::vector<T>& v)
	{
		if (node->Left != nullptr)
		{
			traverseInOrderRecursive(node->Left, v);
		}

		v.push_back(node->)
	}

	template <typename T>
	bool BinarySearchTree<T>::Delete(const T& element)
	{
		TreeNode<T>* targetNode{ Search(element) };

		if (targetNode != nullptr)
		{
			TreeNode<T>* right{ targetNode->Right };
			TreeNode<T>* left{ targetNode->Left };

			if (right == nullptr && left == nullptr)
			{
				if (targetNode == mRoot)
				{
					delete mRoot;
					mRoot = nullptr;

					return true;
				}

				else
				{
					TreeNode<T>* parent{ targetNode->Parent };

					if (targetNode == parent->Right)
					{
						parent->Right = nullptr;

					}

					else
					{
						parent->Left = nullptr;
					}

					delete targetNode;

					return true;
				}
			}

			else if (right == nullptr)
			{
				if (targetNode == mRoot)
				{
					mRoot = left;
					
				}

				else
				{

				}
			}
		}

		else
		{
			return false;
		}
	}

	
}