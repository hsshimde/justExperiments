#include "JustTesting2.h"

namespace placenew2
{
	JustTesting::JustTesting()
		: mName{ "Just Testing" }
		, mNumber{ 0 }
	{
		std::cout << mName << " Constructed ! \n";
	}

	JustTesting::JustTesting(const char* s, int n)
		: mName{ s }
		, mNumber{ n }
	{

	}


	JustTesting::~JustTesting()
	{
		std::cout << mName << " Destructed ! \n";
	}

	void JustTesting::Show() const
	{
		std::cout << "Name : " << mName << ", " << mNumber << std::endl;
	}

}