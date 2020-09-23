#include "Player.h"

namespace player
{
	Player::Player()
		:mName{"Not given"}
		,mPerformance{0}
	{
		
	}

	Player::Player(const std::string& name, size_t performance)
		:mName{name}
		,mPerformance{performance}
	{

	}

	Player::Player(const Player& player)
		:mName{ player.mName }
		, mPerformance{ player.mPerformance }
	{

	}

	Player::~Player()
	{

	}

	const std::string& Player::GetPlayerName() const
	{
		return mName;
	}

	size_t Player::GetPlayerPerformance() const
	{
		return mPerformance;
	}
}