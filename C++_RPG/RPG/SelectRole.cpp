#include "stdafx.h"
#include "SelectRole.h"
#include "DataMgr.h"
#include "GameMgr.h"
CSelectRole::CSelectRole()
{
	m_nSelectIndex = 0;
	m_vecAllRole = CDataMgr::getInstance()->getMgr("RoleDtMgr")->getAllDatas();
	m_defRole = new SRoleDt();
}


CSelectRole::~CSelectRole()
{
	CC_SAFE_DELETE(m_defRole);
	for (SBaseDt* pData : m_vecAllRole)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecAllRole.clear();
}

void CSelectRole::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nSelectIndex--;
		if (m_nSelectIndex < 0)
		{
			m_nSelectIndex = m_vecAllRole.size()-1;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nSelectIndex++;
		if (m_nSelectIndex > m_vecAllRole.size()-1)
		{
			m_nSelectIndex = 0;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->transformData(m_defRole);
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
	}

}

void CSelectRole::render()
{
	cout << "-------------------½ÇÉ«Ñ¡Ôñ-------------------" << endl;
	cout << "    " << "Ãû×Ö" << "\t" << "ÑªÁ¿" << "\t" << "À¶Á¿" << "\t" << "¹¥»÷" << "\t" << "·ÀÓù" << endl;
	for (int i = 0; i < m_vecAllRole.size(); i++)
	{
		SRoleDt* pData = static_cast<SRoleDt*>(m_vecAllRole[i]);
		if (i == m_nSelectIndex)
		{
			cout << "->  ";
			m_defRole = pData;
		}
		else
		{
			cout << "    ";
		}
		cout << pData->strName << "\t" << pData->nHP << "\t";
		cout << pData->nMP << "\t" << pData->nAtk << "\t";
		cout << pData->nDef << endl;
	}
}
