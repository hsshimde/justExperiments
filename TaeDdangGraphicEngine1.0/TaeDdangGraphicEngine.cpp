#include <fstream>
#include <strstream>
#include <cassert>
#include <EASTL/vector_multimap.h>
#include <EASTL/vector.h>
#include <EASTL/map.h>
#include <EASTL/sort.h>
#include <EASTL/queue.h>

#include "TehmarniEAStlHeader.h"
#include "FunctionObject.h"
#include "olcConsoleGameEngine.h"
#include "Vector3D.h"

class TaeDdangGraphicEngine : public olcConsoleGameEngine
{
public:
	TaeDdangGraphicEngine();

private:

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserDestroy() override;

	void initiateWithAssignment();
	bool initiateFromFile(const char* fileName);


	Matrix4D MultiplyMatrix(const Matrix4D& op1, const Matrix4D& op2) const;
	void MultiplyTriangle(Triangle& out, const Triangle& in, const Matrix4D& mat) const;
	void ProjectTriangle(Triangle* in, const Matrix4D& mat) const;

	Matrix4D GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up);
	Matrix4D GetInverseMatrix(const Matrix4D& mat);

	Matrix4D GetRotateMatrixX(const float theta) const;
	Matrix4D GetRotateMatrixY(const float theta) const;
	Matrix4D GetRotateMatrixZ(const float theta) const;
	Matrix4D GetIdentityMatrix() const;
	Matrix4D GetProjectionMatrix(float fNear, float fFar, float fFOV, int nScreenHeight, int nScreenWidth);

	size_t ClipTriangleAgainstPlane(const Vector3D& normal, const Vector3D& point, const Triangle* in, Triangle* out1, Triangle* out2);
	//float GetPlaneEquationValue(const Vector3D& target, const Vector3D& normal, const Vector3D& point);


private:
	Mesh mMesh;
	float mfTheta;
	float mnScreenOffset;
	float mfYCameraAxisRotate;
	Vector3D mvCamera;
	const Vector3D mvLookDirection;

	const float mfVerticalMoveSpeed = 8.0f;
	const float mfHorizantalMoveSpeed = 8.0f;
	static const float fPi;
	const float mfAngularMoveSpeed = 2.0f * fPi / 3.0f;

	Matrix4D mMLeftRecRotate;
	Matrix4D mMRightRecRotate;

	eastl::queue<Triangle*> mTriangleMemoryPool;

};

CHAR_INFO GetColour(float lum)
{
	short bg_col, fg_col;
	wchar_t sym;
	int pixel_bw = static_cast<int>(13.0f * lum);
	switch (pixel_bw)
	{
	case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;
		//bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
	case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
	case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
	case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
	case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

	case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
	case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
	case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
	case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

	case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
	case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
	case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
	case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
	default:
		//bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; //This is the original code from olc engine
		bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; //This is what I turned into 
	}

	CHAR_INFO c;
	c.Attributes = bg_col | fg_col;
	c.Char.UnicodeChar = sym;
	return c;
}

TaeDdangGraphicEngine::TaeDdangGraphicEngine()
	: mMesh()
	, mfTheta(0.0f)
	, mnScreenOffset(0.0f)
	, mvCamera()
	, mfYCameraAxisRotate{ 0.0f }
	, mvLookDirection{ 0.0f, 0.0f, 1.0f }
{

}

const float TaeDdangGraphicEngine::fPi = 3.141592f;

bool TaeDdangGraphicEngine::initiateFromFile(const char* fileName)
{
	std::fstream fileHandle(fileName);
	if (!fileHandle.is_open())
	{
		return false;
	}
	bool bItsAxis = false;
	switch (fileName[0])
	{
	case 't':
		mnScreenOffset = 6.5f;
		break;
	case 'V':
		mnScreenOffset = 9.5f;
		break;
	case 'a':
		mnScreenOffset = 3.5f;
		bItsAxis = true;
		break;
	case 'm':
		mnScreenOffset = -10.0f;
		break;
	}

	char line[100];
	eastl::vector<Vector3D> vVertex{};
	vVertex.reserve(5000);

	while (!fileHandle.eof())
	{
		fileHandle.getline(line, 100);
		std::strstream stream;
		stream << line;
		char indicator;
		stream >> indicator;

		if (indicator == 'v')
		{
			float x;
			float y;
			float z;

			stream >> x;
			stream >> y;
			stream >> z;
			//if (bItsAxis)
			//{
			//	/*x /= 12.0f;
			//	y /=
			//	z /= 12.0f;*/
			//	y *= -1.0f;
			//}
			vVertex.push_back(Vector3D(x, y, z));
		}
		else if (indicator == 'f')
		{
			int index[3];

			stream >> index[0];
			stream >> index[1];
			stream >> index[2];


			assert(static_cast<size_t>(index[0]) <= vVertex.size());
			assert(static_cast<size_t>(index[1]) <= vVertex.size());
			assert(static_cast<size_t>(index[2]) <= vVertex.size());

			Vector3D& v1 = vVertex[index[0] - 1];
			Vector3D& v2 = vVertex[index[1] - 1];
			Vector3D& v3 = vVertex[index[2] - 1];
			mMesh.triangles.push_back(Triangle{ v1,v2,v3 });
		}
	}
	size_t poolSize = mMesh.triangles.size();
	for (size_t i = 0; i < poolSize; i++)
	{
		mTriangleMemoryPool.push(new Triangle{});
	}
	return true;
}

void TaeDdangGraphicEngine::initiateWithAssignment()
{
	const float fCubeSize = 2.0f;
	mnScreenOffset = 2.5;
	mMesh.triangles =
	{
		//SOUTH
		Triangle{Vector3D{ 0.0f, 0.0f, 0.0f}, {0.0f, fCubeSize, 0.0f}  ,{ fCubeSize, fCubeSize, 0.0f }},

		Triangle{Vector3D{0.0f, 0.0f, 0.0f},    {fCubeSize, fCubeSize, 0.0f},    {fCubeSize, 0.0f, 0.0f }},


		//EAST
		Triangle{Vector3D{fCubeSize, 0.0f, 0.0f},   { fCubeSize, fCubeSize, 0.0f},   { fCubeSize, fCubeSize, fCubeSize } },

		Triangle{Vector3D{fCubeSize, 0.0f, 0.0f},  {  fCubeSize, fCubeSize, fCubeSize},  {  fCubeSize, 0.0f, fCubeSize } },

		//NORTH                                                     
		Triangle{Vector3D{fCubeSize, 0.0f, fCubeSize},   { fCubeSize, fCubeSize, fCubeSize},   { 0.0f, fCubeSize, fCubeSize} },
		Triangle{Vector3D{ fCubeSize, 0.0f, fCubeSize},  {  0.0f, fCubeSize, fCubeSize},  {  0.0f, 0.0f, fCubeSize }},

		// WEST                                                      
		Triangle{Vector3D{ 0.0f, 0.0f, fCubeSize},   { 0.0f, fCubeSize, fCubeSize },		{0.0f, fCubeSize, 0.0f} },
		Triangle{Vector3D{ 0.0f, 0.0f, fCubeSize},   { 0.0f, fCubeSize, 0.0f },		{0.0f, 0.0f, 0.0f} },

		// TOP                                                       
		Triangle{ Vector3D{0.0f, fCubeSize, 0.0f},   { 0.0f, fCubeSize, fCubeSize},		{fCubeSize,	fCubeSize,	fCubeSize }},
		Triangle{ Vector3D{0.0f, fCubeSize, 0.0f},   { fCubeSize, fCubeSize,	fCubeSize},  {  fCubeSize, fCubeSize, 0.0f }},

		// BOTTOM                                                    
		Triangle{Vector3D{fCubeSize, 0.0f, fCubeSize},   { 0.0f, 0.0f, fCubeSize},    {0.0f, 0.0f, 0.0f} },
		Triangle{Vector3D{fCubeSize, 0.0f, fCubeSize},  {  0.0f, 0.0f, 0.0f},   { fCubeSize, 0.0f, 0.0f} }

	};

	for (size_t i = 0; i < mMesh.triangles.size(); i++)
	{
		mTriangleMemoryPool.push(new Triangle{});
	}

}

Matrix4D TaeDdangGraphicEngine::GetRotateMatrixX(const float theta) const
{
	Matrix4D result;
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cosf(theta);
	result.m[1][2] = -std::sinf(theta);
	result.m[2][1] = std::sinf(theta);
	result.m[2][2] = std::cosf(theta);
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4D TaeDdangGraphicEngine::GetRotateMatrixY(const float theta) const
{
	Matrix4D result;
	result.m[0][0] = std::cosf(theta);
	result.m[0][2] = -std::sinf(theta);
	result.m[2][0] = std::sinf(theta);
	result.m[2][2] = std::cosf(theta);
	result.m[1][1] = 1.0f;
	result.m[3][3] = 1.0f;


	return result;
}

Matrix4D TaeDdangGraphicEngine::GetRotateMatrixZ(const float theta) const
{
	Matrix4D result;
	result.m[0][0] = std::cosf(theta);
	result.m[0][1] = -std::sinf(theta);
	result.m[1][0] = std::sinf(theta);
	result.m[1][1] = std::cosf(theta);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4D TaeDdangGraphicEngine::GetIdentityMatrix() const
{
	Matrix4D identity{};
	identity.m[0][0] = 1.0f;
	identity.m[1][1] = 1.0f;
	identity.m[2][2] = 1.0f;
	identity.m[3][3] = 1.0f;
	return identity;
}


Matrix4D TaeDdangGraphicEngine::GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up)
{
	//vec3d newForward = Vector_Sub(target, pos);
	//newForward = Vector_Normalise(newForward);

	//// Calculate new Up direction
	//vec3d a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
	//vec3d newUp = Vector_Sub(up, a);
	//newUp = Vector_Normalise(newUp);

	//// New Right direction is easy, its just cross product
	//vec3d newRight = Vector_CrossProduct(newUp, newForward);

	//// Construct Dimensioning and Translation Matrix	
	//mat4x4 matrix;
	//matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	//matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	//matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	//matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	//return matrix;


	Vector3D newForward = target - position;
	newForward.Normalize();

	Vector3D vectorForUp = newForward * (up.GetDotProduct(newForward));
	Vector3D newUp = up - vectorForUp;
	newUp.Normalize();

	Vector3D newRight = newUp.GetCrossProduct(newForward);
	float length = newRight.GetSize();
	assert(length != 0.0f);

	Matrix4D pointAtMatrix;
	pointAtMatrix.m[0][0] = newRight.mfX;
	pointAtMatrix.m[1][0] = newRight.mfY;
	pointAtMatrix.m[2][0] = newRight.mfZ;
	pointAtMatrix.m[3][0] = 0.0f;

	pointAtMatrix.m[0][1] = newUp.mfX;
	pointAtMatrix.m[1][1] = newUp.mfY;
	pointAtMatrix.m[2][1] = newUp.mfZ;
	pointAtMatrix.m[3][1] = 0.0f;

	pointAtMatrix.m[0][2] = newForward.mfX;
	pointAtMatrix.m[1][2] = newForward.mfY;
	pointAtMatrix.m[2][2] = newForward.mfZ;
	pointAtMatrix.m[3][2] = 0.0f;

	pointAtMatrix.m[0][3] = position.mfX;
	pointAtMatrix.m[1][3] = position.mfY;
	pointAtMatrix.m[2][3] = position.mfZ;
	pointAtMatrix.m[3][3] = 1.0f;

	return pointAtMatrix;

}

Matrix4D TaeDdangGraphicEngine::GetInverseMatrix(const Matrix4D& mat)
{
	/*mat4x4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;*/
	Matrix4D matrix;
	matrix.m[0][0] = mat.m[0][0];
	matrix.m[1][0] = mat.m[0][1];
	matrix.m[2][0] = mat.m[0][2];
	matrix.m[3][0] = 0.0f;

	matrix.m[0][1] = mat.m[1][0];
	matrix.m[1][1] = mat.m[1][1];
	matrix.m[2][1] = mat.m[1][2];
	matrix.m[3][1] = 0.0f;

	matrix.m[0][2] = mat.m[2][0];
	matrix.m[1][2] = mat.m[2][1];
	matrix.m[2][2] = mat.m[2][2];
	matrix.m[3][2] = 0.0f;

	matrix.m[0][3] = -(mat.m[0][3] * matrix.m[0][0] + mat.m[1][3] * matrix.m[0][1] + mat.m[2][3] * matrix.m[0][2]);
	matrix.m[1][3] = -(mat.m[0][3] * matrix.m[1][0] + mat.m[1][3] * matrix.m[1][1] + mat.m[2][3] * matrix.m[1][2]);
	matrix.m[2][3] = -(mat.m[0][3] * matrix.m[2][0] + mat.m[1][3] * matrix.m[2][1] + mat.m[2][3] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix4D GetInverseMatrix(const Matrix4D& mat)
{
	Matrix4D matrix;
	matrix.m[0][0] = mat.m[0][0];
	matrix.m[1][0] = mat.m[0][1];
	matrix.m[2][0] = mat.m[0][2];
	matrix.m[3][0] = 0.0f;

	matrix.m[0][1] = mat.m[1][0];
	matrix.m[1][1] = mat.m[1][1];
	matrix.m[2][1] = mat.m[1][2];
	matrix.m[3][1] = 0.0f;

	matrix.m[0][2] = mat.m[2][0];
	matrix.m[1][2] = mat.m[2][1];
	matrix.m[2][2] = mat.m[2][2];

	matrix.m[3][2] = 0.0f;
	matrix.m[0][3] = -(mat.m[0][3] * matrix.m[0][0] + mat.m[1][3] * matrix.m[0][1] + mat.m[2][3] * matrix.m[0][2]);
	matrix.m[1][3] = -(mat.m[0][3] * matrix.m[1][0] + mat.m[1][3] * matrix.m[1][1] + mat.m[2][3] * matrix.m[1][2]);
	matrix.m[2][3] = -(mat.m[0][3] * matrix.m[2][0] + mat.m[1][3] * matrix.m[2][1] + mat.m[2][3] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix4D TaeDdangGraphicEngine::MultiplyMatrix(const Matrix4D& op1, const Matrix4D& op2) const
{
	Matrix4D result;
	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			//float element = 0.0f;
			result.m[r][c] += op1.m[r][0] * op2.m[0][c];
			result.m[r][c] += op1.m[r][1] * op2.m[1][c];
			result.m[r][c] += op1.m[r][2] * op2.m[2][c];
			result.m[r][c] += op1.m[r][3] * op2.m[3][c];

			//result.m[r][c] = element;
		}
	}
	return result;
}

Matrix4D TaeDdangGraphicEngine::GetProjectionMatrix(float fNear, float fFar, float fFOV, int nScreenHeight, int nScreenWidth)
{
	Matrix4D projectionMatrix;

	float fAspectRatio = static_cast<float>(nScreenHeight) / static_cast<float>(nScreenWidth);
	float fFovRad = 1.0f / tanf(fFOV * 0.5f);

	projectionMatrix.m[0][0] = fAspectRatio * fFovRad;
	projectionMatrix.m[1][1] = fFovRad;
	projectionMatrix.m[2][2] = fFar / (fFar - fNear);
	projectionMatrix.m[2][3] = (-fFar * fNear) / (fFar - fNear);
	projectionMatrix.m[3][2] = 1.0f;
	projectionMatrix.m[3][3] = 0.0f;

	return projectionMatrix;
}

size_t TaeDdangGraphicEngine::ClipTriangleAgainstPlane(const Vector3D& normal, const Vector3D& passingPoint, const Triangle* targetTriangle, Triangle* newTri1, Triangle* newTri2)
{
	/*size_t nInPointNumber = 0;
	size_t nOutPointNumber = 0;*/

	/*float fPlaneEquationValue1 = in->Point[0].GetPlaneEquationValue(normal, point);
	float fPlaneEquationValue2 = in->Point[1].GetPlaneEquationValue(normal, point);
	float fPlaneEquationValue3 = in->Point[2].GetPlaneEquationValue(normal, point);*/

	float fPlaneEquationValue[3]{};
	fPlaneEquationValue[0] = targetTriangle->Point[0].GetPlaneEquationValue(normal, passingPoint);
	fPlaneEquationValue[1] = targetTriangle->Point[1].GetPlaneEquationValue(normal, passingPoint);
	fPlaneEquationValue[2] = targetTriangle->Point[2].GetPlaneEquationValue(normal, passingPoint);
	//bool bOutPointIndex[3] = { false };
	size_t nOutPointIndex[3]{};
	size_t nInPointIndex[3]{};
	size_t nOutPointNumber{};
	size_t nInPointNumber{};
	for (size_t i = 0; i < 3; i++)
	{
		if (fPlaneEquationValue[i] < 0.0f)
		{
			//nOutPointNumber++;
			nOutPointIndex[nOutPointNumber++] = i;
		}
		else
		{
			nInPointIndex[nInPointNumber++] = i;
		}
	}
	assert(nInPointNumber + nOutPointNumber == 3);

	if (nOutPointNumber == 3) //  Do nothing when the entire triangle is out of the view 
	{
		return 3;
	}
	else if (nOutPointNumber == 2)  // two vectors should be replaced by two intersecting vectors and it creates just one new triangle to rasterize
	{

		size_t nInIndex = nInPointIndex[nInPointNumber - 1];  // Unwrapping the information to debug comfortably
		const Vector3D* InPoint = &targetTriangle->Point[nInIndex];
		float checkPlaneEquationValue = InPoint->GetPlaneEquationValue(normal, passingPoint);  //to ensure there is no logical errors
		assert(checkPlaneEquationValue > 0.0f);
		size_t newTrianglePointIndex{ 1 };
		//newTri1->Point[0] = targetTriangle->Point[nPointIndex];
		for (size_t i = 0; i < 3; i++)
		{
			if (i == nInIndex)
			{
				newTri1->Point[0] = targetTriangle->Point[nInIndex];
			}
			else
			{
				//now Point[i] == outPoint => so you should get the intersect vector and put it in the new tiangle 
				const Vector3D* vEndPointVector = &targetTriangle->Point[i];
				newTri1->Point[newTrianglePointIndex++] = InPoint->GetIntersectPlaneVector(normal, passingPoint, *vEndPointVector);
			}
		}
		return 2;
	}

	else if (nOutPointNumber == 1)     //in this case, there should be two new triangles to replace the  clipped triangle
	{
		const Vector3D* vOutPoint = &targetTriangle->Point[nOutPointIndex[0]];
		const Vector3D* vInPoint[2]{};
		vInPoint[0] = &targetTriangle->Point[nInPointIndex[0]];
		vInPoint[1] = &targetTriangle->Point[nInPointIndex[1]];

		const Vector3D* vIntersectVectors[2]{};
		vIntersectVectors[0] = &vInPoint[0]->GetIntersectPlaneVector(normal, passingPoint, *vOutPoint);
		vIntersectVectors[1] = &vInPoint[1]->GetIntersectPlaneVector(normal, passingPoint, *vOutPoint);

		newTri1->Point[0] = *vInPoint[0];
		newTri1->Point[1] = *vIntersectVectors[0];
		newTri1->Point[2] = *vInPoint[1];

		newTri2->Point[0] = *vInPoint[1];
		newTri2->Point[1] = *vIntersectVectors[0];
		newTri2->Point[2] = *vIntersectVectors[1];

		return 1;
	}
	else   // when nOutPointNumber == 0,  the entire triangle is in the view
	{
		return 0;
	}
	
	/*if (fPlaneEquationValue1 > 0.0f)
	{
		nInPointNumber++;
	}
	else
	{
		bOutPointIndex[0] = true;
		nOutPointNumber++;
	}
	if (fPlaneEquationValue2 > 0.0f)
	{
		nInPointNumber++;
	}
	else
	{
		bOutPointIndex[1] = true;
		nOutPointNumber++;
	}
	if (fPlaneEquationValue3 > 0.0f)
	{
		nInPointNumber++;
	}
	else
	{
		bOutPointIndex[2]= true;
		nOutPointNumber++;
	}*/

	//for (size_t i = 0; i < 3; i++)
	//{
	//	if (fPlaneEquationValue[i] > 0.0f)
	//	{
	//		bOutPointIndex[i] = true;
	//		nInPointNumber++;
	//	}
	//}

	//if (nInPointNumber == 3)
	//{
	//	return 3;
	//}
	//if (nInPointNumber == 0)
	//{
	//	return 0;
	//}

	//if (nInPointNumber == 2)
	//{
	//	
	//}

	//else // when nInPointNumber == 1
	//{
	//	return 1;
	//}

}


void TaeDdangGraphicEngine::MultiplyTriangle(Triangle& out, const Triangle& in, const Matrix4D& mat) const
{
	out.Point[0] = in.Point[0].MultiplyMatrix(mat);
	out.Point[1] = in.Point[1].MultiplyMatrix(mat);
	out.Point[2] = in.Point[2].MultiplyMatrix(mat);
}

void TaeDdangGraphicEngine::ProjectTriangle(Triangle* in, const Matrix4D& mat) const
{

	in->Point[0] = in->Point[0].MultiplyMatrix(mat);
	in->Point[1] = in->Point[1].MultiplyMatrix(mat);
	in->Point[2] = in->Point[2].MultiplyMatrix(mat);

	in->Point[0].Divide(in->Point[0].mfZ);
	in->Point[1].Divide(in->Point[1].mfZ);
	in->Point[2].Divide(in->Point[2].mfZ);

	return;
}

inline bool TaeDdangGraphicEngine::OnUserCreate()
{

	//initiateWithAssignment();
	//initiateFromFile("VideoShip.obj");
	initiateFromFile("axis.obj");
	//initiateFromFile("mountains.obj");
	//initiateFromFile("teapot.obj");
	mvCamera.mfZ = -2.0f;
	//mfTheta = 3.14159f;
	const float fPi = 3.141592f;
	mMLeftRecRotate = GetRotateMatrixY(fPi / 2.0f);
	mMRightRecRotate = GetRotateMatrixY(-fPi / 2.0f);
	//mMRightRecRotate = GetRotateMatrixX(-fPi / 2.0f);

	return true;
}

bool TaeDdangGraphicEngine::OnUserUpdate(float fElapsedTime)
{
	/*const float fVerticalMoveSpeed = 8.0f;
	const float fHorizantalMoveSpeed = 8.0f;
	static const float fPi = 3.141592f;
	const float fAngularMoveSpeed = 2.0f * fPi / 3.0f;*/

	Matrix4D MRotateForCameraLookDirection = GetRotateMatrixY(mfYCameraAxisRotate);
	Vector3D vRotatedLookDirection = mvLookDirection.MultiplyMatrix(MRotateForCameraLookDirection);
	//assert(vRotatedLookDirection.GetSize() == 1.0f);
	//Vector3D unitVector
	if (GetKey(VK_UP).bHeld)
	{
		mvCamera.mfY -= mfHorizantalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_DOWN).bHeld)
	{
		mvCamera.mfY += mfHorizantalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_LEFT).bHeld)
	{
		mvCamera.mfX -= mfVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_RIGHT).bHeld)
	{
		mvCamera.mfX += mfVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'J').bHeld)
	{
		mfYCameraAxisRotate -= mfAngularMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'L').bHeld)
	{
		mfYCameraAxisRotate += mfAngularMoveSpeed * fElapsedTime;
	}

	if (GetKey(L'W').bHeld)
	{
		mvCamera += vRotatedLookDirection * mfVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'S').bHeld)
	{
		mvCamera -= vRotatedLookDirection * mfVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'A').bHeld)
	{
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMLeftRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * mfVerticalMoveSpeed;
	}
	if (GetKey(L'D').bHeld)
	{
		//mvCamera -= vRotatedLookDirection * fVerticalMoveSpeed * fElapsedTime;
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMRightRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * mfVerticalMoveSpeed;
	}



	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

	eastl::vector<Triangle*> mapTrianlgesToRasterize{};

	Vector3D vUp = { 0.0f, 1.0f, 0.0f };
	Vector3D vTarget = mvCamera + vRotatedLookDirection;

	assert(mvCamera.mfW == 1.0f);

	Matrix4D cameraMatrix = GetPointAtMatrix(mvCamera, vTarget, vUp); //assert here!! Look what the problem is !!!
	Matrix4D rotateY = GetRotateMatrixY(mfTheta);
	Matrix4D viewMatrix = GetInverseMatrix(cameraMatrix);

	for (const auto& originalTriangle : mMesh.triangles)
	{
		//assert(!mTriangleMemoryPool.empty());
		Triangle* translatedTriangle = mTriangleMemoryPool.front();
		Triangle*& viewedTriangle = translatedTriangle;
		mTriangleMemoryPool.pop();


		MultiplyTriangle(*translatedTriangle, originalTriangle, rotateY);
		//TranslateTriangle(*viewedTriangle, *translatedTriangle, viewMatrix);

		/*translatedTriangle->Point[0].AddScreenOffset(mnScreenOffset);
		translatedTriangle->Point[1].AddScreenOffset(mnScreenOffset);
		translatedTriangle->Point[2].AddScreenOffset(mnScreenOffset);*/

		Vector3D firstVectorOnPlane = translatedTriangle->Point[1] - translatedTriangle->Point[0];
		Vector3D secondVectorOnPlane = translatedTriangle->Point[2] - translatedTriangle->Point[1];
		Vector3D normalVector = firstVectorOnPlane.GetCrossProduct(secondVectorOnPlane);

		float normalVectorSize = normalVector.GetSize();

		if (normalVectorSize == 0.0f)
		{
			mTriangleMemoryPool.push(translatedTriangle);
			continue;
		}
		else
		{
			normalVector.Normalize();
		}
		//Vector3D rayFromCameraToPlane = centroidVector - mvCamera;
		//Vector3D rayFromCameraAtPlane = viewedTriangle->Point[0] - mvCamera;
		//Vector3D centroidVector = (viewedTriangle->Point[0] + viewedTriangle->Point[1] + viewedTriangle->Point[2]) / 3.0f;

		Vector3D rayFromCameraToPlane = translatedTriangle->Point[0] - mvCamera;
		float rayAndNormalDotProduct = rayFromCameraToPlane.GetDotProduct(normalVector);

		if (rayAndNormalDotProduct >= 0.0f) // the triangle can't be seen in this angle
		{
			mTriangleMemoryPool.push(translatedTriangle);
		}
		else// (rayAndNormalDotProduct < 0.0f)
		{
			//Vector3D lightDirection = (/*mvCamera +*/ vRotatedLookDirection) * -1.0f;
			Vector3D lightDirection = { 0.0f, 1.0f, -1.0f };
			lightDirection.Normalize();

			float lightAndNormalDotProduct = lightDirection.GetDotProduct(normalVector);
			lightAndNormalDotProduct = (lightAndNormalDotProduct < 0.1f) ? 0.1f : lightAndNormalDotProduct;

			CHAR_INFO color = GetColour(lightAndNormalDotProduct);
			translatedTriangle->color = color.Attributes;
			translatedTriangle->symbol = color.Char.UnicodeChar;

			Triangle*& viewedTriangle = translatedTriangle;
			viewedTriangle->Point[0] = translatedTriangle->Point[0].MultiplyMatrix(viewMatrix);
			viewedTriangle->Point[1] = translatedTriangle->Point[1].MultiplyMatrix(viewMatrix);
			viewedTriangle->Point[2] = translatedTriangle->Point[2].MultiplyMatrix(viewMatrix);

			size_t nNumberOfClippedVector = 0;
			Triangle* pClippedTriangle[2]{};
			for (size_t i = 0; i < 2; i++)
			{
				assert(!mTriangleMemoryPool.empty());
				pClippedTriangle[i] = mTriangleMemoryPool.front();
				mTriangleMemoryPool.pop();
			}

			nNumberOfClippedVector = ClipTriangleAgainstPlane({ 0.0f,0.0f,1.0f }, { 0.0f,0.0f,0.01f }, translatedTriangle, pClippedTriangle[0], pClippedTriangle[1]);

			if (nNumberOfClippedVector == 3) // no need to rasterize this one 
			{
				mTriangleMemoryPool.push(viewedTriangle);
				mTriangleMemoryPool.push(pClippedTriangle[0]);
				mTriangleMemoryPool.push(pClippedTriangle[1]);
				continue;
			}

			switch (nNumberOfClippedVector)
			{
			case 2: //triangle should be replaced by one clipped triangle 
				mTriangleMemoryPool.push(viewedTriangle);
				mTriangleMemoryPool.push(pClippedTriangle[1]);
				if (pClippedTriangle[0])
				{
					pClippedTriangle[0]->color = color.Attributes;
					pClippedTriangle[0]->symbol = color.Char.UnicodeChar;
				}
				//viewedTriangle = nullptr;
				pClippedTriangle[1] = nullptr;
				//mTriangleMemoryPool.push(pClippedTriangle[1]); 
				mapTrianlgesToRasterize.push_back(pClippedTriangle[0]);
				pClippedTriangle[0] = nullptr;
				break;

			case 1: //triangle should be replaced by two clipped triangle
				mTriangleMemoryPool.push(viewedTriangle);
				if (pClippedTriangle[0])
				{
					pClippedTriangle[0]->color = color.Attributes;
					pClippedTriangle[0]->symbol = color.Char.UnicodeChar;
				}
				if (pClippedTriangle[1])
				{
					pClippedTriangle[1]->color = color.Attributes;
					pClippedTriangle[1]->symbol = color.Char.UnicodeChar;
				}
				viewedTriangle = nullptr;
				mapTrianlgesToRasterize.push_back(pClippedTriangle[0]);
				mapTrianlgesToRasterize.push_back(pClippedTriangle[1]);

				pClippedTriangle[0] = nullptr;
				pClippedTriangle[1] = nullptr;
				break;


			case 0: //The triangle is unclipped at all
				mTriangleMemoryPool.push(pClippedTriangle[0]);
				mTriangleMemoryPool.push(pClippedTriangle[1]);
				pClippedTriangle[0] = nullptr;
				pClippedTriangle[1] = nullptr;
				mapTrianlgesToRasterize.push_back(viewedTriangle);
				break;
			default:
				;//do nothing

			}
			//mapTrianlgesToRasterize.push_back(translatedTriangle);
		}

	}
	eastl::quick_sort(begin(mapTrianlgesToRasterize), end(mapTrianlgesToRasterize), CompareZCoordinate());
	size_t trianglesCount = mapTrianlgesToRasterize.size();
	for (size_t i = 0; i < trianglesCount; ++i)
	{
		Triangle* triangleToDraw = mapTrianlgesToRasterize[i];
		Matrix4D projectMatrix = GetProjectionMatrix(0.1f, 1000.0f, 3.14159f / 2.0f, ScreenHeight(), ScreenWidth());
		ProjectTriangle(triangleToDraw, projectMatrix);



		triangleToDraw->Point[0].mfX += 1.0f;
		triangleToDraw->Point[0].mfY += 1.0f;

		triangleToDraw->Point[1].mfX += 1.0f;
		triangleToDraw->Point[1].mfY += 1.0f;

		triangleToDraw->Point[2].mfX += 1.0f;
		triangleToDraw->Point[2].mfY += 1.0f;

		const float fhalfScreenHeight = static_cast<float>(ScreenHeight() * 0.5f);
		const float fhalfScreenWidth = static_cast<float>(ScreenWidth() * 0.5f);

		/*const float fhalfScreenWidth = 1.0f;
		const float fhalfScreenHeight = 1.0f;*/

		/*const float fhalfScreenHeight = static_cast<float>(ScreenHeight() * 0.3f);
		const float fhalfScreenWidth = static_cast<float>(ScreenWidth() * 0.3f);*/

		int x1 = static_cast<int>(triangleToDraw->Point[0].mfX * fhalfScreenWidth);
		int y1 = static_cast<int>(triangleToDraw->Point[0].mfY * fhalfScreenHeight);

		int x2 = static_cast<int>(triangleToDraw->Point[1].mfX * fhalfScreenWidth);
		int y2 = static_cast<int>(triangleToDraw->Point[1].mfY * fhalfScreenHeight);

		int x3 = static_cast<int>(triangleToDraw->Point[2].mfX * fhalfScreenWidth);
		int y3 = static_cast<int>(triangleToDraw->Point[2].mfY * fhalfScreenHeight);

		Clip(x1, y1);
		Clip(x2, y2);
		Clip(x3, y3);

		FillTriangle(x1, y1,
			x2, y2,
			x3, y3,
			triangleToDraw->symbol, triangleToDraw->color);

	}
	for (const auto& pTriangle : mapTrianlgesToRasterize)
	{
		mTriangleMemoryPool.push(pTriangle);
	}
	return true;
}

bool TaeDdangGraphicEngine::OnUserDestroy()
{
	while (!mTriangleMemoryPool.empty())
	{
		delete mTriangleMemoryPool.front();
		mTriangleMemoryPool.pop();
	}
	return true;
}




int main()
{
	TaeDdangGraphicEngine demo;

	if (demo.ConstructConsole(260, 240, 4, 4))
	{
		demo.Start();
	}


	return 0;
}
