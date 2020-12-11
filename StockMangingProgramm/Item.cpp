#include "Item.h"

namespace manager
{
	Item::Item(const eProductType type,const std::string& itemName, size_t itemNumber)
		: mType(type)
		, mName(itemName)
		, mItemNumber(itemNumber)
		, mCurrentItemCount(0)
		, mMaxStock()
		, mMinStock()
	{

	}

	bool Item::Buy(size_t buyCount)
	{
		if (mCurrentItemCount + buyCount >= mMaxStock)
		{
			return false;
		}

		mCurrentItemCount += buyCount;

		return true;
	}

	bool Item::Sell(size_t sellCount)
	{
		if (mCurrentItemCount <= sellCount)
		{
			return false;
		}

		mCurrentItemCount -= sellCount;

		return true;
	}

	const std::string& Item::GetName() const
	{
		return mName;
	}

	size_t Item::GetCurrentCount() const
	{
		return mCurrentItemCount;
	}

	size_t Item::GetItemNumber() const
	{
		return mItemNumber;
	}

	size_t Item::GetMaxCount() const
	{
		return mMaxStock;
	}

	size_t Item::GetMinCount() const
	{
		return mMinStock;
	}


}