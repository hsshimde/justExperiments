#include <memory>
#include "ItemList.h"

namespace manager
{
	ItemList::ItemList()
		: mNumberMap()
		, mItemListSize()
	{

	}

	ItemList::ItemList(const ItemList& rhs)
		: mNumberMap()
		, mItemListSize(rhs.mItemListSize)
	{
		for (const auto& i : rhs.mNumberMap)
		{
			mNumberMap[i.first] = new Item(*i.second);
		}
	}

	ItemList::ItemList(ItemList&& rhs) noexcept
		: mNumberMap()
		, mItemListSize(rhs.mItemListSize)
	{
		for (auto& i : rhs.mNumberMap)
		{
			mNumberMap[i.first] = std::move(i.second);
		}


	}

	ItemList& ItemList::operator=(const ItemList& rhs)
	{
		if (this != &rhs)
		{
			for (auto& i : mNumberMap)
			{
				delete i.second;
				mNumberMap.erase(i.first);
			}

			for (auto& i : rhs.mNumberMap)
			{
				mNumberMap[i.first] = new Item(*i.second);
			}

			mItemListSize = rhs.mItemListSize;

		}

		return *this;
	}

	ItemList& ItemList::operator=(ItemList&& rhs) noexcept
	{
		if (this != &rhs)
		{
			mItemListSize = rhs.mItemListSize;
			
			for (auto& i : mNumberMap)
			{
				delete i.second;
				mNumberMap.erase(i.first);
			}

			for (auto& i : rhs.mNumberMap)
			{
				mNumberMap[i.first] = std::move(i.second);
			}

		}

		return *this;
	}

	bool ItemList::Add(Item* item)
	{
		if (mNumberMap.find(item->GetItemNumber()) != end(mNumberMap))
		{
			delete item;

			return false;
			
		}

		else
		{
			mNumberMap[item->GetItemNumber()] = item;
			mItemListSize++;
			
			return true;
		}
	}
	
	bool ItemList::Remove(const size_t itemNumber)
	{
		if (mNumberMap.find(itemNumber) == end(mNumberMap))
		{
			return false;
		}

		else
		{
			delete mNumberMap[itemNumber];

			mNumberMap.erase(itemNumber);

			return true;
		}
	}

	bool ItemList::Sell(const size_t itemNumber, size_t count)
	{
		if (mNumberMap.find(itemNumber) == end(mNumberMap))
		{
			return false;
		}

		Item* pItem = mNumberMap[itemNumber];

		return pItem->Sell(count);
	}

	bool ItemList::Buy(const size_t itemNumber, size_t count)
	{
		if (mNumberMap.find(itemNumber) == end(mNumberMap))
		{
			return false;
		}

		Item* pItem = mNumberMap[itemNumber];


		return pItem->Buy(count);
		
	}
}