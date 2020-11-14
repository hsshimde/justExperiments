#include <iostream>
#include "SpaceShip.h"

int main()
{
	size_t enemySize{ 5 };
	for (size_t i{}; i < enemySize; ++i)
	{
		for (size_t j{1}; j < enemySize - i; ++j)
		{
			printf(" ");
		}

		for (size_t j{}; j < 2 * i + 1; ++j)
		{
			printf("*");
		}

		printf("\n");
	}

	size_t enemyLegLength{ 2 };

	for (size_t i{}; i < enemyLegLength; ++i)
	{
		size_t firstLegIndex{ 1 };
		size_t secondLegIndex{ 5 };
		
		if (i % 2 == 0)
		{
			for (size_t j{}; j < 2 * enemySize + 1; ++j)
			{
				if (j != firstLegIndex && j != secondLegIndex-1)
				{
					printf(" ");
				}

				else if(j == firstLegIndex)
				{
					printf("|_");
				}

				else
				{
					printf("_|");
				}

			}
		}

		else
		{
			for (size_t j{}; j < 2 * enemySize + 1; ++j)
			{
				if (j != firstLegIndex && j != secondLegIndex - 1)
				{
					printf(" ");
				}

				else if (j == firstLegIndex)
				{
					printf("_|");
				}

				else
				{
					printf("|_");
				}
			}

		}

		printf("\n");
		

	}

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