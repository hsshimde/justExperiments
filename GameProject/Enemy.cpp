#include "Enemy.h"

namespace enemy
{

	Enemy::Enemy()
		: mX{}
		, mY{}
		, mbHit{ false }
	{

	}
	Enemy::~Enemy()
	{

	}

	std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
	{

		if (enemy.mbHit)
		{
			for (size_t i{}; i < 7; ++i)
			{
				for (size_t j{}; j < 7; ++j)
				{
					if (i == j || i == 6 - j)
					{
						printf("*");
					}

					else
					{
						printf(" ");
					}

				}
				printf("\n");
			}
		}
		
		else
		{
			size_t enemySize{ 3 };


			size_t enemyLegLength{ 2 };
			size_t firstLegIndex{ 1 };
			size_t secondLegIndex{ 3 };

			for (size_t i{}; i < enemyLegLength; ++i)
			{
				for (size_t j{}; j < 2 * enemySize + 1; ++j)
				{
					if (j == firstLegIndex || j == secondLegIndex)
					{
						printf("|");
					}

					else
					{
						printf(" ");
					}


				}

				printf("\n");
			}


			for (size_t i{}; i < enemySize; ++i)
			{
				for (size_t j{}; j < i; ++j)
				{
					printf(" ");
				}

				for (size_t j{}; j < 2 * (enemySize - i) - 1; ++j)
				{
					printf("*");
				}

				printf("\n");
			}

			
		}

		return os;
	}
}