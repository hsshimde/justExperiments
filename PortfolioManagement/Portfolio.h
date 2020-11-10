#pragma once
#include <utility>

#include "CompanyFinancialInfo.h"

namespace portfolio
{
	using namespace company;
	typedef size_t stockCount;
	typedef std::pair<Company, stockCount>  
	constexpr size_t PORTFOLIO_STOCK_COUNT;
	class Portfolio
	{
	public:
		

	private:
		Company* mStockArray;
		size_t mStockCount;
		double mPortfolioNetValue;

	};
}