#pragma once
#include <string>

namespace account
{
	

	class Account
	{
	public:
		Account();
		Account(const std::string& name);
		Account(const std::string& name, unsigned long int accountNumber);
		Account(const std::string& name, unsigned long int accountNumber, double balance);
		Account(const Account& rhs) = delete;
		virtual ~Account();
		const std::string& GetName() const;
		const unsigned long int& GetAccountNumber() const;	
		const double& GetBalance() const;
		virtual void ViewAccountInfo() const;
		void Deposit(double amount);
		virtual void Withdraw(double amount);
		

	private:
		std::string mName;
		unsigned long int mAccountNumber;
		double mBalance;
	};
}