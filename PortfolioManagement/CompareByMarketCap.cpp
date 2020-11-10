#include "CompareByMarketCap.h"

namespace compare
{
	bool CompareByMarketCap::operator()(const IndividualStock* lhs, const IndividualStock* rhs)
	{
		const Company* leftHandCompanyPointer{ &lhs->first };
		const Company* rightHandCompanyPointer{ &rhs->first };

		return leftHandCompanyPointer->GetMarketCap() < rightHandCompanyPointer->GetMarketCap();
	}
}