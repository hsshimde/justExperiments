#pragma once
#include <string>
namespace player
{
	class Player
	{
	public:
		Player();
		Player(const std::string& name, size_t performance);
		Player(const Player& player);
		~Player();

		const std::string& GetPlayerName() const;
		size_t GetPlayerPerformance() const;
	
	private:
		std::string mName;
		size_t mPerformance;

	};
}