#include "stdafx.h"
#include "GameMap.h"
#include "DataMgr.h"
#include "GameMgr.h"
#include "Pet.h"
CGameMap::CGameMap()
{
	m_pPlayer = new CPlayer();
	m_pNpcMgr = new CNpcMgr();
	m_pNpcMgr->createNpc();
	m_pEnemyMgr = new CEnemyMgr();
	m_pEnemyMgr->createEnemy();
}
CGameMap::~CGameMap()
{
	CC_SAFE_DELETE(m_pCurMapDt);
	CC_SAFE_DELETE(m_pPlayer);
	CC_SAFE_DELETE(m_pNpcMgr);
	CC_SAFE_DELETE(m_pEnemyMgr);
}
void CGameMap::update()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
	}
	m_pPlayer->update();
}
void CGameMap::render()
{
	cout << "当前位置：" << m_pCurMapDt->strName << endl;
	for (int i = 0; i < m_pCurMapDt->nRowCount; i++)
	{
		for (int j = 0; j < m_pCurMapDt->nColCount; j++)
		{
			CNpc* pNpc = m_pNpcMgr->isExist(i, j, m_pCurMapDt->nID);
			CEnemy* pEnemy = m_pEnemyMgr->isExist(i, j, m_pCurMapDt->nID);
			CPet* pPet = m_pPlayer->getPet();
			if (1 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "■";
			}
			else if (m_pCurMapDt->arrMap[i][j] > 1000)
			{
				cout << "传";
			}
			else if (m_pPlayer->isExist(i, j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (pPet && pPet->isExist(i,j))
			{
				cout << pPet->getPic();
			}
			else if (pNpc)
			{
				cout << pNpc->getPic();
			}
			else if (pEnemy)
			{
				cout << pEnemy->getPic();
			}
			else if (9 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "门";
			}
			else if (0 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
}