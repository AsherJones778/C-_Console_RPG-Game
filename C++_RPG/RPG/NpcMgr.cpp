#include "stdafx.h"
#include "NpcMgr.h"
#include "DataMgr.h"
CNpcMgr::CNpcMgr()
{
}
CNpcMgr::~CNpcMgr()
{
	for (CNpc* pData : m_vecNpcs)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecNpcs.clear();
}
void CNpcMgr::createNpc()
{
	vector<SBaseDt*> vecNpcDts = CDataMgr::getInstance()->getMgr("NpcDtMgr")->getAllDatas();
	for (SBaseDt* pNpcDt : vecNpcDts)
	{
		SNpcDt* p = static_cast<SNpcDt*>(pNpcDt);
		CNpc* pNpc = new CNpc(p);
		vector<SBaseDt*> vecAllMissions = CDataMgr::getInstance()->getMgr("MissionDtMgr")->getAllDatas();
		for (SBaseDt* pAllMissions : vecAllMissions)
		{
			SMissionDt* pMission = static_cast<SMissionDt*>(pAllMissions);

			if (pMission->nNpcID == pNpc->getID())
			{
				pNpc->addMission(pMission);
			}
		}
		m_vecNpcs.push_back(pNpc);
	}
}
CNpc* CNpcMgr::isExist(int nRow, int nCol, int nMapID)
{
	for (CNpc* pNpc : m_vecNpcs)
	{
		if (pNpc->isExist(nRow,nCol,nMapID))
		{
			return pNpc;
		}
	}
	return nullptr;
}
CNpc* CNpcMgr::getNpcByID(int nID)
{
	for (CNpc* pData : m_vecNpcs)
	{
		if (pData->getID() == nID)
		{
			return pData;
		}
	}
	return nullptr;
}