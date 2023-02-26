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

	virtual void loadData(const string& strPath) = 0;//���麯������������������Լ���������
	SBaseDt* getDataByID(int nID);
	vector<SBaseDt*> getAllDatas();
	int getDataSize();
protected:
	vector<SBaseDt*> m_vecDatas;
};


