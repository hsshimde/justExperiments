#include <cassert>

#include "Course.h"
#include "Student.h"

using namespace course;

int main()
{
	Course* c1{ new Course{"Mathematics", 101, 50 } };
	Course* c2{ new Course{"Computer Science", 102, 50} };

	c1->AddStudent(new Student{ "Dami",127 });
	c1->AddStudent(new Student{ "Aryn", 211 });
	c1->AddStudent(new Student{ "Sai", 400 });

	assert(c1->GetStudentCount() == 3);
	assert(c2->GetStudentCount() == 0);
	assert(c1->GetStudent(127)->GetStudentName() == "Dami");

	std::cout << *c1;

	delete c1;
	delete c2;
	
	return 0;
	
	
}