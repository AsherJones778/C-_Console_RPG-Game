#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"
#include "GameMgr.h"
#include "NpcMgr.h"
#include "DataMgr.h"
CPlayerState::CPlayerState()
{
	m_nStateIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		arrWeapon[i] = nullptr;
	}
}


CPlayerState::~CPlayerState()
{
	for (int i = 0; i < 4; i++)
	{
		delete arrWeapon[i];
		arrWeapon[i] = nullptr;
	}
}

void CPlayerState::update()
{
	for (int i = 0; i < 4; i++)
	{
		arrWeapon[i] = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
	}
	if (KEY_DOWN(VK_UP))
	{
		m_nStateIndex--;
		if (m_nStateIndex < 0)
		{
			m_nStateIndex = 3;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nStateIndex++;
		if (m_nStateIndex > 3)
		{
			m_nStateIndex = 0;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (arrWeapon[m_nStateIndex])
		{
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->addItemToBag(arrWeapon[m_nStateIndex]);
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->delValue(arrWeapon[m_nStateIndex]);
			arrWeapon[m_nStateIndex] = nullptr;
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->takeOffItemByIndex(m_nStateIndex);
		}
	}
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
	}
}

void CPlayerState::render()
{
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
	cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����"<<endl;
	for (int i = 0; i < 4; i++)
	{
		if (i == m_nStateIndex)
		{
			cout << "->  ";
		}
		else
		{
			cout << "    ";
		}
		SItemDt* pEquip = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
		if (!pEquip)
		{
			cout << "��" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" <<endl;
		}
		else
		{
			cout << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << "\t" << pEquip->nDef << endl;
		}
	}
	cout << "    ����ǰ�Ľ�ң�";
	cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney() << endl;
	cout << endl;
	cout << "-----------------��������-----------------" <<endl <<endl;
	cout << "      " << "������" << "\t" << "�������" << "\t" << "����NPC" << "\t" << "ʣ������" << endl;
	for (int i = 0; i < pPlayer->getMission().size();i++)
	{
		SNpcDt* temp = static_cast<SNpcDt*>(CDataMgr::getInstance()->getMgr("NpcDtMgr")->getDataByID(pPlayer->getMission()[i]->nNpcID));
		
		cout << "\t" << pPlayer->getMission()[i]->strName << "\t" << pPlayer->getMission()[i]->strDescribe << "\t" << temp->strPic << "\t" << pPlayer->getMission()[i]->nNeedCount << endl;
	}
}
