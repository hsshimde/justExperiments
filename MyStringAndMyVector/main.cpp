#include <vector>	
#include <string>
#include "MyString.h"


int main()
{
	using namespace project;
	std::vector<MyString> vectorStrings;
	std::vector<std::string> vecStrings;

	vectorStrings.push_back(MyString("sdf"));
	vectorStrings.push_back(MyString("sdfah"));
	vectorStrings.push_back(MyString("sdfahew"));
	vectorStrings.push_back(MyString("s"));
	vectorStrings.push_back(MyString("sq	"));
	vectorStrings.push_back("sdfdsf");
	
	for (auto& i : vectorStrings)
	{
		std::cout << i << std::endl;
	}

	return 0;
}