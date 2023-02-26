#include "stdafx.h"
#include "DataMgr.h"
CDataMgr* CDataMgr::m_psInstance = nullptr;
CDataMgr::CDataMgr()
{
}
CDataMgr::~CDataMgr()
{
	map<string, CBaseDtMgr*>::iterator iter = m_mapMgrs.begin();
	for (; iter != m_mapMgrs.end(); iter++)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	m_mapMgrs.clear();
	CC_SAFE_DELETE(m_psInstance);
}
CDataMgr* CDataMgr::getInstance()
{
	if (!m_psInstance)
	{
		m_psInstance = new CDataMgr();
	}
	return m_psInstance;
}
CBaseDtMgr* CDataMgr::getMgr(string strName)//��map���ҵ���Ҫ���ҵĹ����߲����س�ȥ
{
	return m_mapMgrs.at(strName);
}
void CDataMgr::addMgr(string strName, CBaseDtMgr* pMgr)//������ݹ�����
{
	if (strName.empty() || !pMgr)
	{
		return;
	}
	m_mapMgrs.insert(pair<string, CBaseDtMgr*>(strName, pMgr));
}