#pragma once

namespace project
{
	class MyString
	{
	public:
		MyString(const char* str);
		MyString(const MyString& rhs);
		MyString(MyString&& rhs);
		~MyString();

		MyString& operator=(const MyString& rhs);
		MyString& operator=(MyString&& rhs);

		size_t GetLength() const;
		const char* GetCString() const;

		bool Append(size_t totalLength);
		bool Append(size_t totalLength, char ch);

	private:
		char* mCStr;
		size_t mLenght;

	};

}