#include "stdafx.h"
#include "DataBase.h"
//数据基础类 可在后面建立基数结构类 继承与此类
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
