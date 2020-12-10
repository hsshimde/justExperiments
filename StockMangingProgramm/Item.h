#pragma once
#include <string>

namespace manager
{
	class Item 
	{
	public:
		Item() = delete;
		Item(const std::string& itemName, size_t itemNumber, size_t itemCount, size_t minimumStock);

		bool Sell(size_t sellCount);
		bool Buy(size_t buyCount);
		

		
	private:
		std::string mName;
		size_t mItemNumber;
		size_t mItemCount;
		size_t mMinimumStock;
		size_t mMaxStock;

	};

}