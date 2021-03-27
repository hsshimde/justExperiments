#include <fstream>
#include <strstream>
#include <cassert>
#include <algorithm>
#include <map>

#include "olcConsoleGameEngine.h"
#include "Vector3D.h"

class CompareZElement
{
public:
	bool operator()(const float tri1, const float tri2) const
	{
		return tri1 > tri2;
	}
};

class TaeDdangGraphicEngine : public olcConsoleGameEngine
{
public:
	TaeDdangGraphicEngine();

private:

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void initiateWithAssignment();
	bool initiateFromFile(const char* fileName);
	

	Matrix3D MultiplyMatrix3D(const Matrix3D& op1, const Matrix3D& op2) const;
	Triangle TranslateTriangle(const Triangle& tri, const Matrix3D& mat) const;
	Triangle ProjectTriangle(const Triangle& tri, const Matrix4D& mat) const;
	
	Matrix3D GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up);
	Matrix3D GetInverseMatrix(const Matrix3D& mat);

	Matrix3D GetRotateMatrixX(const float theta);
	Matrix3D GetRotateMatrixY(const float theta);
	Matrix3D GetRotateMatrixZ(const float theta);

	Matrix4D GetProjectionMatrix(float fNear, float fFar, float fFOV, int nScreenHeight, int nScreenWidth);

	
private:
	Mesh mMesh;
	float mfTheta;
	float mnScreenOffset;
	
	Vector3D mvCamera;



};

CHAR_INFO GetColour(float lum)
{
	short bg_col, fg_col;
	wchar_t sym;
	int pixel_bw = static_cast<int>(13.0f * lum);
	switch (pixel_bw)
	{
	case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

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
		bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
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
{

}

bool TaeDdangGraphicEngine::initiateFromFile(const char* fileName)
{
	std::fstream fileHandle(fileName);
	if (!fileHandle.is_open())
	{
		return false;
	}
	char line[100];
	std::vector<Vector3D> vVertex{};
	vVertex.reserve(4000);
	mMesh.triangles.reserve(8000);

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
	if (mMesh.triangles.size() > 4000)
	{
		mnScreenOffset = 5.5f;
	}
	else
	{
		mnScreenOffset = 8.5f;
	}
	return true;
}

void TaeDdangGraphicEngine::initiateWithAssignment()
{
	const float fCubeSize = 1.0f;
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

}

Matrix3D TaeDdangGraphicEngine::GetRotateMatrixX(const float theta)
{
	Matrix3D result;
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cosf(theta);
	result.m[1][2] = -std::sinf(theta);
	result.m[2][1] = std::sinf(theta);
	result.m[2][2] = std::cosf(theta);

	return result;
}

Matrix3D TaeDdangGraphicEngine::GetRotateMatrixY(const float theta)
{
	Matrix3D result;
	result.m[0][0] = std::cosf(theta);
	result.m[0][2] = -std::sinf(theta);
	result.m[2][0] = std::sinf(theta);
	result.m[2][2] = std::cosf(theta);
	result.m[1][1] = 1.0f;

	return result;
}

Matrix3D TaeDdangGraphicEngine::GetRotateMatrixZ(const float theta)
{
	Matrix3D result;
	result.m[0][0] = std::cosf(theta);
	result.m[0][1] = -std::sinf(theta);
	result.m[1][0] = std::sinf(theta);
	result.m[1][1] = std::cosf(theta);
	result.m[2][2] = 1.0f;

	return result;
}


Matrix3D TaeDdangGraphicEngine::GetPointAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up)
{
	// Calculate new forward direction
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

	Matrix3D pointAtMatrix;
	pointAtMatrix.m[0][0] = newRight.mfX;
	pointAtMatrix.m[0][1] = newRight.mfY;
	pointAtMatrix.m[0][2] = newRight.mfZ;

	pointAtMatrix.m[1][0] = newUp.mfX;
	pointAtMatrix.m[1][1] = newUp.mfY;
	pointAtMatrix.m[1][2] = newUp.mfZ;

	pointAtMatrix.m[2][0] = newForward.mfX;
	pointAtMatrix.m[2][1] = newForward.mfY;
	pointAtMatrix.m[2][2] = newForward.mfZ;

	return pointAtMatrix;

}

//Matrix3D GetInverseMatrix(const Matrix3D& mat)
//{
//	float det = mat.m[0][0] * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m00 * m12 * m21 - m01 * m10 * m22 - m02 * m11 * m20;
//	m00 = (m11 * m22 - m12 * m21) / det;
//	m01 = (m02 * m21 - m01 * m22) / det;
//	m02 = (m01 * m12 - m02 * m11) / det;
//	m10 = (m12 * m20 - m10 * m22) / det;
//	m11 = (m00 * m22 - m02 * m20) / det;
//	m12 = (m02 * m10 - m00 * m12) / det;
//	m20 = (m10 * m21 - m11 * m20) / det;
//	m21 = (m01 * m20 - m00 * m21) / det;
//	m22 = (m00 * m11 - m01 * m10) / det;
//}

Matrix3D TaeDdangGraphicEngine::MultiplyMatrix3D(const Matrix3D& op1, const Matrix3D& op2) const
{
	Matrix3D result;
	for (size_t r = 0; r < 3; r++)
	{
		for (size_t c = 0; c < 3; c++)
		{
			float element = 0.0f;
			element += op1.m[r][0] * op2.m[0][c];
			element += op1.m[r][1] * op2.m[1][c];
			element += op1.m[r][2] * op2.m[2][c];

			result.m[r][c] = element;
		}
	}
	return result;
}

Matrix4D TaeDdangGraphicEngine::GetProjectionMatrix(float fNear, float fFar,float fFOV, int nScreenHeight, int nScreenWidth)
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

Triangle TaeDdangGraphicEngine::TranslateTriangle(const Triangle& tri, const Matrix3D& mat) const
{
	Triangle result;
	result.Point[0] = tri.Point[0].MultiplyMatrix(mat);
	result.Point[1] = tri.Point[1].MultiplyMatrix(mat);
	result.Point[2] = tri.Point[2].MultiplyMatrix(mat);

	return result;
}


Triangle TaeDdangGraphicEngine::ProjectTriangle(const Triangle& tri, const Matrix4D& matrix) const
{
	Triangle result;
	result.Point[0] = tri.Point[0].MakeProjection(matrix);
	result.Point[1] = tri.Point[1].MakeProjection(matrix);
	result.Point[2] = tri.Point[2].MakeProjection(matrix);

	return result;
}

bool TaeDdangGraphicEngine::OnUserCreate()
{
	//initiateWithAssignment();
	//mvCamera.mfZ = 0.0f;
	initiateFromFile("VideoShip.obj");
	//initiateFromFile("teapot.obj");


	return true;
}

bool TaeDdangGraphicEngine::OnUserUpdate(float fElapsedTime)
{

	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
	mfTheta += 1.3f * fElapsedTime;

	//Matrix3D rotateX = GetRotateMatrixX(mfTheta);
	//Matrix3D rotateMinusX = GetRotateMatrixX(mfTheta * -1.0f);
	//Matrix3D rotateMinusY = GetRotateMatrixY(mfTheta * -1.0f);
	//Matrix3D rotateMinusZ = GetRotateMatrixZ(mfTheta * -1.0f);
	//Matrix3D rotateYZ = MultiplyMatrix3D(rotateMinusZ, rotateMinusY);
	Matrix3D rotateY = GetRotateMatrixY(mfTheta);
	//Matrix3D rotateZ = GetRotateMatrixZ(mfTheta);

	//Matrix3D rotateZ = GetRotateMatrixZ(mfTheta);
	/*Matrix3D rotateY = GetRotateMatrixY(mfTheta);
	Matrix3D rotateZX = MultiplyMatrix3D(rotateX, rotateZ);
	Matrix3D rotateXZ = MultiplyMatrix3D(rotateZ, rotateX);
	Matrix3D rotateYX = MultiplyMatrix3D(rotateX, rotateY);
	Matrix3D rotateZXY = MultiplyMatrix3D(rotateY, rotateZX);
	Matrix3D rotateXY = MultiplyMatrix3D(rotateY, rotateX);
	Matrix3D rotateYZ = MultiplyMatrix3D(rotateZ, rotateY);
	Matrix3D rotateZY = MultiplyMatrix3D(rotateY, rotateZ);*/

	//Matrix3D stayStill = MultiplyMatrix3D(rotateX, rotateMinusX);


	//std::vector<Triangle> vTrianglesToRasterize{};
	//auto ZCompare = CompareZElement{};
	std::map<float, Triangle, CompareZElement> mapTrianlgesToRasterize{};
	//std::vector<Triangle> vTrianglesToRasterize;
	//vTrianglesToRasterize.reserve(mMesh.triangles.size());

	for (const auto& originalTriangle : mMesh.triangles)
	{
		Triangle translatedTriangle = TranslateTriangle(originalTriangle, rotateY);

		translatedTriangle.Point[0].mfZ += mnScreenOffset;
		translatedTriangle.Point[1].mfZ += mnScreenOffset;
		translatedTriangle.Point[2].mfZ += mnScreenOffset;


		Vector3D firstVectorOnPlane = translatedTriangle.Point[1] - translatedTriangle.Point[0];
		Vector3D secondVectorOnPlane = translatedTriangle.Point[2] - translatedTriangle.Point[1];
		Vector3D normalVector = firstVectorOnPlane.GetCrossProduct(secondVectorOnPlane);
		float normalVectorSize = normalVector.GetSize();
		if (normalVectorSize == 0.0f)
		{
			continue;
		}
		normalVector.Normalize();


		Vector3D rayFromCameraAtPlane = translatedTriangle.Point[0] - mvCamera;

		float rayAndNormalDotProduct = rayFromCameraAtPlane.GetDotProduct(normalVector);

		if (rayAndNormalDotProduct < 0.0f)
		{
			Vector3D lightDirection{ 0.0f, 0.0f, -1.0f };

			float lightAndNormalDotProduct = lightDirection.GetDotProduct(normalVector);
			CHAR_INFO color = GetColour(lightAndNormalDotProduct);
			translatedTriangle.color = color.Attributes;
			translatedTriangle.symbol = color.Char.UnicodeChar;

			float fCentroid = 0.0f;
			fCentroid += translatedTriangle.Point[0].mfZ;
			fCentroid += translatedTriangle.Point[1].mfZ;
			fCentroid += translatedTriangle.Point[2].mfZ;
			//fCentroid /= 3.0f;
			//vTrianglesToRasterize.push_back(translatedTriangle);
			mapTrianlgesToRasterize.emplace(fCentroid, translatedTriangle);

		}
	}


	/*auto sortByZElement = [](const Triangle& tri1, const Triangle& tri2)
	{
		float Zcentroid1 = 0.0f;
		Zcentroid1 += tri1.Point[0].mfZ;
		Zcentroid1 += tri1.Point[1].mfZ;
		Zcentroid1 += tri1.Point[2].mfZ;
		float Zcentroid2 = 0.0f;
		Zcentroid2 += tri2.Point[0].mfZ;
		Zcentroid2 += tri2.Point[1].mfZ;
		Zcentroid2 += tri2.Point[2].mfZ;

		return Zcentroid1 > Zcentroid2;
	};*/
	//std::sort(std::begin(vTrianglesToRasterize), std::end(vTrianglesToRasterize), sortByZElement);

	/*for (const auto& triangleToDraw : vTrianglesToRasterize)
	{
		Matrix4D projectMatrix = GetProjectionMatrix(0.1f, 1000.0f, 3.14159f / 2.0f, ScreenHeight(), ScreenWidth());
		Triangle projectedTriangle = ProjectTriangle(triangleToDraw, projectMatrix);
		projectedTriangle.symbol = triangleToDraw.symbol;
		projectedTriangle.color = triangleToDraw.color;
		projectedTriangle.Point[0].mfX += 1.0f;
		projectedTriangle.Point[0].mfY += 1.0f;

		projectedTriangle.Point[1].mfX += 1.0f;
		projectedTriangle.Point[1].mfY += 1.0f;

		projectedTriangle.Point[2].mfX += 1.0f;
		projectedTriangle.Point[2].mfY += 1.0f;

		const float fhalfScreenHeight = static_cast<float>(ScreenHeight() * 0.5f);
		const float fhalfScreenWidth = static_cast<float>(ScreenWidth() * 0.5f);

		int x1 = static_cast<int>(projectedTriangle.Point[0].mfX * fhalfScreenWidth);
		int y1 = static_cast<int>(projectedTriangle.Point[0].mfY * fhalfScreenHeight);

		int x2 = static_cast<int>(projectedTriangle.Point[1].mfX * fhalfScreenWidth);
		int y2 = static_cast<int>(projectedTriangle.Point[1].mfY * fhalfScreenHeight);

		int x3 = static_cast<int>(projectedTriangle.Point[2].mfX * fhalfScreenWidth);
		int y3 = static_cast<int>(projectedTriangle.Point[2].mfY * fhalfScreenHeight);

		FillTriangle(x1, y1,
			x2, y2,
			x3, y3,
			projectedTriangle.symbol, projectedTriangle.color);

	}*/
	for (const auto& iter : mapTrianlgesToRasterize) 
	{
		Triangle triangleToDraw = iter.second;
		Matrix4D projectMatrix = GetProjectionMatrix(0.1f, 1000.0f, 3.14159f / 2.0f, ScreenHeight(), ScreenWidth());
		Triangle projectedTriangle = ProjectTriangle(triangleToDraw, projectMatrix);

		projectedTriangle.symbol = triangleToDraw.symbol;
		projectedTriangle.color = triangleToDraw.color;

		projectedTriangle.Point[0].mfX += 1.0f;
		projectedTriangle.Point[0].mfY += 1.0f;

		projectedTriangle.Point[1].mfX += 1.0f;
		projectedTriangle.Point[1].mfY += 1.0f;

		projectedTriangle.Point[2].mfX += 1.0f;
		projectedTriangle.Point[2].mfY += 1.0f;

		const float fhalfScreenHeight = static_cast<float>(ScreenHeight() * 0.5f);
		const float fhalfScreenWidth = static_cast<float>(ScreenWidth() * 0.5f);

		int x1 = static_cast<int>(projectedTriangle.Point[0].mfX * fhalfScreenWidth);
		int y1 = static_cast<int>(projectedTriangle.Point[0].mfY * fhalfScreenHeight);

		int x2 = static_cast<int>(projectedTriangle.Point[1].mfX * fhalfScreenWidth);
		int y2 = static_cast<int>(projectedTriangle.Point[1].mfY * fhalfScreenHeight);

		int x3 = static_cast<int>(projectedTriangle.Point[2].mfX * fhalfScreenWidth);
		int y3 = static_cast<int>(projectedTriangle.Point[2].mfY * fhalfScreenHeight);

		FillTriangle(x1, y1,
			x2, y2,
			x3, y3,
			projectedTriangle.symbol, projectedTriangle.color);

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