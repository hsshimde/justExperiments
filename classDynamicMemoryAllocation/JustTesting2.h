#pragma once
#include <iostream>
#include <string>


const int BUF = 512;

namespace placenew2
{
	class JustTesting
	{
	public:
		JustTesting();
		JustTesting(const char* s, int n);
		~JustTesting();
		void Show() const;

	private:
		std::string mName;
		int mNumber;
	};
}