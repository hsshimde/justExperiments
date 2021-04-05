#include <fstream>
#include <strstream>
#include <cassert>
#include <EASTL/vector.h>
#include <EASTL/sort.h>
#include <EASTL/queue.h>
#include <EASTL/list.h>
#include <vector>

#include "TehmarniEAStlHeader.h"
#include "FunctionObject.h"
#include "olcConsoleGameEngine.h"
#include "Vector3D.h"

class TaeDdangGraphicEngine : public olcConsoleGameEngine
{
public:
	TaeDdangGraphicEngine();
	//~TaeDdangGraphicEngine();

private:

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserDestroy() override;

	void initiateWithAssignment();
	bool initiateFromFile(const char* fileName);


	Matrix4D MultiplyMatrix(const Matrix4D& op1, const Matrix4D& op2) const;
	//void MultiplyTriangle(Triangle& out, const Triangle& in, const Matrix4D& mat) const;
	void ProjectTriangle(Triangle* in, const Matrix4D& mat) const;

	Matrix4D GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up);
	Matrix4D GetInverseMatrix(const Matrix4D& mat);

	Matrix4D GetRotateMatrixX(const float theta) const;
	Matrix4D GetRotateMatrixY(const float theta) const;
	Matrix4D GetRotateMatrixZ(const float theta) const;
	Matrix4D GetIdentityMatrix() const;
	Matrix4D GetProjectionMatrix(float fNear, float fFar, float fFOV, int nScreenHeight, int nScreenWidth);
	Matrix4D GetTranslationMatrix(const Vector3D& position);

	size_t ClipTriangleAgainstPlane(const Vector3D& normal, const Vector3D& point, const Triangle in, Triangle out1, Triangle out2);
	void ClipAgainstFaceAndProjectAndStore(Triangle& targetTriangle, const Matrix4D& mat, eastl::vector<Triangle>& vectorTriangle);
	eastl::list<Triangle> ClipTrianglesAgaintCorners(const eastl::vector<Triangle>& vectriangles);


private:
	Mesh mMesh;
	float mfTheta;
	float mnScreenOffset;
	float mfYAxisCameraRotateAngle;
	float mfXAxisCameraRotateAngle;
	Vector3D mvCamera;
	const Vector3D mvLookDirection;

	const float mfVerticalMoveSpeed = 8.0f;
	const float mfHorizantalMoveSpeed = 8.0f;
	static const float fPi;
	const float mfAngularMoveSpeed = 2.0f * fPi / 3.0f;

	Matrix4D mMLeftRecRotate;
	Matrix4D mMRightRecRotate;
	Matrix4D mMProject;

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
		bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; //This is the original code from olc engine
		//bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; //This is what I turned into 
	}

	CHAR_INFO c;
	c.Attributes = bg_col | fg_col;
	c.Char.UnicodeChar = sym;
	return c;
}

TaeDdangGraphicEngine::TaeDdangGraphicEngine()
	: mMesh{ }
	, mfTheta{ }
	, mnScreenOffset{  }
	, mvCamera{ }
	, mfYAxisCameraRotateAngle{ }
	, mfXAxisCameraRotateAngle{ }
	, mvLookDirection{ 0.0f, 0.0f, 1.0f }
	, mMProject{}
{
	
}

//TaeDdangGraphicEngine::~TaeDdangGraphicEngine()
//{
//	while (!mTriangleMemoryPool.empty())
//	{
//		delete mTriangleMemoryPool.front();
//		mTriangleMemoryPool.pop();
//	}
//}

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
		mvCamera.mfY = 20.0f;
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
	size_t poolSize = mMesh.triangles.size() * 2;
	for (size_t i = 0; i < poolSize; i++)
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

Matrix4D TaeDdangGraphicEngine::GetTranslationMatrix(const Vector3D& position)
{
	Matrix4D translationMatrix{};
	translationMatrix.m[0][0] = 1.0f;
	translationMatrix.m[1][1] = 1.0f;
	translationMatrix.m[2][2] = 1.0f;
	translationMatrix.m[3][3] = 1.0f;

	translationMatrix.m[0][3] = position.mfX;
	translationMatrix.m[1][3] = position.mfY;
	translationMatrix.m[2][3] = position.mfZ;
	return translationMatrix;
}

size_t TaeDdangGraphicEngine::ClipTriangleAgainstPlane(const Vector3D& normal, const Vector3D& passingPoint, const Triangle* targetTriangle, Triangle* newTri1, Triangle* newTri2)
{
	float fPlaneEquationValue[3]{};
	fPlaneEquationValue[0] = targetTriangle->Point[0].GetPlaneEquationValue(normal, passingPoint);
	fPlaneEquationValue[1] = targetTriangle->Point[1].GetPlaneEquationValue(normal, passingPoint);
	fPlaneEquationValue[2] = targetTriangle->Point[2].GetPlaneEquationValue(normal, passingPoint);
	
	size_t nOutPointIndex[3]{};
	size_t nInPointIndex[3]{};
	size_t nOutPointNumber{};
	size_t nInPointNumber{};
	for (size_t i = 0; i < 3; i++)
	{
		if (fPlaneEquationValue[i] < 0.0f)
		{
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
		return 0;
	}
	else if (nOutPointNumber == 2)  // two vectors should be replaced by two intersecting vectors and it creates just one new triangle to rasterize
	{
		size_t nInIndex = nInPointIndex[nInPointNumber - 1];  // Unwrapping the information to debug comfortably
		const Vector3D* InPoint = &targetTriangle->Point[nInIndex];
		float checkPlaneEquationValue = InPoint->GetPlaneEquationValue(normal, passingPoint);  //to ensure there is no logical errors
		assert(checkPlaneEquationValue >= 0.0f);
		size_t newPointIndex{ 1 };
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
				newTri1->Point[newPointIndex++] = InPoint->GetIntersectPlaneVector(normal, passingPoint, *vEndPointVector);
			}
		}
		newTri1->color = targetTriangle->color;
		newTri1->symbol = targetTriangle->symbol;
		return 1;
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
		newTri1->symbol = targetTriangle->symbol;
		newTri1->color = targetTriangle->color;

		newTri2->Point[0] = *vInPoint[1];
		newTri2->Point[1] = *vIntersectVectors[0];
		newTri2->Point[2] = *vIntersectVectors[1];
		newTri1->symbol = targetTriangle->symbol;
		newTri1->color = targetTriangle->color;


		return 2;
	}
	else   // when nOutPointNumber == 0,  the entire triangle is in the view
	{
		newTri1->Point[0] = targetTriangle->Point[0];
		newTri1->Point[1] = targetTriangle->Point[1];
		newTri1->Point[2] = targetTriangle->Point[2];
		newTri1->symbol = targetTriangle->symbol;
		newTri1->color = targetTriangle->color;
		return 1;
	}
	
}

void TaeDdangGraphicEngine::ClipAgainstFaceAndProjectAndStore(Triangle targetTriangle, const Matrix4D& viewMatrix, eastl::vector<Triangle>& vectorTriangle)
{
	Triangle pClippedTriangle[2]{};
	for (size_t i = 0; i < 2; i++)
	{
		assert(!mTriangleMemoryPool.empty());
		pClippedTriangle[i] = *mTriangleMemoryPool.front();
		mTriangleMemoryPool.pop();
	}

	size_t nClippedTriangleCount = ClipTriangleAgainstPlane({ 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.01f }, targetTriangle, pClippedTriangle[0], pClippedTriangle[1]);
	//mTriangleMemoryPool.push(targetTriangle);
	for (size_t i = 0; i < nClippedTriangleCount; i++)
	{
		Triangle& projectedTriangle = pClippedTriangle[i];
		projectedTriangle.Point[0] = pClippedTriangle[i].Point[0].MultiplyMatrix(mMProject);
		projectedTriangle.Point[1] = pClippedTriangle[i].Point[1].MultiplyMatrix(mMProject);
		projectedTriangle.Point[2] = pClippedTriangle[i].Point[2].MultiplyMatrix(mMProject);
		projectedTriangle.color =    pClippedTriangle[i].color;
		projectedTriangle.symbol =   pClippedTriangle[i].symbol;

		Vector3D vOffset{ 1.0f, 1.0f, 0.0f };
		projectedTriangle.Point[0] /= projectedTriangle.Point[0].mfW;
		projectedTriangle.Point[1] /= projectedTriangle.Point[1].mfW;
		projectedTriangle.Point[2] /= projectedTriangle.Point[2].mfW;
		projectedTriangle.Point[0].mfX *= -1.0f;
		projectedTriangle.Point[0].mfY *= -1.0f;
		projectedTriangle.Point[1].mfX *= -1.0f;
		projectedTriangle.Point[1].mfY *= -1.0f;
		projectedTriangle.Point[2].mfX *= -1.0f;
		projectedTriangle.Point[2].mfY *= -1.0f;
		projectedTriangle.Point[0] += vOffset;
		projectedTriangle.Point[1] += vOffset;
		projectedTriangle.Point[2] += vOffset;

		const float fHalfScreenWidth = static_cast<float>(ScreenWidth() * 0.5);
		const float fHalfScreenHeight = static_cast<float>(ScreenHeight() * 0.5);

		projectedTriangle.Point[0].mfX *= fHalfScreenWidth;
		projectedTriangle.Point[0].mfY *= fHalfScreenHeight;
		projectedTriangle.Point[1].mfX *= fHalfScreenWidth;
		projectedTriangle.Point[1].mfY *= fHalfScreenHeight;
		projectedTriangle.Point[2].mfX *= fHalfScreenWidth;
		projectedTriangle.Point[2].mfY *= fHalfScreenHeight;

		vectorTriangle.push_back(projectedTriangle);
	}
	mTriangleMemoryPool.push(targetTriangle);

	switch (nClippedTriangleCount)
	{
	case 0:
		mTriangleMemoryPool.push(pClippedTriangle[0]);
		mTriangleMemoryPool.push(pClippedTriangle[1]);
		break;
	case 1:
		mTriangleMemoryPool.push(pClippedTriangle[1]);
		break;

	case 2:
		break;


	default:
		break;
	}
	return;
}




eastl::list<Triangle*> TaeDdangGraphicEngine::ClipTrianglesAgaintCorners(const eastl::vector<Triangle>& trianglesToRasterize) 
{
	eastl::list<Triangle*> listTriangles{};
	Triangle* pClippedTriangle[2];
	size_t triangleCount = trianglesToRasterize.size();
	
	for (const auto& triangleToDraw : trianglesToRasterize)
	{
		eastl::queue<Triangle*> queueTriangles{};
		queueTriangles.push(triangleToDraw);
		size_t nNewTrianglesCount = 1;
		for (size_t nAngleNumber = 0; nAngleNumber < 4; nAngleNumber++)
		{
			while (nNewTrianglesCount > 0)
			{
				for (size_t i = 0; i < 2; i++)    // store memory for two potentially replacable triangles 
				{
					assert(!mTriangleMemoryPool.empty());
					pClippedTriangle[i] = mTriangleMemoryPool.front();
					mTriangleMemoryPool.pop();
				}
				nNewTrianglesCount--;
				Triangle* testTriangle = queueTriangles.front();
				queueTriangles.pop();
				size_t queueSize = queueTriangles.size();
				//Triangle*& originalTriangle = testTriangle;
				size_t nAddedTriangleCount{};

				switch (nAngleNumber)
				{
				case 0:
					nAddedTriangleCount = ClipTriangleAgainstPlane({ 1.0f,0.0f,0.0f }, { 0.0f, 0.0f, 0.0f }, testTriangle, pClippedTriangle[0], pClippedTriangle[1]);
					break;

				case 1:
					nAddedTriangleCount = ClipTriangleAgainstPlane({ 0.0f, -1.0f, 0.0f }, { 0.0f, static_cast<float>(ScreenHeight()) - 1.0f ,0.0f }, testTriangle, pClippedTriangle[0], pClippedTriangle[1]);
					break;

				case 2:
					nAddedTriangleCount = ClipTriangleAgainstPlane({-1.0f,0.0f,0.0f }, { static_cast<float>(ScreenWidth()) - 1.0f, 0.0f,0.0f }, testTriangle, pClippedTriangle[0], pClippedTriangle[1]);
					break;

				case 3:
					nAddedTriangleCount = ClipTriangleAgainstPlane({ 0.0f, 1.0f,0.0f }, { 0.0f,0.0f ,0.0f }, testTriangle, pClippedTriangle[0], pClippedTriangle[1]);
					break;

				default:
					break;
				}
				mTriangleMemoryPool.push(testTriangle);
				if (nAddedTriangleCount == 0)	//dont need to rasterize this triangle
				{
					mTriangleMemoryPool.push(pClippedTriangle[0]);
					mTriangleMemoryPool.push(pClippedTriangle[1]);
				}
				else if (nAddedTriangleCount == 1)
				{
					queueTriangles.push(pClippedTriangle[0]);  //A newly replaced  triangle to draw
															  // It does not need to be drawn. so put it back in the memory pool
					mTriangleMemoryPool.push(pClippedTriangle[1]);
				}
				else // (nNewTrianglesCount == 2)
				{
					assert(nAddedTriangleCount == 2);
					queueTriangles.push(pClippedTriangle[0]);   //newly replaced two triangles to draw
					queueTriangles.push(pClippedTriangle[1]);
				}
			}
			nNewTrianglesCount = queueTriangles.size();
				/*else
				{
					queueTriangles.push(pClippedTriangle[0]);
					queueTriangles.push(pClippedTriangle[1]);
					mTriangleMemoryPool.push(originalTriangle);
				}*/

		}
		while (!queueTriangles.empty())
		{
			listTriangles.push_back(queueTriangles.front());
			queueTriangles.pop();
		}

	}
	return listTriangles;
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
	//initiateFromFile("axis.obj");
	initiateFromFile("mountains.obj");
	//initiateFromFile("teapot.obj");
	//mvCamera.mfZ = -2.0f;
	//mfTheta = 3.14159f;
	const float fPi = 3.141592f;
	mMLeftRecRotate = GetRotateMatrixY(fPi / 2.0f);
	mMRightRecRotate = GetRotateMatrixY(-fPi / 2.0f);
	mMProject = GetProjectionMatrix(0.1f, 1000.0f, 3.14159f / 2.0f, ScreenHeight(), ScreenWidth());
	//mMRightRecRotate = GetRotateMatrixX(-fPi / 2.0f);

	return true;
}

bool TaeDdangGraphicEngine::OnUserUpdate(float fElapsedTime)
{
	/*const float fVerticalMoveSpeed = 8.0f;
	const float fHorizantalMoveSpeed = 8.0f;
	static const float fPi = 3.141592f;
	const float fAngularMoveSpeed = 2.0f * fPi / 3.0f;*/

	Matrix4D MYAxisCameraRotate = GetRotateMatrixY(mfYAxisCameraRotateAngle);
	Matrix4D MXAxisCameraRotate = GetRotateMatrixX(mfXAxisCameraRotateAngle);
	Matrix4D MCameraRotate = GetIdentityMatrix();
	MCameraRotate = MultiplyMatrix(MYAxisCameraRotate, MXAxisCameraRotate);
	Vector3D vRotatedLookDirection = mvLookDirection.MultiplyMatrix(MCameraRotate);
	//Vector3D vRotatedLookDirection = mvLookDirection.MultiplyMatrix(MYAxisCameraRotate);
	//assert(vRotatedLookDirection.GetSize() == 1.0f);
	//Vector3D unitVector
	if (GetKey(VK_UP).bHeld)
	{
		//mvCamera.mfY += mfHorizantalMoveSpeed * fElapsedTime;
		mfXAxisCameraRotateAngle -= mfAngularMoveSpeed * fElapsedTime;

	}
	if (GetKey(VK_DOWN).bHeld)
	{
		//mvCamera.mfY -= mfHorizantalMoveSpeed * fElapsedTime;
		mfXAxisCameraRotateAngle += mfAngularMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_LEFT).bHeld)
	{
		//mvCamera.mfX -= mfVerticalMoveSpeed * fElapsedTime;
		mfYAxisCameraRotateAngle -= mfAngularMoveSpeed * fElapsedTime;

	}
	if (GetKey(VK_RIGHT).bHeld)
	{
		//mvCamera.mfX += mfVerticalMoveSpeed * fElapsedTime;
		mfYAxisCameraRotateAngle += mfAngularMoveSpeed * fElapsedTime;
	}							
	if (GetKey(L'J').bHeld)
	{
		//mfYAxisCameraRotateAngle -= mfAngularMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'L').bHeld)
	{
		//mfYAxisCameraRotateAngle += mfAngularMoveSpeed * fElapsedTime;
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
		//mvCamera -= vRotatedLookDirection * fVerticalMoveSpeed * fElapsedTime;
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMRightRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * mfVerticalMoveSpeed;
	}
	if (GetKey(L'D').bHeld)
	{
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMLeftRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * mfVerticalMoveSpeed;
	}

	if (GetKey(L'Q').bReleased)
	{
		return false;
	}
	



	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

	eastl::vector<Triangle> vecProjectedTriangles{};

	Vector3D vUp = { 0.0f, 1.0f, 0.0f };
	Vector3D vTarget = mvCamera + vRotatedLookDirection;

	assert(mvCamera.mfW == 1.0f);

	Matrix4D cameraMatrix = GetPointAtMatrix(mvCamera, vTarget, vUp); //assert here!! Look what the problem is !!!
	Matrix4D viewMatrix = GetInverseMatrix(cameraMatrix);
	Matrix4D rotateYMatrix = GetRotateMatrixY(mfTheta);
	Matrix4D worldMatrix = GetTranslationMatrix({ 0.0f, 0.0f, 5.0f });

	for (const auto& originalTriangle : mMesh.triangles)
	{
		assert(!mTriangleMemoryPool.empty());
		Triangle* translatedTriangle = mTriangleMemoryPool.front();
		Triangle*& viewedTriangle = translatedTriangle;
		mTriangleMemoryPool.pop();

		translatedTriangle->Point[0] = originalTriangle.Point[0].MultiplyMatrix(worldMatrix);
		translatedTriangle->Point[1] = originalTriangle.Point[1].MultiplyMatrix(worldMatrix);
		translatedTriangle->Point[2] = originalTriangle.Point[2].MultiplyMatrix(worldMatrix);

		Vector3D firstVectorOnPlane = translatedTriangle->Point[1] - translatedTriangle->Point[0];
		Vector3D secondVectorOnPlane = translatedTriangle->Point[2] - translatedTriangle->Point[1];
		Vector3D normalVector = firstVectorOnPlane.GetCrossProduct(secondVectorOnPlane);

		float normalVectorSize = normalVector.GetSize();
		if (normalVectorSize == 0.0f) // if the normal vector is zero, it is mathematically wrong dont even bother to draw it
		{
			mTriangleMemoryPool.push(translatedTriangle);
			continue;
		}
		else
		{
			normalVector.Normalize();
		}

		Vector3D rayFromCameraToPlane = translatedTriangle->Point[0] - mvCamera;
		float rayAndNormalDotProduct = rayFromCameraToPlane.GetDotProduct(normalVector);

		if (rayAndNormalDotProduct >= 0.0f) // the triangle can't be seen in this angle, so let's move on to the next one
		{
			mTriangleMemoryPool.push(translatedTriangle);
			continue;
		}
		else
		{
			Vector3D lightDirection = { 0.0f, 1.0f, -1.0f };
			lightDirection.Normalize();

			float lightAndNormalDotProduct = lightDirection.GetDotProduct(normalVector);
			lightAndNormalDotProduct = (lightAndNormalDotProduct < 0.1f) ? 0.1f : lightAndNormalDotProduct;

			CHAR_INFO color = GetColour(lightAndNormalDotProduct);
			translatedTriangle->color = color.Attributes;
			translatedTriangle->symbol = color.Char.UnicodeChar;
			translatedTriangle->Point[0] = translatedTriangle->Point[0].MultiplyMatrix(viewMatrix);
			translatedTriangle->Point[1] = translatedTriangle->Point[1].MultiplyMatrix(viewMatrix);
			translatedTriangle->Point[2] = translatedTriangle->Point[2].MultiplyMatrix(viewMatrix);

			ClipAgainstFaceAndProjectAndStore(translatedTriangle, viewMatrix, vecProjectedTriangles);
		}
	}
	
	eastl::quick_sort(begin(vecProjectedTriangles), end(vecProjectedTriangles), CompareZCoordinate());
	eastl::list<Triangle*> listTriangles = ClipTrianglesAgaintCorners(vecProjectedTriangles);
	for (const auto& triangleToDraw : listTriangles)
	{
		const float fhalfScreenWidth = static_cast<float>(ScreenWidth());
		const float fhalfScreenHeight = static_cast<float>(ScreenHeight());

		int x1 = static_cast<int>(triangleToDraw->Point[0].mfX );
		int y1 = static_cast<int>(triangleToDraw->Point[0].mfY );

		int x2 = static_cast<int>(triangleToDraw->Point[1].mfX );
		int y2 = static_cast<int>(triangleToDraw->Point[1].mfY );

		int x3 = static_cast<int>(triangleToDraw->Point[2].mfX );
		int y3 = static_cast<int>(triangleToDraw->Point[2].mfY );

		FillTriangle(x1, y1,
			x2, y2,
			x3, y3,
			triangleToDraw->symbol, triangleToDraw->color);
	}
	while (!listTriangles.empty())
	{
		mTriangleMemoryPool.push(listTriangles.front());
		listTriangles.pop_front();
	}

	return true;

}


		/*int x1 = static_cast<int>(triangleToDraw->Point[0].mfX * fhalfScreenWidth);
		int y1 = static_cast<int>(triangleToDraw->Point[0].mfY * fhalfScreenHeight);

		int x2 = static_cast<int>(triangleToDraw->Point[1].mfX * fhalfScreenWidth);
		int y2 = static_cast<int>(triangleToDraw->Point[1].mfY * fhalfScreenHeight);

		int x3 = static_cast<int>(triangleToDraw->Point[2].mfX * fhalfScreenWidth);
		int y3 = static_cast<int>(triangleToDraw->Point[2].mfY * fhalfScreenHeight);*/


		/*FillTriangle(x1, y1,
			x2, y2,
			x3, y3,
			triangleToDraw->symbol, triangleToDraw->color);*/

	/*
	for (const auto& pTriangle : mapTrianlgesToRasterize)
	{
		mTriangleMemoryPool.push(pTriangle);
	}*/


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
