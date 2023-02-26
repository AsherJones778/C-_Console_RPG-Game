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
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();//�õ���ǰ��ͼ�е����
	vector<SItemDt*> vecBag = pPlayer->getBag();//�õ���ҵı�����Ʒ
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
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);//���ص�ͼ
	}
	if (KEY_DOWN(VK_BACK))
	{
		if (vecBag.empty())
		{
			return;
		}
		if (pPlayer->isNearANpc())//�����NPC����
		{
			if (m_pDefItem->nCount == 1)//�����Ʒֻ��һ��
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
		//ʹ�õ���
		if (vecBag[m_nIndex]->nType == 10)
		{
			if (vecBag[m_nIndex]->strName == "�󻹵�" && vecBag[m_nIndex]->nCount > 0)
			{
				pPlayer->setMp(pPlayer->getMp() + vecBag[m_nIndex]->nMP);//�ظ�����
				vecBag[m_nIndex]->nCount--;
				if (vecBag[m_nIndex]->nCount == 0)
				{
					pPlayer->removeItemFromBag(m_nIndex);
				}
			}
			else if (vecBag[m_nIndex]->strName == "�󲹵�" && vecBag[m_nIndex]->nCount > 0)
			{
				pPlayer->setHp(pPlayer->getHp() + vecBag[m_nIndex]->nHP);//�ظ�Ѫ��
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
		pPlayer->addEquip(vecBag[m_nIndex]);//��װ��
		pPlayer->addValue(vecBag[m_nIndex]);//���϶�Ӧ������
		pPlayer->removeItemFromBag(m_nIndex);//�ӱ����Ƴ����װ��
	}
}
void CBag::render()
{
	cout << "-------------------- ��  �� -------------------" << endl << endl;
	cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << "\t" << "����" << endl;
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
	cout << "--------------------װ����-------------------" << endl << endl;
	cout << "    " << "����" << "\t" << "Ѫ��" << "\t" << "����" << "\t" << "����" << endl;
	for (int i = 0; i < 4; i++)
	{
		SItemDt* pEquip = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->getEquipByIndex(i);
		if (!pEquip)
		{
			cout << "    " << "��" << "\t" << "\t" << "0" << "\t" << "0" << "\t" << "0" << endl;
		}
		else
		{
			cout << "    " << pEquip->strName << "\t" << pEquip->nHP << "\t" << pEquip->nMP << "\t" << pEquip->nAtk << endl;
		}
	}
	cout << "    ����ǰ�Ľ�ң�";
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
