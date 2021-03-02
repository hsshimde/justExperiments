#pragma once


namespace game
{
	class Bullet
	{
	public:
		Bullet(float x=10.0f, float y=10.0f) : mX(x), mY(y),mbHitEnemy(false) {}


		float mX;
		float mY;
		bool mbHitEnemy;
		ULONGLONG mHitTick;
	};
}