#pragma once

#include "Student.h"

namespace course
{
	class Course
	{
	public:
		Course(const std::string courseName, size_t courseNumber, size_t maxStudentCount);
		Course(const Course& rhs);
		Course& operator=(const Course& rhs) = delete;

		virtual ~Course();
		bool AddStudent(const Student* student);
		bool RemoveStudent(size_t studentNumber);

		size_t GetStudentCount() const;
		const Student* GetStudent(size_t studentNumber) const;

		friend std::ostream& operator<<(std::ostream& os, const Course& course);

	private:
		size_t hash(size_t key) const;

		std::string mCourseName;
		size_t mCourseNumber;
		constexpr static size_t MAX_COUNT{ 200 };
		constexpr static size_t HashNumber{ 211 };
		const size_t mMaxStudentCount;
		size_t mStudentCount;

		size_t mStudentNumberArray[MAX_COUNT];
		const Student* mStudentPointerArray[MAX_COUNT];

	};
}