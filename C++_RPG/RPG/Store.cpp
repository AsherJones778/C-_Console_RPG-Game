#include "stdafx.h"
#include "Store.h"
#include "GameMgr.h"
#include "DataMgr.h"
CStore::CStore()
{
	m_bEnoughMoney = true;
}


CStore::~CStore()
{
	for (SItemDt* pData : m_vecItems)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecItems.clear();
}

void CStore::update()
{
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	int nPlayerMoney = pPlayer->getMoney();
	if (KEY_DOWN(VK_UP))
	{
		m_nIndex--;
		if (m_nIndex < 0)
		{
			m_nIndex = m_vecItems.size() - 1;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nIndex++;
		if (m_nIndex > m_vecItems.size() - 1)
		{
			m_nIndex = 0;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		SItemDt* pItem = m_vecItems[m_nIndex];
		if (nPlayerMoney >= pItem->nMoney)
		{
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->addItemToBag(pItem);
			int nMoneyAfterDeduction = nPlayerMoney - pItem->nMoney;
			pPlayer->setMoney(nMoneyAfterDeduction);
			m_bEnoughMoney = true;
			
		}
		else
		{
			m_bEnoughMoney = false;
		}
	}
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
	}
}

void CStore::render()
{
	cout << "--------------------��Ϸ�̵�-------------------" << endl << endl;
	cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "���" << endl;
	for (int i = 0; i < m_vecItems.size(); i++)
	{
		if (i == m_nIndex)
		{
			cout << "->  ";
		}
		else
		{
			cout << "    ";
		}
		cout << m_vecItems[i]->strName << "\t" << m_vecItems[i]->nHP << "\t";
		cout << m_vecItems[i]->nMP << "\t" << m_vecItems[i]->nAtk << "\t";
		cout << m_vecItems[i]->nMoney << endl;
	}
	if (!m_bEnoughMoney)
	{
		cout << "             ���Ľ�Ǯ����          "<<endl;
	}
	cout << "------------------------------------------------" << endl;
	cout << "---------------��Esc���뿪�̵�------------------" << endl;
	cout << "-------------------- ��  �� --------------------" << endl << endl;
	cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����" << endl;
	vector<SItemDt*> vecBag = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getBag();
	for (int i = 0; i < vecBag.size(); i++)
	{
		cout << "    " << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t";
		cout << vecBag[i]->nMP << "\t" << vecBag[i]->nAtk << "\t" << vecBag[i]->nCount << endl;
	}
	cout << "    ����ǰ�Ľ�ң�";
	cout << CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getMoney()<<endl;
}

void CStore::initItemWithNpcID(int nNpcID)
{
	m_vecItems.clear();
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getMgr("ItemDtMgr")->getAllDatas();
	for (SBaseDt* pData : vecDatas)
	{
		SItemDt* pItemDt = static_cast<SItemDt*>(pData);
		if (pItemDt->nNpcID == nNpcID)
		{
			m_vecItems.push_back(pItemDt);
		}
	}
}
