#include "AccountPlus.h"

namespace accountplus
{
	AccountPlus::AccountPlus()
		:Account{}
		,mRate{-1.0}
		, mMaxLoan{ -1.0 }
		, mOwesBank{ -1.0 }
	{

	}
	AccountPlus::AccountPlus(const std::string& name)
		:Account{name}
		,mRate{5.0}
		, mMaxLoan{ 1000 }
		, mOwesBank{ 0 }
	{

	}
	AccountPlus::AccountPlus(const std::string& name, unsigned long int accountNumber)
		:Account{name,accountNumber}
		,mRate{5.0}
		, mMaxLoan{ 1000 }
		, mOwesBank{ 0.0 }
	{

	}
	AccountPlus::AccountPlus(const std::string& name,unsigned long int accountNumber,double balance)
		:Account{name,accountNumber,balance}
		,mRate{5.0}
		, mMaxLoan{ 1000 }
		, mOwesBank{ 0.0 }
	{

	}

	AccountPlus::AccountPlus(const std::string& name,unsigned long int accountNumber,double balance,double maxLoan)
		:Account{ name,accountNumber,balance }
		, mMaxLoan{ maxLoan }
		, mRate{ 5.0 }
		, mOwesBank{ 0.0 }	
	{

	}


	AccountPlus::AccountPlus(const std::string& name,unsigned long int accountNumber,double balance,double maxLoan,double rate)
		:Account{name,accountNumber,balance}
		, mMaxLoan{ maxLoan }
		, mRate{ rate }
		,mOwesBank{0.0}
	{

	}



	AccountPlus::AccountPlus(const std::string& name,unsigned long int accountNumber,double balance,double maxLoan,double rate,double owesBank)
		:Account{name,accountNumber,balance}
		,mMaxLoan{maxLoan}
		, mRate{ rate }
		, mOwesBank{ owesBank }
	{

	}

	AccountPlus::AccountPlus(const Account& account,double maxLoan,double rate,double owesBank)
		:Account{account.GetName(),account.GetAccountNumber(),account.GetBalance()}
		,mMaxLoan{maxLoan}
		, mRate{ rate }
		, mOwesBank{ owesBank }
	{

	}


}