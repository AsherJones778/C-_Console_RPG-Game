#include "stdafx.h"
#include "EnemyMgr.h"
#include "DataMgr.h"
CEnemyMgr::CEnemyMgr()
{
}
CEnemyMgr::~CEnemyMgr()
{
	for (CEnemy* pData : m_vecEnemys)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecEnemys.clear();
}
void CEnemyMgr::createEnemy()
{
	vector<SBaseDt*> vecEnemyDts = CDataMgr::getInstance()->getMgr("EnemyDtMgr")->getAllDatas();
	for (SBaseDt* pData : vecEnemyDts)
	{
		SEnemyDt* pEnemyDt = static_cast<SEnemyDt*>(pData);
		CEnemy* pEnemy = new CEnemy(pEnemyDt);
		m_vecEnemys.push_back(pEnemy);
	}
}
CEnemy* CEnemyMgr::isExist(int nRow, int nCol, int nMapID)
{
	for (CEnemy* pEnemy : m_vecEnemys)
	{
		if (pEnemy->isExist(nRow,nCol,nMapID))
		{
			return pEnemy;
		}
	}
	return nullptr;
}
