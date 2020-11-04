#pragma once

#include "Lawn.h"
#include "IFencable.h"
#include "eFenceType.h"


namespace lab5
{
	class RectangleLawn : public Lawn, public IFenceable
	{
	public:
		RectangleLawn(size_t width, size_t height);
		RectangleLawn(const RectangleLawn& rhs);
		virtual ~RectangleLawn();
		RectangleLawn& operator=(const RectangleLawn& rhs);


		virtual size_t GetArea() const;
		virtual size_t GetMinimumFencesCount() const;
		virtual size_t GetFencePrice(eFenceType fenceType) const;



	protected:
		size_t mWidth;
		size_t mHeight;

	};

}
