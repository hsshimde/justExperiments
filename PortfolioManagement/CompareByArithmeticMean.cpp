
#include "CompareByArithmeticMean.h"

namespace compare
{
	using namespace company;

	CompareByAriMean::CompareByAriMean(size_t timeLength)
		: mTimeLength{ timeLength }
	{

	}

	bool CompareByAriMean::operator()(const IndividualStock* lhs, const IndividualStock* rhs)
	{

		const Company* leftHandCompanyPointer{ &lhs->first };
		const Company* rightHandCompanyPointer{ &rhs->first };

		float leftHandArithmeticMean{ leftHandCompanyPointer->GetArithmeticMean(mTimeLength) };
		float rightHandArithmeticMean{ rightHandCompanyPointer->GetArithmeticMean(mTimeLength) };

		return leftHandArithmeticMean < rightHandArithmeticMean;

	}

}