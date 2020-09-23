#include "Queue.h"

namespace queue
{
	Queue::Queue()
		:mQsize{ QSIZE }
	{
		mFront = nullptr;
		mRear = nullptr;
		mDataCount = 0;
	}

	Queue::Queue(size_t qsize)
		: mQsize{ qsize }
	{
		mFront = nullptr;
		mRear = nullptr;
		mDataCount = 0;
	}

	Queue::~Queue()
	{
		
		if (CheckEmpty()==true)
		{
			return;
		}

		Nodeptr tmp{ mFront->next };

		if (tmp == nullptr)
		{
			delete mFront;
			return;
		}

		while (tmp != nullptr)
		{
			delete mFront;
			mFront = tmp;
			tmp = mFront->next;
		}

	}

	bool Queue::CheckEmpty() const
	{
		if (mFront == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Queue::CheckFull() const
	{
		if (GetQueueCount()>=mQsize)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	size_t Queue::GetQueueCount() const
	{
		return mDataCount;
	}


	bool Queue::Enqueue(const Data& rhs)
	{
		if (CheckFull()==true)
		{
			return false;
		}

		Nodeptr addNewOne = new Node{};
		addNewOne->data = rhs;
		addNewOne->next = nullptr;

		++mDataCount;

		if (CheckEmpty()==true)
		{
			mFront = addNewOne;
		}
		else
		{
			mRear->next = addNewOne;
		}

		mRear = addNewOne;
		return true;

	}

	bool Queue::Dequeue(Data& rhs)
	{
		if (CheckEmpty()==true)
		{
			return false;
		}

		else
		{
			rhs = mRear->data;
			mDataCount--;

			if (mFront == mRear)
			{
				delete mFront;
				mFront = nullptr;
				mRear = nullptr;

				return true;
			}

			Nodeptr temp{ mFront };
				
			while (temp->next != mRear)
			{
				temp = temp->next;
			}

			delete mRear;
			temp->next = nullptr;
			mRear = temp;

			return true;

		}
	}
}
