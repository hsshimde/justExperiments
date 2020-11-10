#pragma once
#include <utility>
#include <vector>

#include "CompanyFinancialInfo.h"

constexpr static size_t MAX_PORTFOLIO_SIZE{ 100 };

namespace portfolio
{
	using namespace company;
	typedef float weight;
	typedef std::pair<Company, weight> IndividualStock;
	typedef std::vector<IndividualStock*> StockVector;
	
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
		
			
	
	private:
		const IndividualStock* mStockArray[MAX_PORTFOLIO_SIZE];
		size_t mPortfolioSize;
		

	};


	

}