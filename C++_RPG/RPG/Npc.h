#pragma once
#include "DataBasic.h"
class CNpc
{
public:
	CNpc();
	CNpc(SNpcDt* pData);
	~CNpc();
	void addMission(SMissionDt* pData);
	bool isExist(int nRow,int nCol,int nMapID);
	CC_SYNTHESIZE(string,m_strPic,Pic);
	CC_SYNTHESIZE(int, m_nID, ID);
	CC_SYNTHESIZE(int, m_nDeal, Deal);
	CC_SYNTHESIZE(vector<SMissionDt*>,m_vecMission,NpcMission);
	CC_SYNTHESIZE(string, m_strName,Name);
	CC_SYNTHESIZE(int, m_nRow,Row);
	CC_SYNTHESIZE(int, m_nCol,Col);
private:
	int m_nMapID;
};

