#pragma once
#include "DataBasic.h"
class CEnemy
{
public:
	CEnemy();
	CEnemy(SEnemyDt* pData);
	~CEnemy();
	bool isExist(int nRow,int nCol,int nMapID);
	bool isExist(int nRow, int nCol);
	void emitData(SEnemyDt* pData);
	void setRow(int nRow);
	void setCol(int nCol);
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic);
	CC_SYNTHESIZE_READONLY(int, m_nRow,Row);
	CC_SYNTHESIZE_READONLY(int, m_nCol, Col);
	CC_SYNTHESIZE(int, m_nHP,HP);
	CC_SYNTHESIZE(int, m_nAtk, Atk);
	CC_SYNTHESIZE(int, m_nDef, Def);
	CC_SYNTHESIZE(int, m_nBattleMapID, BattleMapID);
	CC_SYNTHESIZE(int, m_nID,ID);
	CC_SYNTHESIZE_READONLY(int, m_nMoney,Money);
private:
	string m_strName;
	int m_nMapID;
};