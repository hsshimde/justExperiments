#pragma once
#include <iostream>

namespace spaceship
{
	class SpaceShip
	{
	public:
		SpaceShip* GetInstance();
		SpaceShip(const SpaceShip& rhs) = delete;
		SpaceShip& operator=(const SpaceShip& rhs) = delete;
		//~SpaceShip();

		void Attack();

		friend std::ostream& operator<<(std::ostream& out, const SpaceShip& spaceShip);

		


	private:
		SpaceShip();
		size_t mX;
		size_t mY;

	};
}