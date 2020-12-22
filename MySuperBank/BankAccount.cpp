#include <iostream>
#include "BankAccout.h"


namespace account
{
	BankAccount::BankAccount(const char* name)
		: mName(name)
		, mBalance()
		, mAllTransactions()
	{

	}

	BankAccount::BankAccount(const std::string& name)
		: mName(name)
		, mBalance()
		, mAllTransactions()
	{

	}
	
	BankAccount::~BankAccount()
	{
		for (size_t i = 0; i < mAllTransactions.size(); i++)
		{
			delete mAllTransactions[i];
		}
		
	}

	void BankAccount::MakeDeposit(const double& amount, const std::string& note)
	{
		mBalance += amount;
		mAllTransactions.push_back(new Transaction(amount, note));
	}

	bool BankAccount::MakeWithdrwal(const double& amount, const std::string& note)
	{
		if (mBalance < amount)
		{
			return false;
		}

		else
		{
			mBalance -= amount;
			mAllTransactions.push_back(new Transaction(amount, note));
			return true;
		}
	}

	void BankAccount::ShowTransactions() const
	{
		for (size_t i = 0; i < mAllTransactions.size(); i++)
		{
			std::cout << "[" << i + 1 << "] :" << mAllTransactions[i]->GetAmount() << ", " << mAllTransactions[i]->GetNote() << std::endl;
		}
		return;
	}


}