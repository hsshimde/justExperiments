#pragma once

#include "Lawn.h"
#include "IFencable.h"

namespace lab5
{
	class EquilateralTriangleLawn : public Lawn, public IFenceable
	{
	public:
		EquilateralTriangleLawn(size_t side);
		EquilateralTriangleLawn(const EquilateralTriangleLawn& rhs);
		EquilateralTriangleLawn& operator=(const EquilateralTriangleLawn& rhs);

		virtual ~EquilateralTriangleLawn();

		size_t GetArea() const;
		size_t GetMinimumFencesCount() const;
		size_t GetFencePrice(eFenceType fenceType) const;


	private:
		size_t mSide;


	};
}