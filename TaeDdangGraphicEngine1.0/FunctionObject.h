#pragma once
#include "Vector3D.h"
class CompareZElement
{
public:
	bool operator()(const float tri1, const float tri2) const
	{
		return tri1 < tri2;
	}
};
//class CompareZElement
//{
//public:
//	bool operator()(const Triangle& tri1, const Triangle& tri2) const
//	{
//		return (tri1.Point[0].mfZ + tri1.Point[1].mfZ + tri1.Point[2].mfZ < tri2.Point[0].mfZ + tri2.Point[1].mfZ + tri2.Point[2].mfZ);
//	}
//};
class CompareZCoordinate
{
public:
	bool operator()(const Triangle* tri1, const Triangle* tri2) const
	{
		return (tri1->Point[0].mfZ + tri1->Point[1].mfZ + tri1->Point[2].mfZ < tri2->Point[0].mfZ + tri2->Point[1].mfZ + tri2->Point[2].mfZ);
	}
};