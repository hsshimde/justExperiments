#pragma once
#include <iostream>

namespace enemy
{
	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy();


		friend std::ostream& operator<<(std::ostream& out, const Enemy& enemey);


	private:
		size_t mX;	
		size_t mY;

	};
}