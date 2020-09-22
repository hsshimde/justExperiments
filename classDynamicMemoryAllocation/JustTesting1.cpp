#include "JustTesting1.h"

namespace placenew1
{
	JustTesting::JustTesting()
		: mName{"Default Constructor"}
		, mNumber{ 0 }
	{

	}
	
	JustTesting::JustTesting(const char* s, int n)
		: mName{s}
		,mNumber{n}
	{
		
	}


	JustTesting::~JustTesting()
	{
		
	}

	void JustTesting::Show() const
	{
		std::cout << "Name : " << mName << ", "  << mNumber << std::endl;
	}

}