#pragma once

namespace assignment2
{
	class IDrivable
	{
	public:
		virtual unsigned int GetDriveSpeed() const = 0;
		size_t GetMaxSpeed() const;
		
	};
}