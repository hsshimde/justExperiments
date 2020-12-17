#pragma once
#include <string>

namespace manager
{
	enum class eProductType
	{
		NULLTYPE,NECKLACE, EARING, RING
	};

	class Item 
	{
	public:
		Item() = delete;
		Item(const std::string& itemName, size_t itemNumber);
		Item(const Item& rhs) = default;
		Item(Item&& rhs) = default;
		
		

		bool Sell(size_t sellCount);
		bool Buy(size_t buyCount);

		const std::string& GetName() const;
		size_t GetItemNumber() const;
		size_t GetCurrentCount() const;
		size_t GetMinCount() const;
		size_t GetMaxCount() const;


		void SetMaxStock(size_t newMaxCount);
		void SetMinStock(size_t newMinCount);


		size_t RefillMinAndReturnCost();
		size_t RefillMaxAndReturnCost();

		

		
	private:
		std::string mName;
		size_t mItemNumber;
		size_t mCurrentItemCount;
		size_t mMinStock;
		size_t mMaxStock;
		size_t mSalePrice;
		

	};

}