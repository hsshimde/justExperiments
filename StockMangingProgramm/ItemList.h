#pragma once
#include <unordered_map>
#include "Item.h"

namespace manager
{
	typedef std::unordered_map<size_t, Item*> itemNumberMap;
	
	class ItemList
	{
	public:
		ItemList();
		ItemList(const ItemList& rhs);
		ItemList(ItemList&& rhs) noexcept;
		ItemList& operator=(const ItemList& rhs);
		ItemList& operator=(ItemList&& rhs) noexcept;
		
		bool Add(Item* item);
		//bool RemoveByName(const std::string& name);
		bool Remove(const size_t number);

		bool Sell(size_t itemNumber, size_t count);
		bool Buy(size_t itemNumber, size_t count);


		


	private:
		itemNumberMap mNumberMap;
		size_t mItemListSize;
		
	};


}