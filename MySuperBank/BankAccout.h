#pragma once
#include <string>
#include <vector>
#include "Transaction.h"


namespace account
{
	class BankAccount 
	{
	public:
		BankAccount(const char* mName);
		BankAccount(const std::string& mName);
		~BankAccount();

		void MakeDeposit(const double& amount, const std::string& note);
		bool MakeWithdrwal(const double& amount, const std::string& note);

		void ShowTransactions() const;
	

	private:
		std::string mName;
		double mBalance;
		std::vector<Transaction*> mAllTransactions;
	};
}