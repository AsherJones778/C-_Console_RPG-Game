#include "stdafx.h"
#include "Pet.h"
#include "Player.h"
#include "GameMgr.h"
CPet::CPet()
{
}
CPet::~CPet()
{
}
bool CPet::isExist(int nRow, int nCol)
{
	if (m_nRow == nRow && m_nCol == nCol)
	{
		return true;
	}
	return false;
}
void CPet::emitData(SItemDt* pData)
{
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	if (pData)
	{
		m_strName = pData->strName;
		m_strPic = pData->strPic;
		m_nAtk = pData->nAtk;
		m_nDef = pData->nDef;
		m_nHP = pData->nHP;
		m_nMP = pData->nMP;
		m_nMoney = pData->nMoney;
	}
}
void CPet::setPosition(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}
void CPet::update()
{
	CPlayer* pData = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	m_nRow = pData->getRowBk();
	m_nCol = pData->getColBk();
}