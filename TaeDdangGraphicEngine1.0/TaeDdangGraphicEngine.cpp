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
	void TranslateTriangle(Triangle& out, const Triangle& in, const Matrix4D& mat) const;
	void ProjectTriangle(Triangle* in, const Matrix4D& mat) const;

	Matrix4D GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up);
	Matrix4D GetInverseMatrix(const Matrix4D& mat);

	Matrix4D GetRotateMatrixX(const float theta) const;
	Matrix4D GetRotateMatrixY(const float theta) const;
	Matrix4D GetRotateMatrixZ(const float theta) const;
	Matrix4D GetIdentityMatrix() const;


	Matrix4D GetProjectionMatrix(float fNear, float fFar, float fFOV, int nScreenHeight, int nScreenWidth);


private:
	Mesh mMesh;
	float mfTheta;
	float mnScreenOffset;
	float mfYCameraAxisRotate;
	Vector3D mvCamera;
	const Vector3D mvLookDirection;

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

void TaeDdangGraphicEngine::TranslateTriangle(Triangle& out, const Triangle& in, const Matrix4D& mat) const
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

	initiateWithAssignment();
	//initiateFromFile("VideoShip.obj");
	//initiateFromFile("axis.obj");
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
	const float fVerticalMoveSpeed = 8.0f;
	const float fHorizantalMoveSpeed = 8.0f;
	static const float fPi = 3.141592f;
	const float fAngularMoveSpeed = 2.0f * fPi / 3.0f;

	Matrix4D MRotateForCameraLookDirection = GetRotateMatrixY(mfYCameraAxisRotate);
	Vector3D vRotatedLookDirection = mvLookDirection.MultiplyMatrix(MRotateForCameraLookDirection);
	//assert(vRotatedLookDirection.GetSize() == 1.0f);
	//Vector3D unitVector
	if (GetKey(VK_UP).bHeld)
	{
		mvCamera.mfY -= fHorizantalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_DOWN).bHeld)
	{
		mvCamera.mfY += fHorizantalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_LEFT).bHeld)
	{
		mvCamera.mfX -= fVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(VK_RIGHT).bHeld)
	{
		mvCamera.mfX += fVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'J').bHeld)
	{
		mfYCameraAxisRotate -= fAngularMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'L').bHeld)
	{
		mfYCameraAxisRotate += fAngularMoveSpeed * fElapsedTime;
	}

	if (GetKey(L'W').bHeld)
	{
		mvCamera += vRotatedLookDirection * fVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'S').bHeld)
	{
		mvCamera -= vRotatedLookDirection * fVerticalMoveSpeed * fElapsedTime;
	}
	if (GetKey(L'A').bHeld)
	{
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMLeftRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * fVerticalMoveSpeed;
	}
	if (GetKey(L'D').bHeld)
	{
		//mvCamera -= vRotatedLookDirection * fVerticalMoveSpeed * fElapsedTime;
		Vector3D vMoveDirection = vRotatedLookDirection.MultiplyMatrix(mMRightRecRotate);
		vMoveDirection.Normalize();
		mvCamera += vMoveDirection * fElapsedTime * fVerticalMoveSpeed;
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
		assert(!mTriangleMemoryPool.empty());
		Triangle* translatedTriangle = mTriangleMemoryPool.front();

		Triangle*& viewedTriangle = translatedTriangle;
		mTriangleMemoryPool.pop();

		TranslateTriangle(*translatedTriangle, originalTriangle, rotateY);
		TranslateTriangle(*viewedTriangle, *translatedTriangle, viewMatrix);

		viewedTriangle->Point[0].AddScreenOffset(mnScreenOffset);
		viewedTriangle->Point[1].AddScreenOffset(mnScreenOffset);
		viewedTriangle->Point[2].AddScreenOffset(mnScreenOffset);

		Vector3D firstVectorOnPlane = viewedTriangle->Point[1] - viewedTriangle->Point[0];
		Vector3D secondVectorOnPlane = viewedTriangle->Point[2] - viewedTriangle->Point[1];
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
		//Vector3D rayFromCameraAtPlane = viewedTriangle->Point[0] - mvCamera;
		//Vector3D centroidVector = (viewedTriangle->Point[0] + viewedTriangle->Point[1] + viewedTriangle->Point[2]) / 3.0f;
		//Vector3D rayFromCameraToPlane = centroidVector - mvCamera;
		Vector3D rayFromCameraToPlane = viewedTriangle->Point[0] - mvCamera;
		
		float rayAndNormalDotProduct = rayFromCameraToPlane.GetDotProduct(normalVector);
		if (rayAndNormalDotProduct < 0.0f)
		{
			Vector3D lightDirection = (/*mvCamera +*/ vRotatedLookDirection) * -1.0f;
			lightDirection.Normalize();
			float lightAndNormalDotProduct = lightDirection.GetDotProduct(normalVector);
			CHAR_INFO color = GetColour(lightAndNormalDotProduct);
			viewedTriangle->color = color.Attributes;
			viewedTriangle->symbol = color.Char.UnicodeChar;
			mapTrianlgesToRasterize.push_back(viewedTriangle);
		}
		else
		{
			mTriangleMemoryPool.push(viewedTriangle);
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
