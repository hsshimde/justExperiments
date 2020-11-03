#pragma once

#include "Student.h"

namespace course
{
	class Course
	{
	public:
		Course(const std::string courseName, size_t courseNumber, size_t maxStudentCount);
		Course(const Course& rhs);
		Course& operator=(const Course& rhs);

		virtual ~Course();
		bool AddStudent(const Student* student);
		bool RemoveStudent(size_t studentNumber);
	
		

	private:
		std::string mCourseName;
		size_t mCourseNumber;
		constexpr static size_t MAX_COUNT{ 200 };
		constexpr static size_t HashNumber{ 211 };
		const size_t mMaxStudentCount;
		size_t mStudentCount;

		size_t mStudentNumberArray[MAX_COUNT];
		const Student* mStudentPointerArrat[MAX_COUNT];

	};
}