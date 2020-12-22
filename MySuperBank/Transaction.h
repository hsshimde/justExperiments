#pragma once
#include <string>


namespace account
{
	class Transaction
	{
	public:
		Transaction(double amount, const std::string note);
		~Transaction() = default;
		
		const double& GetAmount() const;
		const std::string& GetNote() const;
		


	private:
		double mAmount;
		std::string mNote;
	};
}