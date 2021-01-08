#include <cstring>
#include <memory>

#include "MyString.h"

namespace project
{
	MyString::MyString(const char* str)
		: mCStr()
		, mLength()
	{
		mLength = std::strlen(str);
		mCStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength + 1; i++)
		{
			mCStr[i] = str[i];
		}	
	}
	
	MyString::MyString(const MyString& rhs)
		: mCStr()
		, mLength(rhs.mLength)
	{
		mCStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength+1; i++)
		{
			mCStr[i] = rhs.mCStr[i];
		}
	}

	MyString::MyString(MyString&& rhs) noexcept
		: mCStr(rhs.mCStr)
		, mLength(rhs.mLength)
	{
		rhs.mCStr = nullptr;
		rhs.mLength = 0;
	}

	MyString::~MyString()
	{
		delete mCStr;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		if (this != &rhs)
		{
			delete mCStr;
			mLength = rhs.mLength;
			mCStr = new char[mLength+ 1];
			for (size_t i = 0; i < mLength+1; i++)
			{
				mCStr[i] = rhs.mCStr[i];
			}
		}
		return *this;
	}
	
	MyString& MyString::operator=(MyString&& rhs) noexcept
	{
		if (this != &rhs)
		{
			delete mCStr;
			mLength = rhs.mLength;
			mCStr = rhs.mCStr;
			rhs.mCStr = nullptr;
			rhs.mLength = 0;
		}
		return *this;
	}

	size_t MyString::GetLength() const
	{
		return mLength;
	}


	const char* MyString::GetCString() const
	{
		return mCStr;
	}

	bool MyString::Append(size_t totalLength)
	{
		return Append(totalLength, ' ');
	}

	bool MyString::Append(size_t totalLength, char ch)
	{
		if (mLength >= totalLength)
		{
			return false;
		}
		else
		{
			char* newString = new char[totalLength + 1];
			for (size_t i = 0; i < mLength; i++)
			{
				newString[i] = mCStr[i];
			}
			for (size_t i = mLength; i < totalLength; i++)
			{
				newString[i] = ch;
			}
			newString[totalLength] = '\0';
			
			delete mCStr;
			mCStr = newString;
			return true;
		}
	}

	bool MyString::Remove(size_t index)
	{
		if (index >= mLength)
		{
			return false;
		}
		else
		{
			for (size_t i = index; i < mLength; i++)
			{
				mCStr[i] = mCStr[i + 1];
			}
			return true;
		}
	}

	std::ostream& operator<<(std::ostream& out, const MyString& rhs)
	{
		out << rhs.GetCString();
		return out;
	}
}