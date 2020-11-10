#pragma once
#include <utility>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "CompanyFinancialInfo.h"

constexpr static size_t MAX_PORTFOLIO_SIZE{ 100 };

namespace portfolio
{
	using namespace company;
	typedef std::pair<Company, size_t> IndividualStock;
	typedef std::vector<IndividualStock*> StockVector;
	typedef std::unordered_map<size_t, size_t> StockHashMapForIndex;


	
	class Portfolio
	{
		friend class company::Company;

	public:
		Portfolio();
		virtual ~Portfolio();
		Portfolio(const Portfolio& rhs);
		Portfolio& operator=(const Portfolio& rhs);
		
		StockVector SortByShare() const;
		StockVector SortByPBR() const;
		StockVector SortByPCR() const;
		StockVector SortByPOR() const;
		
		StockVector SortByGeometricMean() const;
		StockVector SortByArithmeticMean() const;
		StockVector SortByWeight() const;


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