#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class MyNumberString
{
public:
	MyNumberString();
	MyNumberString(int number);
	MyNumberString(const MyNumberString& rhs);
	~MyNumberString();
	MyNumberString& operator=(const MyNumberString& rhs);
	bool operator>(const MyNumberString& rhs) const;
	bool operator==(const MyNumberString& rhs) const;
	bool operator<(const MyNumberString& rhs) const;
	

	const std::string& GetNumber() const;
	

private:
	std::string mNumberString;


};