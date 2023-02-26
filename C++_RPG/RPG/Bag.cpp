#include "stdafx.h"
#include "Bag.h"
#include "DataBasic.h"
#include "GameMgr.h"
CBag::CBag()
{
	m_nIndex = 0;
	m_pDefItem = new SItemDt();
}
CBag::~CBag()
{
	CC_SAFE_DELETE(m_pDefItem);
}
void CBag::update()
{
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();//拿到当前地图中的玩家
	vector<SItemDt*> vecBag = pPlayer->getBag();//拿到玩家的背包物品
	if (KEY_DOWN(VK_UP))
	{
		m_nIndex--;
		if (m_nIndex < 0)
		{
			m_nIndex = vecBag.size() - 1;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nIndex++;
		if (m_nIndex > vecBag.size() - 1)
		{
			m_nIndex = 0;
		}
	}
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);//返回地图
	}
	if (KEY_DOWN(VK_BACK))
	{
		if (vecBag.empty())
		{
			return;
		}
		if (pPlayer->isNearANpc())//如果在NPC附近
		{
			if (m_pDefItem->nCount == 1)//如果物品只有一件
			{
				sellItems(pPlayer);
			}
			else
			{
				sellItems(pPlayer);
				m_pDefItem->nCount--;
			}
		}	
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (vecBag.empty())
		{
			return;
		}
		//使用道具
		if (vecBag[m_nIndex]->nType == 10)
		{
			if (vecBag[m_nIndex]->strName == "大还丹" && vecBag[m_nIndex]->nCount > 0)
			{
				pPlayer->setMp(pPlayer->getMp() + vecBag[m_nIndex]->nMP);//回复篮量
				vecBag[m_nIndex]->nCount--;
				if (vecBag[m_nIndex]->nCount == 0)
				{
					pPlayer->removeItemFromBag(m_nIndex);
				}
			}
			else if (vecBag[m_nIndex]->strName == "大补丹" && vecBag[m_nIndex]->nCount > 0)
			{
				pPlayer->setHp(pPlayer->getHp() + vecBag[m_nIndex]->nHP);//回复血量
				useGood(vecBag, pPlayer);
			}
		}
		if (m_nIndex < 0 || m_nIndex > vecBag.size() - 1)
		{
			return;
		}
		if (vecBag[m_nIndex]->nType >= 10)
		{
			return;
		}
		pPlayer->addEquip(vecBag[m_nIndex]);//穿装备
		pPlayer->addValue(vecBag[m_nIndex]);//加上对应的属性
		pPlayer->removeItemFromBag(m_nIndex);//从背包移除这个装备
	}
}
void CBag::render()
{
	cout << "-------------------- 背  包 -------------------" << endl << endl;
	cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << "\t" << "数量" << endl;
	vector<SItemDt*> vecBag = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getBag();
	for (int i = 0; i < vecBag.size(); i++)
	{
		if (i == m_nIndex)
		{
			cout << "->  ";
			m_pDefItem = vecBag[m_nIndex];
		}
		else
		{
			cout << "    ";
		}
		cout << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t";
		cout << vecBag[i]->nMP << "\t" << vecBag[i]->nAtk << "\t" << vecBag[i]->nCount << endl;
	}
	cout << endl << endl;
	cout << "--------------------装备栏-------------------" << endl << endl;
	cout << "    " << "名称" << "\t" << "血量" << "\t" << "蓝量" << "\t" << "攻击" << endl;
	for (int i = 0; i < 4; i++)
	{
		SItemDt* pEquip = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
		if (!pEquip)
		{
			cout << "    " << "空" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << endl;
		}
		else
		{
			cout << "    " << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << endl;
		}
	}
	cout << "    您当前的金币：";
	cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney() << endl;
}
void CBag::sellItems(CPlayer* pPlayer)
{
	pPlayer->removeItemFromBag(m_nIndex);
	int nCurPlayerMoney = pPlayer->getMoney();
	int nMedian = m_pDefItem->nMoney * 0.7 + nCurPlayerMoney;
	pPlayer->setMoney(nMedian);
}
void CBag::useGood(vector<SItemDt*> vecBag,CPlayer* pPlayer)
{
	vecBag[m_nIndex]->nCount--;
	if (vecBag[m_nIndex]->nCount == 0)
	{
		pPlayer->removeItemFromBag(m_nIndex);
	}
}
