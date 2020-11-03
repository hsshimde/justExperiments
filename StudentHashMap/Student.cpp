
#include "Student.h"

namespace course
{
	Student::Student()
		: mName{ "Null" }
		, mStudentNumber{}
	{

	}

	Student::Student(std::string& name, size_t student)
		: mName{ name }
		, mStudentNumber{ student }
	{

	}

	Student::~Student()
	{

	}

	const std::string& Student::GetName() const
	{
		return mName;
	}

	size_t Student::GetNumber() const
	{
		return mStudentNumber;
	}

	std::ostream& operator<<(std::ostream& os, const Student& rhs)
	{
		os << "{ " << rhs.mStudentNumber << " : " << rhs.mName << " } ";
		return os;
	}

	bool Student::operator<(const Student& rhs) const
	{
		return mStudentNumber < rhs.mStudentNumber;
	}

	bool Student::operator==(const Student& rhs) const
	{
		return mStudentNumber == rhs.mStudentNumber;
	}
}