#include "MyNumberString.h"

MyNumberString::MyNumberString()
	: mNumberString{}
{

}
MyNumberString::MyNumberString(int number)
{
	mNumberString = std::to_string(number);
}

MyNumberString::MyNumberString(const MyNumberString& rhs)
	: mNumberString{ rhs.mNumberString }
{

}
MyNumberString::~MyNumberString()
{

}

bool MyNumberString::operator>(const MyNumberString& rhs) const
{
	int leftNumber{};
	int rightNumber{};

	for(int i{};i<static_cast<int>(mNumberString.size())-1;i++)
	{
		leftNumber += static_cast<int>(mNumberString[i]);
		leftNumber *= 10;
	}

	leftNumber += static_cast<int>(mNumberString[mNumberString.size() - 1]);

	for (int i{}; i < static_cast<int>(rhs.mNumberString.size()) - 1; i++)
	{
		leftNumber += static_cast<int>(rhs.mNumberString[i]);
		leftNumber *= 10;
	}

	leftNumber += static_cast<int>(rhs.mNumberString.size() - 1);



	for (int i{}; i < static_cast<int>(rhs.mNumberString.size()) - 1; i++)
	{
		rightNumber += static_cast<int>(rhs.mNumberString[i]);
		rightNumber *= 10;
	}


	rightNumber += static_cast<int>(rhs.mNumberString.size() - 1);


	for (int i{}; i < static_cast<int>(mNumberString.size()) - 1; i++)
	{
		rightNumber += static_cast<int>(mNumberString[i]);
		rightNumber *= 10;
	}

	rightNumber += static_cast<int>(mNumberString[mNumberString.size() - 1]);

	//rightNumber += static_cast<int>(rhs.mNumberString.size() - 1);


	return leftNumber > rightNumber;

}



MyNumberString& MyNumberString::operator=(const MyNumberString& rhs)
{
	mNumberString = rhs.mNumberString;
	return *this;
}

//
bool MyNumberString::operator==(const MyNumberString& rhs) const
{
	return mNumberString == rhs.mNumberString;
}


bool MyNumberString::operator<(const MyNumberString& rhs) const
{
	return !(rhs == *this || rhs > * this);
}

const std::string& MyNumberString::GetNumber() const
{
	return mNumberString;
}