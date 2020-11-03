#pragma once
#include <string>
#include <iostream>

namespace course
{
	class Student
	{
	public:
		Student();
		Student(std::string& name, size_t studentNumber);
		virtual ~Student();
		bool operator<(const Student& rhs) const;
		bool operator==(const Student& rhs) const;
		
		size_t GetStudentNumber() const;
		const std::string& GetStudentName() const;
		friend std::ostream& operator<<(std::ostream& os, const Student& student);

	private:
		std::string mName;
		size_t mStudentNumber;

	};
}