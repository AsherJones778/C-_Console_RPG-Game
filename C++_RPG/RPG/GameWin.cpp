#include "stdafx.h"
#include "GameWin.h"
#include "GameMgr.h"
#include "Player.h"
enum 
{
	E_WIN_RESTART,
	E_WIN_SHOWVALUE,
	E_WIN_EXIT,
};

CGameWin::CGameWin()
{
	m_nIndex = E_WIN_RESTART;
	m_bShowPlayerValue = false;
}


CGameWin::~CGameWin()
{
}

void CGameWin::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nIndex--;
		if (m_nIndex < E_WIN_RESTART)
		{
			m_nIndex = E_WIN_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nIndex++;
		if (m_nIndex > E_WIN_EXIT)
		{
			m_nIndex = E_WIN_RESTART;
		}
	}
	
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_WIN_RESTART == m_nIndex)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		}
		else if (E_WIN_SHOWVALUE == m_nIndex)
		{
			m_bShowPlayerValue = true;
		}
		else if (E_WIN_EXIT == m_nIndex)
		{
			exit(0);
		}
	}

	if (m_bShowPlayerValue && KEY_DOWN(VK_ESCAPE))
	{
		m_bShowPlayerValue = false;
	}
}

void CGameWin::render()
{
	
	if (!m_bShowPlayerValue)
	{
		cout << "��ϲ�������������:ɱ����Ⱥ����-��ɫ���𼪣�Ұ��" << endl;
		cout << "����������´�ׯ�Ĵ�����" << endl <<endl;
		cout << "���Ѿ��ɹ�ͨ��" << endl;
		if (E_WIN_RESTART == m_nIndex)
		{
			cout << "������������������������������" << endl;
			cout << "��    ��������ɫ���¿�ʼ    ��" << endl;
			cout << "��      ��ʾ�������        ��" << endl;
			cout << "��      �˳���Ϸ            ��" << endl;
			cout << "������������������������������" << endl;
		}
		else if (E_WIN_SHOWVALUE == m_nIndex)
		{
			cout << "������������������������������" << endl;
			cout << "��      ������ɫ���¿�ʼ    ��" << endl;
			cout << "��    ����ʾ�������        ��" << endl;
			cout << "��      �˳���Ϸ            ��" << endl;
			cout << "������������������������������" << endl;
		}
		else if (E_WIN_EXIT == m_nIndex)
		{
			cout << "������������������������������" << endl;
			cout << "��      ������ɫ���¿�ʼ    ��" << endl;
			cout << "��      ��ʾ�������        ��" << endl;
			cout << "��    ���˳���Ϸ            ��" << endl;
			cout << "������������������������������" << endl;
		}

	}
	else
	{
		cout << "---------------�������---------------" <<endl;
		CPlayer* curPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
		cout << "--------------------״̬��-------------------" << endl << endl;
		cout << "    " << "�������" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����" << endl;
		CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
		cout << "    " << pPlayer->getPic() << "\t\t" << pPlayer->getHp() << "\t" << pPlayer->getMp() << "\t" << pPlayer->getAtk() << "\t" << pPlayer->getDef() << endl;
		cout << "-------------------- ��  �� -------------------" << endl << endl;
		cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����" << endl;
		vector<SItemDt*> vecBag = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getBag();
		for (int i = 0; i < vecBag.size(); i++)
		{
			cout << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t";
			cout << vecBag[i]->nMP << "\t" << vecBag[i]->nAtk << "\t" << vecBag[i]->nCount << endl;
		}
		cout << "--------------------װ����-------------------" << endl << endl;
		cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����" << endl;
		for (int i = 0; i < 4; i++)
		{
			SItemDt* pEquip = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
			if (!pEquip)
			{
				cout << "��" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" << endl;
			}
			else
			{
				cout << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << "\t" << pEquip->nDef << endl;
			}
		}
		cout << "    ����ǰ�Ľ�ң�";
		cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney() << endl;
		cout << endl;
	}

}
