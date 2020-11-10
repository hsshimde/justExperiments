#include <algorithm>

#include "Portfolio.h"
#include "CompareByArithmeticMean.h"
#include "CompareByGeometricMean.h"
#include "CompareByMarketCap.h"
#include "CompareByPBR.h"
#include "CompareByPCR.h"
#include "CompareByPOR.h"
#include "CompareByWeight.h"


namespace portfolio
{
	Portfolio::Portfolio()
		: mStockArray{}
		, mStockHashMap{}
		, mPortfolioSize{}
		, mNetPortfolioValue{}
	{

	}

	Portfolio::~Portfolio()
	{
		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			delete mStockArray[i];
		}
	}

	Portfolio::Portfolio(const Portfolio& rhs)
		: mPortfolioSize{ rhs.mPortfolioSize }
		, mStockHashMap{ rhs.mStockHashMap }
		, mNetPortfolioValue{ rhs.mNetPortfolioValue }
	{
		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			mStockArray[i] = new IndividualStock{ *rhs.mStockArray[i] };
		}
	}

	Portfolio& Portfolio::operator=(const Portfolio& rhs)
	{
		if (this != &rhs)
		{
			for (size_t i{}; i < mPortfolioSize; ++i)
			{
				delete mStockArray[i];
			}

			mPortfolioSize = rhs.mPortfolioSize;
			mNetPortfolioValue = rhs.mNetPortfolioValue;

			for (size_t i{}; i < mPortfolioSize; ++i)
			{
				mStockArray[i] = new IndividualStock{ *rhs.mStockArray[i] };
			}

			mStockHashMap = rhs.mStockHashMap;
		}

		return *this;
	}

	bool Portfolio::BuyStock(IndividualStock* buyingStock)
	{
		const Company* tempCompanyPointer{ &buyingStock->first };
		size_t buyingCompanyKey{ tempCompanyPointer->GetCompanyKey() };

		if (mStockHashMap.find(buyingCompanyKey) == end(mStockHashMap))
		{
			if (mPortfolioSize >= MAX_PORTFOLIO_SIZE)
			{
				delete buyingStock;
				assert(mPortfolioSize >= MAX_PORTFOLIO_SIZE);

				return false;
			}

			else
			{
				size_t arrayIndex{ mPortfolioSize };
				mStockHashMap.insert({ buyingCompanyKey, arrayIndex });
				mStockArray[mPortfolioSize++] = buyingStock;
				return true;
			}
		}
		else
		{
			size_t arrayIndex{ mStockHashMap.find(buyingCompanyKey)->second };
			size_t buyingCount{ buyingStock->second };

			mStockArray[arrayIndex]->second += buyingCount;

			return true;
		}
	}

	bool Portfolio::SellStock(IndividualStock* sellingStock)
	{
		Company* tempCompanyPointer{ &sellingStock->first };
		size_t sellingCompanyKey{ tempCompanyPointer->GetCompanyKey() };

		assert(mStockHashMap.find(sellingCompanyKey) != end(mStockHashMap));

		
		size_t sellingCount{ sellingStock->second };
		size_t sellingCompanyArrayIndex{ mStockHashMap.find(sellingCompanyKey)->second };
		size_t shareCount{ mStockArray[sellingCompanyArrayIndex]->second };
		delete sellingStock;
		
		if (shareCount < sellingCount)
		{
			return false;
		}

		else
		{
			mStockArray[sellingCompanyArrayIndex]->second -= sellingCount;
			return true;
		}
		
	}

	IndividualStock* Portfolio::GetStockNullable(size_t companyKey) const
	{
		if (mStockHashMap.find(companyKey) == end(mStockHashMap))
		{
			return nullptr;
		}
		else
		{
			size_t arrayIndex{ mStockHashMap.find(companyKey)->second };

			return mStockArray[arrayIndex];
		}
	}

	float Portfolio::GetWeight(size_t companyKey) const
	{
		const IndividualStock* tempIndivStockPointer{ GetStockNullable(companyKey) };

		if (tempIndivStockPointer == nullptr)
		{
			return -1.0f;
		}

		else
		{
			const Company* tempCompanyPointer{ &tempIndivStockPointer->first };
			double valuePerShare{ tempCompanyPointer->GetValuePerShare() };
			size_t shareCount{ tempIndivStockPointer->second };

			return static_cast<float>(valuePerShare * shareCount) / mNetPortfolioValue;
			
		}
	}


	StockPointerVector Portfolio::SortByMarketCap() const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}
		
		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByMarketCap());

		return sortedVector;
	}

	StockPointerVector Portfolio::SortByPBR() const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByPBR());

		return sortedVector;
	}

	StockPointerVector Portfolio::SortByPCR() const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByPCR());

		return sortedVector;
	}
	
	StockPointerVector Portfolio::SortByPOR() const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByPOR());

		return sortedVector;
	}

	StockPointerVector Portfolio::SortByWeight() const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByWeight());
		
		return sortedVector;
	}

	StockPointerVector Portfolio::SortByArithmeticMean(size_t timeLength) const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByAriMean(timeLength));

		return sortedVector;
	}

	StockPointerVector Portfolio::SortByGeometricMean(size_t timeLength) const
	{
		StockPointerVector sortedVector{};

		for (size_t i{}; i < mPortfolioSize; ++i)
		{
			sortedVector.push_back(mStockArray[i]);
		}

		std::sort(begin(sortedVector), end(sortedVector), compare::CompareByGeoMean(timeLength));

		return sortedVector;
	}

	

}