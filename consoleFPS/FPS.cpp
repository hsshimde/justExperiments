
#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>

int nScreenWidth = 120;
//int nScreenHeight = 40;
int nAbstractMapHeight = 20;
int nViewHeight = 40;
int nScreenHeight = nViewHeight + nAbstractMapHeight;

float fPlayerPosX = 8.0f;
float fPlayerPosY = 8.0f;
float fPlayerAngle = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFieldOfView = 3.14159f / 12.0f;
float fDepth = 16.0f;


int main()
{
	wchar_t* screen = new wchar_t[nScreenHeight * nScreenWidth];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	std::wstring map;
	map += L"################";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"#............. #";
	map += L"################";

	while (1)
	{
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		{
			if (fPlayerPosX > 1.0f)
			{
				fPlayerPosX -= 0.02f;
			}
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		{
			if (fPlayerPosX < 14.0f)
			{
				fPlayerPosX += 0.02f;
			}
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			if (fPlayerPosY > 1.0f)
			{
				fPlayerPosY -= 0.02f;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			if (fPlayerPosY < 14.0f)
			{
				fPlayerPosY += 0.02f;
			}
		}

		for (int x = 0; x < nScreenWidth; x++)
		{
			float fRayAngle = (fPlayerAngle - fFieldOfView / 2.0f) + ((float)x / (float)nScreenWidth) * fFieldOfView;
			float fDistanceToWall = 0.0f;
			bool bHitWall = false;
			float fEyeX = sinf(fRayAngle);
			float fEyeY = -cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += 0.1f;
				int nTestX = (int)(fPlayerPosX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerPosY + fEyeY * fDistanceToWall);
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;
					fDistanceToWall = fDepth;
				}
				else
				{
					if (map[nTestY * nMapWidth + nTestX] == '#')
					{
						bHitWall = true;
					}
				}
			}
			int nCeiling = (int)((float)(nViewHeight) / 2.0f - (float)(nViewHeight) / fDistanceToWall);
			//nCeiling += nAbstractMapHeight;
			int nFloor = nViewHeight - nCeiling;
			nCeiling += nAbstractMapHeight;
			nFloor += nAbstractMapHeight;


			for (int y = 0; y < nScreenHeight; y++)
			{
				int nPlayerPosX = static_cast<int>(std::roundf((fPlayerPosX)));
				int nPlayerPosY = static_cast<int>(std::roundf((fPlayerPosY)));
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
							screen[y * nScreenWidth + x] = ' ';
						}
					}
					else
					{
						screen[y * nScreenWidth + x] = ' ';
					}
				}
				else if (y > nAbstractMapHeight && y < nCeiling)
				{
					screen[y * nScreenWidth + x] = ' ';
				}
				else if (y > nCeiling && y < nFloor)
				{
					screen[y * nScreenWidth + x] = '0';
				}
				else //if (y > nFloor)
				{
					screen[y * nScreenWidth + x] = ' ';
				}
			}

		}
		std::wstring characterPosInfo = L"X : ";
		characterPosInfo += std::to_wstring(fPlayerPosX);
		characterPosInfo += L", Y : ";
		characterPosInfo += std::to_wstring(fPlayerPosY);

		for (int i = 0; i < (int)characterPosInfo.size(); ++i)
		{
			if (i+20 < std::wcslen(screen))
			{
				screen[i + 20] = characterPosInfo[i];
			}
		}
		screen[nScreenHeight * nScreenWidth - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}