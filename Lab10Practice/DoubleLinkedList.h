#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;

	private:
		std::shared_ptr<Node<T>> mHead;
		size_t mLength;
	};

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mHead(nullptr)
		, mLength()
	{

	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		if (mLength < 1)
		{
			mHead = std::make_shared<Node<T>>(std::move(data));
		}

		else
		{
			std::shared_ptr<Node<T>> tempNode = mHead;
			while (tempNode->Next != nullptr)
			{
				tempNode = tempNode->Next;
			}
			tempNode->Next = std::make_shared<Node<T>>(std::move(data), tempNode);
		}
		mLength++;
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (index >= mLength)
		{
			if (mHead != nullptr)
			{
				mHead = std::make_shared<Node<T>>(std::move(data));
			}

			else
			{
				std::shared_ptr<Node<T>> tempNode = mHead;
				while (tempNode->Next != nullptr)
				{
					tempNode = tempNode->Next;
				}
				tempNode->Next = std::make_shared<Node<T>>(std::move(data), tempNode);
			}
		}

		else
		{
			if (index != 0)
			{
				std::shared_ptr<Node<T>> tempNode = mHead;
				for (size_t i = 0; i < index - 1; i++)
				{
					tempNode = tempNode->Next;
				}
				std::shared_ptr<Node<T>> originalIndexNode = tempNode->Next;
				tempNode->Next = std::make_shared<Node<T>>(std::move(data), tempNode);
				std::shared_ptr<Node<T>> newIndexNode = tempNode->Next;
				originalIndexNode->Previous = std::weak_ptr<Node<T>>(newIndexNode);

			}
			else
			{
				std::shared_ptr<Node<T>> newHead = std::make_shared<Node<T>>(std::move(data));
				newHead->Next = mHead;
				mHead->Previous = std::weak_ptr<Node<T>>(newHead);
				mHead = newHead;
			}

		}
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		if (mLength < 1)
		{
			return false;
		}

		std::shared_ptr<Node<T>> tempNode = mHead;
		while (*tempNode->Data != data)
		{
			if (tempNode->Next == nullptr)
			{
				return false;
			}
			tempNode = tempNode->Next;
		}
		if (tempNode->Next != nullptr)
		{
			std::shared_ptr<Node<T>> previousNode = tempNode->Previous.lock();
			std::shared_ptr<Node<T>> nextNode = tempNode->Next;
			previousNode->Next = nextNode;
			nextNode->Previous = std::weak_ptr<Node<T>>(previousNode);
			tempNode.reset(nullptr);
		}
		else
		{
			std::shared_ptr<Node<T>> previousNode = tempNode->Previous.lock();
			previousNode->Next = nullptr;
		}
		mLength--;
		return true;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		if (mLength < 1)
		{
			return false;
		}

		std::shared_ptr<Node<T>> tempNode = mHead;
		while (*tempNode->Data != data)
		{
			if (tempNode->Next == nullptr)
			{
				return false;
			}
			tempNode = tempNode->Next;
		}

		return true;

	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (mLength <= index)
		{
			return nullptr;
		}

		std::shared_ptr<Node<T>> tempNode = mHead;
		for (size_t i = 0; i < index; i++)
		{
			tempNode = tempNode->Next;
		}
		return tempNode;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}
