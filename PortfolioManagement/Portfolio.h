#pragma once
#include <utility>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "Company.h"

constexpr static size_t MAX_PORTFOLIO_SIZE{ 100 };

namespace portfolio
{
	using namespace company;
	typedef std::pair<Company, size_t> IndividualStock;
	typedef std::vector<IndividualStock*> StockPointerVector;
	typedef std::unordered_map<size_t, size_t> StockHashMapForIndex;


	
	class Portfolio
	{
		friend class company::Company;

	public:
		Portfolio();
		virtual ~Portfolio();
		Portfolio(const Portfolio& rhs);
		Portfolio& operator=(const Portfolio& rhs);
		
		StockPointerVector SortByMarketCap(size_t timeLength) const;
		StockPointerVector SortByPBR(size_t timeLength) const;
		StockPointerVector SortByPCR(size_t timeLength) const;
		StockPointerVector SortByPOR(size_t timeLength) const;
		StockPointerVector SortByGeometricMean(size_t timeLength) const;
		StockPointerVector SortByArithmeticMean(size_t timeLength) const;
		StockPointerVector SortByWeight(size_t timeLength) const;


		bool BuyStock(IndividualStock* indivStock);
		bool SellStock(IndividualStock* indivStock);
		
		IndividualStock* GetStockNullable(size_t companyKey) const;
		float GetWeight(size_t companyKey) const;

		
			
	
	private:
		IndividualStock* mStockArray[MAX_PORTFOLIO_SIZE];
		StockHashMapForIndex mStockHashMap;
		size_t mPortfolioSize;
		double mNetPortfolioValue;
		

	};


	

}