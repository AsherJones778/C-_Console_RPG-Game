#pragma once
#include <string>
#include <vector>
using namespace std;
struct SBaseDt
{
	SBaseDt()
	{
		nID = 0;
		strName = "";
	}
	virtual ~SBaseDt(){}
	int nID;
	string strName;
};
class CBaseDtMgr
{
public:
	CBaseDtMgr();
	virtual ~CBaseDtMgr();

	virtual void loadData(const string& strPath) = 0;//纯虚函数用于让子类必须在自己的作用域
	SBaseDt* getDataByID(int nID);
	vector<SBaseDt*> getAllDatas();
	int getDataSize();
protected:
	vector<SBaseDt*> m_vecDatas;
};


