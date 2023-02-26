#pragma once
#include "DataBasic.h"
class CPet
{
public:
	CPet();
	~CPet();
	void update();
	void emitData(SItemDt* pData);
	void setPosition(int nRow, int nCol);
	bool isExist(int nRow, int nCol);
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic);
private:
	int m_nRow;
	int m_nCol;
	string m_strName;
	int m_nAtk;
	int m_nMoney;
	int m_nDef;
	int m_nHP;
	int m_nMP;
};