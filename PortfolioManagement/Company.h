#pragma once
#include <vector>
namespace company
{
	

	class Company
	{
	public:
		Company(size_t companyKey, double marketValue, double valuePerShare ,double sales, double operatingProfit, double netProfit, const std::vector<float>& growthRate);
		virtual ~Company();

		void SetMarketValue(double marketValue);
		void SetSales(double Sales);
		void SetOperatingProfit(double operatingProfit);
		void SetNetProfit(double netProfit);
		void AddRecentGrothRate(float recentGrowthRate);
		
		size_t GetCompanyKey() const;
		const double& GetMarketValue() const;
		const double& GetSales() const;
		const double& GetOperatingProfit() const;
		const double& GetNetProfit() const;
		const double& GetValuePerShare() const;

	private:
		size_t mCompanyKey;
		double mMarketValue;
		double mValuePerShare;
		double mSales;
		double mOperatingProfit;
		double mNetProfit;
		std::vector<float> mGrowthRateVector;
		
	};
}