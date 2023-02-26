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
	cout << "--------------------状态栏-------------------" << endl << endl;
	cout << "    " << "玩家名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "防御" << endl;
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	cout << "    " << pPlayer->getPic() << "\t\t" << pPlayer->getHp() << "\t" << pPlayer->getMp() << "\t" << pPlayer->getAtk() << "\t" << pPlayer->getDef() << endl;
	cout << "-------------------- 背  包 -------------------" << endl << endl;
	cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "数量" << endl;
	vector<SItemDt*> vecBag = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getBag();
	for (int i = 0; i < vecBag.size(); i++)
	{
		cout << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t";
		cout << vecBag[i]->nMP << "\t" << vecBag[i]->nAtk << "\t" << vecBag[i]->nCount << endl;
	}
	cout << "--------------------装备栏-------------------" << endl << endl;
	cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "防御"<<endl;
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
			cout << "空" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" <<endl;
		}
		else
		{
			cout << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << "\t" << pEquip->nDef << endl;
		}
	}
	cout << "    您当前的金币：";
	cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney() << endl;
	cout << endl;
	cout << "-----------------主线任务-----------------" <<endl <<endl;
	cout << "      " << "任务名" << "\t" << "任务概述" << "\t" << "任务NPC" << "\t" << "剩余数量" << endl;
	for (int i = 0; i < pPlayer->getMission().size();i++)
	{
		SNpcDt* temp = static_cast<SNpcDt*>(CDataMgr::getInstance()->getMgr("NpcDtMgr")->getDataByID(pPlayer->getMission()[i]->nNpcID));
		
		cout << "\t" << pPlayer->getMission()[i]->strName << "\t" << pPlayer->getMission()[i]->strDescribe << "\t" << temp->strPic << "\t" << pPlayer->getMission()[i]->nNeedCount << endl;
	}
}
