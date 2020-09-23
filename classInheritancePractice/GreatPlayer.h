#pragma once
#include "Player.h"

namespace greatplayer
{
	using player::Player;

	class GreatPlayer : public Player
	{
	public:
		GreatPlayer();
		GreatPlayer(const std::string& name, size_t performance, bool hasGuts);
		GreatPlayer(const Player& player, bool hasGuts);
		GreatPlayer(const GreatPlayer& greatPlayer);
		bool HasGuts() const;
	
	private:
		bool mGuts;


	};
}