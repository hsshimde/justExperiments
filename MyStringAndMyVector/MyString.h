#pragma once
#include <iostream>

namespace project
{
	class MyString
	{
	public:
		MyString(const char* str);
		MyString(const MyString& rhs);
		MyString(MyString&& rhs) noexcept;
		~MyString();

		MyString& operator=(const MyString& rhs);
		MyString& operator=(MyString&& rhs) noexcept;

		size_t GetLength() const;
		const char* GetCString() const;

		bool Append(size_t totalLength);
		bool Append(size_t totalLength, char ch);
		bool Remove(size_t index);

		friend std::ostream& operator<<(std::ostream& out, const MyString& str);

	private:
		char* mCStr;
		size_t mLength;

	};

}