#include <cassert>

#include "Course.h"

//std::string mCourseName;
//size_t mCourseNumber;
//constexpr static size_t MAX_COUNT{ 200 };
//constexpr static size_t HashNumber{ 211 };
//const size_t mMaxStudentCount;
//size_t mStudentCount;
//
//size_t mStudentNumberArray[MAX_COUNT];
//const Student* mStudentPointerArrat[MAX_COUNT];
namespace course
{
	Course::Course(const std::string courseName, size_t courseNumber, size_t maxStudentCount)
		: mCourseName{ courseName }
		, mCourseNumber{ courseNumber }
		, mMaxStudentCount{ maxStudentCount }
		, mStudentCount{}
		, mStudentNumberArray{}
		, mStudentPointerArray{}
	{

	}

	Course::Course(const Course& rhs)
		: mCourseName{ rhs.mCourseName }
		, mCourseNumber{ rhs.mCourseNumber }
		, mMaxStudentCount{ rhs.mMaxStudentCount }
		, mStudentCount{ rhs.mStudentCount }
		, mStudentNumberArray{}
		, mStudentPointerArray{}
	{

		for (size_t i{}; i < mStudentCount; ++i)
		{
			mStudentNumberArray[i] = rhs.mStudentNumberArray[i];
			mStudentPointerArray[hash(mStudentNumberArray[i])] = new Student{ *rhs.mStudentPointerArray[hash(rhs.mStudentNumberArray[i])] };
		}
	}


	Course::~Course()
	{
		for (size_t i{}; i < mStudentCount; ++i)
		{
			delete mStudentPointerArray[i];
		}
	}

	bool Course::AddStudent(const Student* student)
	{
		
		if (mStudentCount >= mMaxStudentCount)
		{
			delete student;
			return false;
		}
	}



}