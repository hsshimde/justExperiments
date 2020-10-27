#include "Person.h"

namespace assignment2
{
	Person::Person(const char* name, unsigned int weight)
		: mName{name}
		, mWeight{weight}
	{

	}

	Person::Person(const Person& rhs)
		: mName{ rhs.mName }
		, mWeight{ rhs.mWeight }
	{

	}

	Person& Person::operator=(const Person& rhs)
	{
		if (rhs != *this)
		{
			mName = rhs.mName;
			mWeight = rhs.mWeight;
		}
		return *this;
	}

	Person::~Person()
	{

	}

	const std::string& Person::GetName() const
	{
		return mName;
	}
		
	unsigned int Person::GetWeight() const
	{
		return mWeight;
	}

	bool Person::operator==(const Person& rhs) const
	{
		return mName == rhs.mName && mWeight == rhs.mWeight;
	}

	bool Person::operator!=(const Person& rhs) const
	{
		return !(rhs == *this);
	}
}