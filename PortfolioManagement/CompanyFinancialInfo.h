#pragma once
#include <string>
namespace company
{
	class Company
	{
	public:
		Company(size_t companyKey, double marketValue, double sales, double operatingProfit, double netProfit);

		void SetMarketValue(double marketValue);
		void SetSales(double Sales);
		void SetOperatingProfit(double operatingProfit);
		void SetNetProfit(double netProfit);
	


	private:
		size_t mCompanyKey;
		double mMarketValue;
		double mSales;
		double mOperatingProfit;
		double mNetProfit;
		
	};
}