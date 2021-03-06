
#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>
#include <cassert>	

const int nScreenWidth = 120;
//int nScreenHeight = 40;
const int nAbstractMapHeight = 20;
const int nViewHeight = 40;
const int nScreenHeight = nViewHeight + nAbstractMapHeight;
const float fPi = 3.14159f;

float fPlayerPosX = 4.0f;
float fPlayerPosY = 10.0f;
float fPlayerAngle = fPi / 2.0f;
float fMoveIncrement = 0.009f;
float fAngleIncrement = 0.001f;
float fAngleInDegree = std::roundf(fPlayerAngle * 180.0f / fPi);
int nPlayerAngleInDegree = static_cast<int>(std::round(fAngleInDegree));

const int nMapHeight = 16;
const int nMapWidth = 16;

const int nAngleMapSize = 6;
const int nAngleMapScreenPosX = 70;
const int nAngleMapScreenPosY = 8;

const float fFieldOfView = fPi / 4.0f;
const int nFieldOfView = static_cast<int>(std::roundf(fFieldOfView * 180.0f / fPi));
const float fDepth = 16.0f;

//void DrawAngle(const float& fAngle);

int main()
{
	wchar_t* screen = new wchar_t[nScreenHeight * nScreenWidth];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	std::wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#.....####.....#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	
	assert(nFieldOfView % 45 == 0);

	if (fPlayerPosX < 1.0f)
	{
		fPlayerPosX = 1.0f;
	}
	if (fPlayerPosX > 14.0f)
	{
		fPlayerPosX = 14.0f;
	}
	if (fPlayerPosY < 1.0f)
	{
		fPlayerPosY = 1.0f;
	}
	if (fPlayerPosY > 14.0f)
	{
		fPlayerPosY = 14.0f;
	}
	if (fPlayerAngle < 0)
	{
		fPlayerAngle += 2 * fPi;
	}
	while (1)
	{
		int nPlayerPosX = static_cast<int>(std::roundf(fPlayerPosX));
		int nPlayerPosY = static_cast<int>(std::roundf(fPlayerPosY));
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		{
			if (map[nPlayerPosY * nMapWidth + nPlayerPosX - 1] != '#')
			{
				fPlayerPosX -= fMoveIncrement;
			}
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		{
			if (map[nPlayerPosY * nMapWidth + nPlayerPosX + 1] != '#')
			{
				fPlayerPosX += fMoveIncrement;
			}
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			if (map[(nPlayerPosY - 1) * nMapWidth + nPlayerPosX] != '#')
			{
				fPlayerPosY -= fMoveIncrement;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			if (map[(nPlayerPosY + 1) * nMapWidth + nPlayerPosX] != '#')
			{
				fPlayerPosY += fMoveIncrement;
			}
		}
		if (GetAsyncKeyState((unsigned short)'J') & 0x8000)
		{
			fPlayerAngle += fAngleIncrement;
		}
		if (GetAsyncKeyState((unsigned short)'L') & 0x8000)
		{
			fPlayerAngle -= fAngleIncrement;
		}
		for (int x = 0; x < nScreenWidth; x++)
		{
			float fRayAngle = (fPlayerAngle + fFieldOfView / 2.0f) - ((float)x / (float)nScreenWidth) * fFieldOfView;
			float fDistanceToWall = 0.0f;
			bool bHitWall = false;
			float fUnitX = cosf(fRayAngle);
			float fUnitY = sinf(fRayAngle);
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += 0.1f;
				int nTestX = static_cast<int>(std::roundf(fPlayerPosX + fUnitX * fDistanceToWall));
				int nTestY = static_cast<int>(std::roundf(fPlayerPosY - fUnitY * fDistanceToWall));
				if (nTestX <= 0 || nTestX >= nMapWidth || nTestY <= 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;
					//fDistanceToWall = fDepth;
				}
				else
				{
					if (map[nTestY * nMapWidth + nTestX] == '#')
					{
						bHitWall = true;
						//fDistanceToWall = fDepth;
					}
				}
			}
			int nCeiling = (int)((float)(nViewHeight) / 2.0f - (float)(nViewHeight) / (fDistanceToWall));
			int nFloor = nViewHeight - nCeiling;
		/*	std::cout << nCeiling << std::endl;
			std::cout << fDistanceToWall << std::endl;*/
			/*assert(nCeiling >= 0);
			assert(nFloor <= nScreenHeight);*/
			nCeiling += nAbstractMapHeight;
			nFloor += nAbstractMapHeight;
			for (int y = 0; y < nScreenHeight; y++)
			{
				int nPlayerPosX = static_cast<int>(std::roundf(fPlayerPosX));
				int nPlayerPosY = static_cast<int>(std::roundf(fPlayerPosY));
				if (y < nAbstractMapHeight)
				{
					if (y < nMapHeight)
					{
						if (x < nMapWidth)
						{
							if (nPlayerPosX == x && nPlayerPosY == y)
							{
								screen[y * nScreenWidth + nPlayerPosX] = 'x';
							}
							else
							{
								screen[y * nScreenWidth + x] = map[y * nMapWidth + x];
							}

						}
						else
						{
							if (x <= nAngleMapScreenPosX + nAngleMapSize / 2 && x >= nAngleMapScreenPosX - nAngleMapSize / 2 && y <= nAngleMapScreenPosY + nAngleMapSize / 2 && y >= nAngleMapScreenPosY - nAngleMapSize / 2)
							{
								
								screen[y * nScreenWidth + x] = '*';
							}
							else
							{
								screen[y * nScreenWidth + x] = ' ';
							}
						}
					}
					else
					{
						screen[y * nScreenWidth + x] = ' ';
					}


				}
				else if (y >= nAbstractMapHeight && y < nCeiling)
				{
					screen[y * nScreenWidth + x] = ' ';
				}
				else if (y >= nCeiling && y < nFloor)
				{
					screen[y * nScreenWidth + x] = '0';
				}
				else //if (y > nFloor)
				{
					screen[y * nScreenWidth + x] = ' ';
				}
			}

		}
		std::wstring playerPosInfo = L"X : ";
		playerPosInfo += std::to_wstring(fPlayerPosX);
		playerPosInfo += L", Y : ";
		playerPosInfo += std::to_wstring(fPlayerPosY);
		playerPosInfo += L", Angle : ";
		fAngleInDegree = std::roundf(fPlayerAngle * 180.0f / fPi);
		nPlayerAngleInDegree = static_cast<int>(fAngleInDegree);
		if (nPlayerAngleInDegree < 0)
		{
			nPlayerAngleInDegree = 360 + nPlayerAngleInDegree;
		}
		nPlayerAngleInDegree = nPlayerAngleInDegree % 360;
		playerPosInfo += std::to_wstring(nPlayerAngleInDegree);
		playerPosInfo += L" deg";

		for (size_t i = 0; i < playerPosInfo.size(); i++)
		{
			size_t positionInfo = nMapWidth + 5;
			screen[positionInfo + i] = playerPosInfo[i];
		}
		screen[nScreenHeight * nScreenWidth - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}

