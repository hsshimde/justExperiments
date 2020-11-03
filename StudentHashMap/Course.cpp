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
		assert(student != nullptr);

		if (mStudentCount >= mMaxStudentCount)
		{
			delete student;
			return false;
		}

		else
		{
			mStudentNumberArray[mStudentCount] = student->GetStudentNumber();
			mStudentPointerArray[hash(student->GetStudentNumber())] = student;
			mStudentCount++;
			return true;
		}

	}

	bool Course::RemoveStudent(size_t studentNumber)
	{
		if (studentNumber >= mStudentCount)
		{
			return false;
		}

		else
		{
			bool bFoundStudent{ false };

			size_t i{};
			for (; i < mStudentCount; ++i)
			{
				if (mStudentNumberArray[i] == studentNumber)
				{
					bFoundStudent = true;
					break;
				}
			}

			if (!bFoundStudent)
			{
				return false;
			}

			else
			{
				delete mStudentPointerArray[hash(mStudentNumberArray[i])];

				if (i != MAX_COUNT)
				{
					for (size_t j{ i + 1 }; j < mMaxStudentCount; ++j)
					{
						mStudentNumberArray[j - 1] = mStudentNumberArray[j];
					}
				}

				mStudentCount--;
				return true;
			}


		}
	}


	size_t Course::GetStudentCount() const
	{
		return mStudentCount;
	}

	const Student* Course::GetStudent(size_t studentNumber) const
	{
		return mStudentPointerArray[hash(studentNumber)];
	}

	size_t Course::hash(size_t studentNumber) const
	{
		return studentNumber % HashNumber;
	}

	std::ostream& operator<<(std::ostream& os, const Course& course)
	{
		for (size_t i{}; i < course.mStudentCount; ++i)
		{
			os << *course.mStudentPointerArray[course.hash(course.mStudentNumberArray[i])] << std::endl;
		}

		return os;
	}


}