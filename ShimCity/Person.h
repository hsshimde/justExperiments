#pragma once

#include <string>

namespace assignment2
{
	class Person
	{
	public:
		Person(const char* name, unsigned int weight);
		Person(const Person& rhs);
		~Person();

		const std::string& GetName() const;
		unsigned int GetWeight() const;

	private:
		std::string mName;
		size_t mWeight;


	};
}