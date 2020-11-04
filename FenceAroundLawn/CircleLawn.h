#pragma once
#include <cmath>

#include "Lawn.h"


namespace lab5
{
	class CircleLawn : public Lawn
	{
	public:
		CircleLawn(size_t radius);
		CircleLawn(const CircleLawn& rhs);
		CircleLawn& operator=(const CircleLawn& rhs);

		virtual ~CircleLawn();

		size_t GetArea() const;

	private:
		size_t mRadius;

	};
}
