#pragma once
#include "Portfolio.h"

namespace compare
{

	using namespace portfolio;

	class CompareByPCR
	{

	public:
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);


	};
}