#include "stdafx.h"
#include "Enemy.h"
CEnemy::CEnemy()
{
}
CEnemy::CEnemy(SEnemyDt* pData)
{
	m_nID = pData->nID;
	m_strName = pData->strName;
	m_nHP = pData->nHP;
	m_nAtk = pData->nAtk;
	m_nDef = pData->nDef;
	m_strPic = pData->strPic;
	m_nRow = pData->nRow;
	m_nCol = pData->nCol;
	m_nMapID = pData->nMapID;
}
CEnemy::~CEnemy()
{
}
bool CEnemy::isExist(int nRow, int nCol, int nMapID)
{
	if (nRow == m_nRow && nCol == m_nCol && nMapID == m_nMapID)
	{
		return true;
	}
	return false;
}
bool CEnemy::isExist(int nRow, int nCol)
{
	if (nRow == m_nRow && nCol == m_nCol)
	{
		return true;
	}
	return false;
}
void CEnemy::emitData(SEnemyDt* pData)//从数据里面获取相关数据赋值给敌人实例
{
	m_nHP = pData->nHP;
	m_nAtk = pData->nAtk;
	m_nDef = pData->nDef;
	m_strPic = pData->strPic;
	m_nBattleMapID = pData->nBattleMapID;
	m_nID = pData->nID;
	m_nMoney = pData->nMoney;
}
void CEnemy::setRow(int nRow)
{
	m_nRow = nRow;
}
void CEnemy::setCol(int nCol)
{
	m_nCol = nCol;
}