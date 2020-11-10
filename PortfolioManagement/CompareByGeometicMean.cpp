#include "CompareByGeometricMean.h"

namespace compare
{
	CompareByGeoMean::CompareByGeoMean(size_t timeLength)
		: mTimeLength{ timeLength }
	{

	}

	bool CompareByGeoMean::operator()(const IndividualStock* lhs, const IndividualStock* rhs) 
	{
		const Company* leftHandCompanyPointer{ &lhs->first };
		const Company* rightHandCompanyPointer{ &rhs->first };

		float leftHandGeoMean{ leftHandCompanyPointer->GetGeometricMean(mTimeLength) };
		float rightHandGeoMean{ rightHandCompanyPointer->GetGeometricMean(mTimeLength) };

		return leftHandGeoMean < rightHandGeoMean;
	}
}