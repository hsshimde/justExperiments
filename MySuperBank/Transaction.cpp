#include "Transaction.h"


namespace account
{
	Transaction::Transaction(double amount, const std::string note)
		: mAmount(amount)
		, mNote(note)
	{

	}

	const double& Transaction::GetAmount() const
	{
		return mAmount;
	}

	const std::string& Transaction::GetNote() const
	{
		return mNote;
	}
}