#include "Company.h"

namespace company
{
	/*size_t mCompanyKey;
	double mMarketValue;
	double mValuePerShare;
	double mSales;
	double mOperatingProfit;
	double mNetProfit;
	float mLastYearGrowthRate[12];*/
	

	Company::Company(size_t companyKey, double marketValue,double valuePerShare, double sales, double operatingProfit, double netProfit, const std::vector<float>& growthRate)
		: mCompanyKey{companyKey}
		, mMarketValue{marketValue}
		, mValuePerShare{valuePerShare}
		, mSales{sales}
		, mOperatingProfit{operatingProfit}
		, mNetProfit{netProfit}
		, mGrowthRateVector{growthRate}
	{
		
	}

	Company::~Company()
	{

	}

	void Company::SetMarketValue(double marketValue)
	{
		mMarketValue = marketValue;
	}

	void Company::SetNetProfit(double netProfit)
	{
		mNetProfit = netProfit;
	}

	void Company::SetOperatingProfit(double operatingProfit)
	{
		mOperatingProfit = operatingProfit;
	}


	void Company::SetSales(double sales)
	{
		mSales = sales;
	}

	void Company::AddRecentGrothRate(float recentGrowthRate)
	{
		mGrowthRateVector.push_back(recentGrowthRate);
	}

}