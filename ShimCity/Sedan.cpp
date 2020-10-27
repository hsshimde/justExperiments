#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle{ 4 }
	{

	}

	Sedan::~Sedan()
	{

	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		return false;
	}

	bool Sedan::RemoveTrailer()
	{
		return false;
	}
}