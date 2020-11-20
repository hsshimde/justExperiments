#pragma once

#include <memory>
#include <vector>

namespace bst
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
		bool Clear();

	private:
		static void traverseInOrderRecursive(std::shared_ptr<TreeNode<T>>, std::vector<T>& v);
		std::shared_ptr<TreeNode<T>> mRoot;


	};


	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::make_unique<T>(*data));
			return;
		}

		std::shared_ptr<TreeNode<T>> targetNode{ mRoot };
		std::shared_ptr<TreeNode<T>> left{ (*targetNode).Left };
		std::shared_ptr<TreeNode<T>> right{ (*targetNode).Right };

		while (true)
		{
			if (*data <= *(*targetNode).Data)
			{
				if (left == nullptr)
				{
					(*targetNode).Left = std::make_shared<TreeNode<T>>(targetNode, std::make_unique<T>(*data));
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
					(*targetNode).Right = std::make_shared<TreeNode<T>>(targetNode, std::make_unique<T>(*data));
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
		auto left{ (*targetNode).Left };
		auto right{ (*targetNode).Right };

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
		if (mRoot == nullptr)
		{
			return false;
		}

		auto targetNode{ mRoot };
		auto left{ (*targetNode).Left };
		auto right{ (*targetNode).Right };

		while (true)
		{
			if (data == *(*targetNode).Data)
			{
				if (right == nullptr && left == nullptr)
				{
					if (targetNode == mRoot)
					{
						mRoot = nullptr;
						return true;
					}

					else
					{
						auto parent{ (*targetNode).Parent.lock() };

						if (targetNode == (*parent).Right)
						{
							(*parent).Right = nullptr;
						}

						else
						{
							(*parent).Left = nullptr;
						}

						targetNode = nullptr;

						return true;

					}

				}

				else if (right == nullptr)
				{
					if (targetNode == mRoot)
					{

						(*left).Parent.reset();
						mRoot = left;
						targetNode = nullptr;
						return true;
					}

					else
					{
						auto parent{ (*targetNode).Parent.lock() };
						std::weak_ptr<TreeNode<T>> newParent{ parent };

						if (targetNode == (*parent).Right)
						{
							(*parent).Right = left;
						}

						else
						{
							(*parent).Left = left;
						}

						(*left).Parent.swap(newParent);
						targetNode = nullptr;
						return true;

					}

				}

				else
				{
					auto deleteTarget{ right };

					while ((*deleteTarget).Left != nullptr)
					{
						deleteTarget = (*deleteTarget).Left;
					}

					*(*targetNode).Data = *(*deleteTarget).Data;

					std::shared_ptr<TreeNode<T>> deleteTargetParent{ (*deleteTarget).Parent.lock() };

					if ((*deleteTargetParent).Right == deleteTarget)
					{
						if ((*deleteTarget).Right != nullptr)
						{
							std::weak_ptr<TreeNode<T>> newParent{ deleteTargetParent };
							std::shared_ptr<TreeNode<T>> deleteTargetRight{ (*deleteTarget).Right };
							(*deleteTargetRight).Parent.swap(newParent);
							(*deleteTargetParent).Right = deleteTargetRight;
						}

						else
						{
							(*deleteTargetParent).Right = nullptr;
						}

						deleteTarget = nullptr;

						return true;
					}

					else
					{
						if ((*deleteTarget).Right != nullptr)
						{
							std::weak_ptr<TreeNode<T>> newParent{ deleteTargetParent };
							std::shared_ptr<TreeNode<T>> deleteTargetRight{ (*deleteTarget).Right };
							(*deleteTargetRight).Parent.swap(newParent);
							(*deleteTargetParent).Left = deleteTargetRight;
						}

						else
						{
							(*deleteTargetParent).Left = nullptr;
						}

						deleteTarget = nullptr;

					}

					return true;
				}

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


		return false;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		if (startNode != nullptr)
		{
			traverseInOrderRecursive(startNode, v);
		}

		return v;
	}

	template <typename T>
	void BinarySearchTree<T>::traverseInOrderRecursive(std::shared_ptr<TreeNode<T>> node, std::vector<T>& v)
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

		return;

	}

	template <typename T>
	bool BinarySearchTree<T>::Clear()
	{
		if (mRoot != nullptr)
		{
			mRoot = nullptr;
			return true;
		}

		else
		{
			return false;
		}
	}
}