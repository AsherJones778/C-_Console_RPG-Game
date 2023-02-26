#pragma once
#include <map>
#include <string>
#include "DataBase.h"
using namespace std;
class CDataMgr
{
public:
	~CDataMgr();
	static CDataMgr* getInstance();
	void addMgr(string strName,CBaseDtMgr* pMgr);
	CBaseDtMgr* getMgr(string strName);
private:
	CDataMgr();
	static CDataMgr* m_psInstance;
	map<string, CBaseDtMgr*> m_mapMgrs;
};
