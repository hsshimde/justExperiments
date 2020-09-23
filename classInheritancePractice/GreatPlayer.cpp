#include "GreatPlayer.h"

namespace greatplayer
{

	GreatPlayer::GreatPlayer()
		:Player{}
		,mGuts{false}
	{
		
	}

	GreatPlayer::GreatPlayer(const std::string& name,size_t performance,bool hasGuts)
		:Player{ name,performance }
		, mGuts{ hasGuts }
	{

	}
	
	GreatPlayer::GreatPlayer(const Player& rhs,bool hasGuts)
		:Player{ rhs }
		, mGuts{ hasGuts }
	{

	}

	GreatPlayer::GreatPlayer(const GreatPlayer& rhs)
		:Player{ rhs }
		, mGuts{ rhs.mGuts }
	{
		
	}

	bool GreatPlayer::HasGuts() const
	{
		return mGuts;
	}



}