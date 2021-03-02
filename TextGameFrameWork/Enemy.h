#pragma once

namespace game
{
	enum class eMoveDirection {UP, DOWN};
	class Enemy
	{
	public:
		Enemy(float x, float y)
			: mX(x)
			, mY(y)
			, mbHit(false)
			, meMove(eMoveDirection::DOWN)
		{
			int nRandomValue = rand() % 100;
			if (nRandomValue >=50)
			{
				meMove = eMoveDirection::UP;
			}
			else
			{
				meMove = eMoveDirection::DOWN;
			}
		}
		Enemy(const Enemy& rhs) = delete;
		Enemy& operator=(const Enemy& rhs) = delete;
		
		float mX;
		float mY;
		bool mbHit;
		ULONGLONG mHitTick;
		eMoveDirection meMove;
	};
}