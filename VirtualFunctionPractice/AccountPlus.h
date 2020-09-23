#pragma once
#include "Account.h"

namespace accountplus
{
	using account::Account;

	class AccountPlus : public Account
	{
	public:

		AccountPlus();
		AccountPlus(const std::string& name);
		AccountPlus(const std::string& name, unsigned long int accountNumber);
		AccountPlus(const std::string& name, unsigned long int accountNumber, double balance);
		AccountPlus(const std::string& name, unsigned long int accountNumber, double balance, double maxLoan);
		AccountPlus(const std::string& name, unsigned long int accountNumber, double balance, double maxLoan, double rate);
		AccountPlus(const std::string& name, unsigned long int accountNumber, double balance, double maxLoan, double rate, double owesBank);
		AccountPlus(const Account& account,double maxLoan,double rate,double owesBank);
		AccountPlus(const AccountPlus& accountPlus) = delete;
		virtual ~AccountPlus();
		virtual void ViewAccountInfo() const;
		virtual void Withdraw(double amount);

		void ResetMax(double max);
		void ResetRate(double rate);
		void ResetOwesBank(double owes);

	private:
		double mMaxLoan;
		double mRate;
		double mOwesBank;


	};


}