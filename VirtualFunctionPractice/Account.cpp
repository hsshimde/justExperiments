#include <iostream>
#include "Account.h"

namespace account
{
	Account::Account()
		:mName{"Not Given"}
		, mAccountNumber{0}
		, mBalance{0}
	{

	}

	Account::Account(const std::string& name)
		:mName{name}
		, mAccountNumber{ 0 }
		, mBalance{ 0 }
	{

	}

	Account::Account(const std::string& name,unsigned long int accountNumber)
		:mName{name}
		, mAccountNumber{ accountNumber }
		, mBalance{ 0 }
	{

	}

	Account::Account(const std::string& name,unsigned long int accountNumber,double balance)
		:mName{name}
		, mAccountNumber{ accountNumber }
		, mBalance{ balance }
	{

	}

	Account::~Account()
	{

	}

	const std::string& Account::GetName() const
	{
		return mName;
	}

	const double& Account::GetBalance() const
	{
		return mBalance;
	}

	const unsigned long int& Account::GetAccountNumber() const
	{
		return mAccountNumber;
	}
	
	void Account::ViewAccountInfo() const
	{
		std::cout << "Name : " << GetName() << std::endl;
		std::cout << "Account Number : " << GetAccountNumber() << std::endl;
		std::cout << "Balance : " << GetBalance() << std::endl;

	}

	void Account::Deposit(double amount)
	{
		mBalance += amount;
	}

	void Account::Withdraw(double amount)
	{
		if (mBalance >= amount)
		{
			mBalance -= amount;
		}
	}


}