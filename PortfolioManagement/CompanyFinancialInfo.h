#pragma once
#include <string>
namespace company
{
	

	class Company
	{
	public:
		Company(size_t companyKey, double marketValue, double sales, double operatingProfit, double netProfit);
		virtual ~Company();

		void SetMarketValue(double marketValue);
		void SetSales(double Sales);
		void SetOperatingProfit(double operatingProfit);
		void SetNetProfit(double netProfit);
	
		size_t GetCompanyKey() const;
		double GetMarketValue() const;
		double GetSales() const;
		double GetOperatingProfit() const;
		double GetNetProfit() const;
		double GetValuePerShare() const;




	private:
		size_t mCompanyKey;
		double mMarketValue;
		double mValuePerShare;
		double mSales;
		double mOperatingProfit;
		double mNetProfit;
		float mLastYearGrowthRate[12];
		
	};
}