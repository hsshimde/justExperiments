#include <iostream>
#include "SpaceShip.h"

int main()
{
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