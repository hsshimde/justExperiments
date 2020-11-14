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
			
		}

		return os;
	}
}