#include "stdafx.h"
#include "Npc.h"
CNpc::CNpc()
{
}
CNpc::CNpc(SNpcDt* pData)
{
	m_nID = pData->nID;
	m_strName = pData->strName;
	m_strPic = pData->strPic;
	m_nRow = pData->nRow;
	m_nCol = pData->nCol;
	m_nMapID = pData->nMapID;
	m_nDeal = pData->nDeal;
}
CNpc::~CNpc()
{
	for (SMissionDt* pData : m_vecMission)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecMission.clear();
}
bool CNpc::isExist(int nRow, int nCol, int nMapID)
{
	if (nRow == m_nRow && nCol == m_nCol && nMapID == m_nMapID)
	{
		return true;
	}
	return false;
}
void CNpc::addMission(SMissionDt* pData)
{
	m_vecMission.push_back(pData);
}