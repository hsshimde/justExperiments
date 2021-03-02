#pragma once

#include <queue>
#include <vector>

#include "C:\hsShim\videos-master\videos-master\olcConsoleGameEngine.h"
#include "Bullet.h"
#include "Enemy.h"

namespace game
{
	class Game : public olcConsoleGameEngine
	{
	public:

		~Game()
		{

		}
		bool OnUserCreate()
		{
			mSpaceShipX = 10.0f;
			mSpaceShipY = (float)m_nScreenHeight / 2;
			return true;
		}

		bool OnUserDestroy()
		{
			for (auto& i : mActivatedBullets)
			{
				delete i;
			}
			for (size_t i = 0; i < mBulletPool.size(); i++)
			{
				delete mBulletPool.front();
				mBulletPool.pop();
			}
			for (auto& i : mEnemies)
			{
				delete i;
			}
			for (size_t i = 0; i < mEnemyPool.size(); i++)
			{
				delete mEnemyPool.front();
				mEnemyPool.pop();
			}

			return true;

		}

		bool OnUserUpdate(float fElapsedTime)
		{

			Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

			double probForEnemy = (double)(rand() % 100);
			if (probForEnemy < ENEMY_PROBABILITY)
			{
				if (mEnemies.size() < MAX_ENEMY_COUNT)
				{
					Enemy* newEnemy;
					if (!mEnemyPool.empty())
					{
						newEnemy = mEnemyPool.front();
						mEnemyPool.pop();
						newEnemy->mX = (float)(m_nScreenWidth - 3);
						newEnemy->mY = (float)(rand() % m_nScreenHeight);
						newEnemy->mbHit = false;
					}
					else
					{
						newEnemy = new Enemy((float)(m_nScreenWidth - 3), float(rand() % m_nScreenHeight));
					}
					mEnemies.push_back(newEnemy);
				}
			}
			for (auto& en : mEnemies)
			{
				if (en->mY < 2)
				{
					en->meMove = eMoveDirection::DOWN;
				}
				else if (en->mY > m_nScreenHeight - 2)
				{
					en->meMove = eMoveDirection::UP;
				}
				if (en->meMove == eMoveDirection::UP)
				{
					en->mY -= fElapsedTime * 4.0f;
				}
				else
				{
					en->mY += fElapsedTime * 4.0f;
				}
				en->mX -= fElapsedTime * 3.0f;

				
			}
			for (auto it = mActivatedBullets.begin(); it != mActivatedBullets.end();)
			{
				(*it)->mX += fElapsedTime * 32.0f;
				if ((*it)->mX >= m_nScreenWidth)
				{
					mBulletPool.push(*it);
					it = mActivatedBullets.erase(it);
					continue;
				}
				++it;
			}
			ProcessEnemiesAndBullet();
			DrawEnemies();
			DrawBullets();

			if (m_keys[VK_LEFT].bHeld && mSpaceShipX > 2)
			{
				mSpaceShipX -= fElapsedTime * 18.0f;
			}
			if (m_keys[VK_RIGHT].bHeld && mSpaceShipX < m_nScreenWidth - 2)
			{
				mSpaceShipX += fElapsedTime * 18.0f;
			}
			if (m_keys[VK_UP].bHeld && mSpaceShipY > 1)
			{
				mSpaceShipY -= fElapsedTime * 18.0f;
			}
			if (m_keys[VK_DOWN].bHeld && mSpaceShipY < m_nScreenHeight - 2)
			{
				mSpaceShipY += fElapsedTime * 18.0f;
			}
			if (m_keys[VK_SPACE].bPressed)
			{
				if (mActivatedBullets.size() < MAX_BULLET_COUNT)
				{
					Bullet* newlyGeneratedBullet;

					if (!mBulletPool.empty())
					{
						newlyGeneratedBullet = mBulletPool.front();
						mBulletPool.pop();
						newlyGeneratedBullet->mX = mSpaceShipX + 1;
						newlyGeneratedBullet->mY = mSpaceShipY;
						newlyGeneratedBullet->mbHitEnemy = false;
					}
					else
					{
						newlyGeneratedBullet = new Bullet((mSpaceShipX)+1, mSpaceShipY);
					}
					mActivatedBullets.push_back(newlyGeneratedBullet);
				}

			}

			//#define VK_SPACE          0x20
			//#define VK_PRIOR          0x21
			//#define VK_NEXT           0x22
			//#define VK_END            0x23
			//#define VK_HOME           0x24
			//#define VK_LEFT           0x25
			//#define VK_UP             0x26
			//#define VK_RIGHT          0x27
			//#define VK_DOWN           0x28
			//#define VK_SELECT         0x29
			//#define VK_PRINT          0x2A
			//#define VK_EXECUTE        0x2B
			//#define VK_SNAPSHOT       0x2C
			//#define VK_INSERT         0x2D
			//#define VK_DELETE         0x2E
			//#define VK_HELP           0x2F

			DrawBullets();

			DrawSpeaceShip();

			if (m_keys[VK_ESCAPE].bHeld)
			{
				Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);
				return false;
			}
			
			return true;
		}

		void DrawSpeaceShip()
		{
			DrawCircle((int)mSpaceShipX, (int)mSpaceShipY, 2);
		}

		void DrawBullets()
		{
			for (auto& bullet : mActivatedBullets)
			{
				if (!bullet->mbHitEnemy)
				{
					DrawLine((int)bullet->mX, (int)bullet->mY, (int)bullet->mX + 2, (int)bullet->mY);
				}
			}

		}

		void DrawEnemies()
		{
			for (const auto& enemy : mEnemies)
			{
				int x = (int)(enemy->mX);
				int y = (int)(enemy->mY);
				if (!enemy->mbHit)
				{
					DrawTriangle(x - 2, y - 3, x - 2, y + 3, x + 1, y);
					DrawLine(x - 5, y - 1, x - 2, y - 2);
					DrawLine(x - 5, y + 1, x - 2, y + 2);
				}
				else
				{
					DrawLine(x - 2, y - 2, x + 2, y + 2);
					DrawLine(x + 2, y - 2, x - 2, y + 2);
				}
			}


		}

		void ProcessEnemiesAndBullet()
		{
			for (auto bulletIt = mActivatedBullets.begin(); bulletIt != mActivatedBullets.end();)
			{
				if (!(*bulletIt)->mbHitEnemy)
				{
					for (auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end();)
					{
						

						if (!(*enemyIt)->mbHit)
						{
							float fBulletPosX = (*bulletIt)->mX;
							float fBulletPosY = (*bulletIt)->mY;
							float fEnemyPosX = (*enemyIt)->mX;
							float fEnemyPosY = (*enemyIt)->mY;
							float fDistanceX = fBulletPosX - fEnemyPosX;
							float fDistanceY = fBulletPosY - fEnemyPosY;
							float distanceToBullet = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY);

							if (distanceToBullet < 4.0f)
							{
								(*bulletIt)->mbHitEnemy = true;
								(*bulletIt)->mHitTick = GetTickCount64();
								(*enemyIt)->mbHit = true;
								(*enemyIt)->mHitTick = GetTickCount64();
							}
						}
						else
						{
							if (GetTickCount64() - (*enemyIt)->mHitTick >= 800||(*enemyIt)->mX<1)
							{
								mEnemyPool.push(*enemyIt);
								enemyIt = mEnemies.erase(enemyIt);
								continue;
							}
						}
						enemyIt++;
					}


				}
				else
				{
					if (GetTickCount64() - (*bulletIt)->mHitTick >= 3000)
					{
						mBulletPool.push(*bulletIt);
						bulletIt = mActivatedBullets.erase(bulletIt);
						continue;
					}

				}
				bulletIt++;
			}
		}

	private:
		float mSpaceShipX;
		float mSpaceShipY;
		const size_t MAX_BULLET_COUNT = 10000;
		const size_t MAX_ENEMY_COUNT = 10000;
		const double ENEMY_PROBABILITY = 99.0;

		std::vector<Bullet*> mActivatedBullets;
		std::queue<Bullet*> mBulletPool;

		std::vector<Enemy*> mEnemies;
		std::queue<Enemy*> mEnemyPool;

	};

}