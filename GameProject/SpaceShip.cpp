#include <iostream>
#include <cassert>
#include "SpaceShip.h"
void printDownSidePyramid(size_t n);
void changeNumber(size_t& n);
int main()
{

	for (size_t i{}; i < 10; ++i)
	{
		printDownSidePyramid(i);
	}

	size_t experiment{ 10 };

	changeNumber(experiment);
	//assert(experiment != 20);

	
	return 0;
	

}

namespace spaceship
{

	SpaceShip* SpaceShip::GetInstance()
	{
		static SpaceShip* instance{ new SpaceShip{} };

		return instance;
	}

	SpaceShip::SpaceShip()
		: mX{20}
		, mY{20}
	{
		
	}

	std::ostream& operator<<(std::ostream& out, const SpaceShip& spaceShip)
	{
		for (size_t i{}; i < spaceShip.mX; ++i)std::cout << " "; std::cout << " /\\\n";
		for (size_t i{}; i < spaceShip.mX; ++i)std::cout << " "; std::cout << "/++\\\n ";
		for (size_t i{}; i < spaceShip.mX - 3; ++i)std::cout << " "; std::cout << "[++++++]\n";
		for (size_t i{}; i < spaceShip.mX - 2; ++i)std::cout << " "; std::cout << "/|\\  /|\\\n";

		return out;
	}
}

void printDownSidePyramid(size_t n)
{
	for (size_t i{}; i < n; ++i)
	{
		for (size_t j{}; j < i; ++j)
		{
			printf(" ");
		}
		for (size_t j{}; j < 2 * n + 1 - 2 * (i + 1); ++j)
		{
			printf("*");
		}

		printf("\n");
	}
}

void changeNumber(size_t& n)
{
	n += 10;
}