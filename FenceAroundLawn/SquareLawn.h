#pragma once

#include "IFencable.h"
#include "eGrassType.h"
#include "RectangleLawn.h"

namespace lab5
{
	class SquareLawn : public RectangleLawn
	{
	public:
		SquareLawn(size_t width);
		SquareLawn(const SquareLawn& rhs);
		SquareLawn& operator=(const SquareLawn& rhs);
		virtual ~SquareLawn();

	};
}