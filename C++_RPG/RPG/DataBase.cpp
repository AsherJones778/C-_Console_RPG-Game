#include "stdafx.h"
#include "DataBase.h"
//���ݻ����� ���ں��潨�������ṹ�� �̳������
CBaseDtMgr::CBaseDtMgr()
{
}
CBaseDtMgr::~CBaseDtMgr()
{
	for (SBaseDt* pData : m_vecDatas)
	{
		if (pData)
		{
			delete pData;
			pData = nullptr;
		}
	}
	m_vecDatas.clear();
}
SBaseDt* CBaseDtMgr::getDataByID(int nID)
{
	for (SBaseDt* pData : m_vecDatas)
	{
		if (pData->nID == nID)
		{
			return pData;
		}
	}
	return nullptr;
}
vector<SBaseDt*> CBaseDtMgr::getAllDatas()
{
	return m_vecDatas;
}
int CBaseDtMgr::getDataSize()
{
	return m_vecDatas.size();
}
