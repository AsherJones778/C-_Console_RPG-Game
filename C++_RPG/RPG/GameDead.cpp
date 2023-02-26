#include "stdafx.h"
#include "GameDead.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include "SelectRole.h"
#include "Player.h"
enum 
{
	E_DEAD_RESTART,
	E_DEAD_VALUE,
	E_DEAD_EXIT,
};
CGameDead::CGameDead()
{
	m_nDeadIndex = E_DEAD_RESTART;
	m_bShowValue = false;
}
CGameDead::~CGameDead()
{

}
void CGameDead::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nDeadIndex--;
		if (m_nDeadIndex < E_DEAD_RESTART)
		{
			m_nDeadIndex = E_DEAD_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nDeadIndex++;
		if (m_nDeadIndex > E_DEAD_EXIT)
		{
			m_nDeadIndex = E_DEAD_RESTART;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_DEAD_RESTART == m_nDeadIndex)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->transformData(CGameMgr::getInstance()->getSelectRole()->getDefiniteRole());
		}
		else if (E_DEAD_VALUE == m_nDeadIndex)
		{
			m_bShowValue = true;
		}
		else if (E_DEAD_EXIT == m_nDeadIndex)
		{
			exit(0);
		}
	}
}
void CGameDead::render()
{
	if (E_DEAD_RESTART == m_nDeadIndex)
	{
		cout << "�������������Ѿ���������������" << endl;
		cout << "��        �����¿�ʼ        ��" << endl;
		cout << "��          �鿴����        ��" << endl;
		cout << "��          �˳���Ϸ        ��" << endl;
		cout << "������������������������������" << endl;
	}
	else if (E_DEAD_VALUE == m_nDeadIndex)
	{
		cout << "�������������Ѿ���������������" << endl;
		cout << "��          ���¿�ʼ        ��" << endl;
		cout << "��        ���鿴����        ��" << endl;
		cout << "��          �˳���Ϸ        ��" << endl;
		cout << "������������������������������" << endl;
	}
	else if (E_DEAD_EXIT == m_nDeadIndex)
	{
		cout << "�������������Ѿ���������������" << endl;
		cout << "��          ���¿�ʼ        ��" << endl;
		cout << "��          �鿴����        ��" << endl;
		cout << "��        ���˳���Ϸ        ��" << endl;
		cout << "������������������������������" << endl;
	}
	if (m_bShowValue)
	{
		showPlayerValue();
	}
}
void CGameDead::showPlayerValue()
{
	CPlayer* pData = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	cout << "��ɫ����" << "\t" << "����ֵ" << "\t" << "����ֵ" << "\t" << "������" << "\t" << "������" << endl;
	cout << pData->getPic() << "\t" << "\t" << pData->getHp() << "\t" << pData->getMp() << "\t" << pData->getAtk() << "\t" << pData->getDef() << endl;
}
