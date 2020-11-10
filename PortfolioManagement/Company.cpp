#include <cassert>
#include <cmath>

#include "Company.h"

namespace company
{
	Company::Company(size_t companyKey, double marketValue, double valuePerShare, double sales, double operatingProfit, double netProfit, const std::vector<float>& growthRate)
		: mCompanyKey{ companyKey }
		, mMarketCap{ marketValue }
		, mValuePerShare{ valuePerShare }
		, mSales{ sales }
		, mOperatingProfit{ operatingProfit }
		, mNetProfit{ netProfit }
		, mGrowthRateVector{ growthRate }
	{

	}

	Company::~Company()
	{

	}

	void Company::SetMarketValue(double marketValue)
	{
		mMarketCap = marketValue;
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

	size_t Company::GetCompanyKey() const
	{
		return mCompanyKey;
	}

	const double& Company::GetMarketCap() const
	{
		return mMarketCap;
	}

	const double& Company::GetNetProfit() const
	{
		return mNetProfit;
	}

	const double& Company::GetOperatingProfit() const
	{
		return mOperatingProfit;
	}

	const double& Company::GetSales() const
	{
		return mSales;
	}

	const double& Company::GetValuePerShare() const
	{
		return mValuePerShare;
	}

	float Company::GetArithmeticMean(size_t timeLength) const
	{
		assert(!mGrowthRateVector.empty());

		float totalSum{};

		if (mGrowthRateVector.size() < timeLength)
		{
			for (size_t i{}; i < mGrowthRateVector.size(); ++i)
			{
				totalSum += mGrowthRateVector[i];
			}

			return totalSum / mGrowthRateVector.size();
		}

		else
		{
			size_t lastIndex{ mGrowthRateVector.size() - 1 };

			for (size_t i{}; i < timeLength; ++i)
			{
				totalSum += mGrowthRateVector[lastIndex - i];
			}

			return totalSum / timeLength;
		}
	}


	float Company::GetGeometricMean(size_t timeLength) const
	{
		assert(!mGrowthRateVector.empty());

		double totalMultiplied{ 1.0 };

		if (timeLength > mGrowthRateVector.size())
		{
			for (size_t i{}; i < mGrowthRateVector.size(); ++i)
			{
				totalMultiplied *= mGrowthRateVector[i];
			}

			return static_cast<float>(std::pow(totalMultiplied, 1.0 / mGrowthRateVector.size()));
		}

		else
		{
			size_t lastIndex{ mGrowthRateVector.size() - 1 };

			for (size_t i{}; i < timeLength; ++i)
			{
				totalMultiplied *= mGrowthRateVector[i];
			}

			return static_cast<float>(std::pow(totalMultiplied, 1.0 / timeLength));
		}



	}
}