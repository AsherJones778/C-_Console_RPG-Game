#include "stdafx.h"
#include "Player.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include "DataBasic.h"
#include "GameMap.h"
#define VK_B 0x42
#define VK_M 0x4D
CPlayer::CPlayer()//��Ǯ���ܷŽ�������캯�� ��Ϊû�е���
{
	
}

CPlayer::~CPlayer()
{
	CC_SAFE_DELETE(m_pCurEnemyDt);
	CC_SAFE_DELETE(m_pPet);
	CC_SAFE_DELETE(m_pCurEnemyDt);
	for (SSkillDt* pData : m_vecSkill)
	{
		delete pData;
		pData = nullptr;
	}
	for (SMissionDt* pData : m_vecMission)
	{
		delete pData;
		pData = nullptr;
	}
	for (SItemDt* pData : m_vecBag)
	{
		delete pData;
		pData = nullptr;
	}

	for (int i = 0; i < 4; i++)
	{
		delete m_arrWeapons[i];
		m_arrWeapons[i] = nullptr;
	}

	m_vecSkill.clear();
	m_vecMission.clear();
	m_vecBag.clear();
}

bool CPlayer::isExist(int nRow, int nCol)
{
	if (nRow == m_nRow && nCol == m_nCol)
	{
		return true;
	}
	return false;
}

void CPlayer::update()
{
	m_nRowBk = m_nRow;
	m_nColBk = m_nCol;
	if (KEY_DOWN(VK_UP))
	{
		m_nRow--;
		petMove();
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nRow++;
		petMove();
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_nCol--;
		petMove();
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_nCol++;
		petMove();
	}
	else if (KEY_DOWN(VK_B))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_BAG);
	}
	else if (KEY_DOWN(VK_M))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_PLAYERSTATE);
	}
	
	if (KEY_DOWN(VK_F1))
	{
		for (SMissionDt* pData : m_vecMission)
		{
			if (pData->nNeedCount == 0)
			{
				CGameMgr::getInstance()->getHandInMission()->getMission(pData);
				CGameMgr::getInstance()->setGameScene(E_GAME_HANDINMISSION);
			}
		}
	}
	
	//���ײǽ����
	SMapDt* pCurMapDt = CGameMgr::getInstance()->getGameMap()->getCurMapDt();
	if (1 == pCurMapDt->arrMap[m_nRow][m_nCol])
	{
		restorePosition();
	}
	//��ײ�����Ų����д���
	if (pCurMapDt->arrMap[m_nRow][m_nCol] > 1000)
	{
		int nMapID = pCurMapDt->arrMap[m_nRow][m_nCol];
		SMapDt* pNextMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getMgr("MapDtMgr")->getDataByID(nMapID));
		CGameMgr::getInstance()->getGameMap()->setCurMapDt(pNextMapDt);
		m_nRow = pNextMapDt->nPlayerRow;
		m_nCol = pNextMapDt->nPlayerCol;
	}

	//���ײ�Ϲ��ﴦ��
	vector<SBaseDt*> vecMonster = CDataMgr::getInstance()->getMgr("EnemyDtMgr")->getAllDatas();
	for (int i = 0; i < vecMonster.size(); i++)
	{
		SEnemyDt* pData = static_cast<SEnemyDt*>(vecMonster[i]);
		if (m_nRow == pData->nRow && m_nCol == pData->nCol && pData->nMapID == CGameMgr::getInstance()->getGameMap()->getCurMapDt()->nID)
		{
			restorePosition();//��ԭλ��
			m_pCurEnemyDt->emitData(pData);//����ǰ�ĵ�����Ϣ����
			CGameMgr::getInstance()->getBattleScene()->init(this);//ս��������ʼ��
			CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE);//����ս������
		}
	}
	//ײ���̵����͵�NPC���������̵�
	CGameMap* pGameMap = CGameMgr::getInstance()->getGameMap();
	CNpc* pNpc = pGameMap->getCurNpcMgr()->isExist(m_nRow, m_nCol, pGameMap->getCurMapDt()->nID);
	if (pNpc)
	{
		if (pNpc->getDeal() == 1)//���NPC���̵����͵�
		{
			//��ԭ���λ��
			restorePosition();
			//�����̵�ĳ�ʼ��������������Ʒ
			CGameMgr::getInstance()->getStore()->initItemWithNpcID(pNpc->getID());
			CGameMgr::getInstance()->setGameScene(E_GAME_STORE);//�����̵�
		}
		if (pNpc->getDeal() == 0)//���NPC���������͵�
		{
			restorePosition();
			CGameMgr::getInstance()->getMissionScene()->setNpc(pNpc);//����ǰ��NPC�����������
			CGameMgr::getInstance()->getMissionScene()->setPlayer(this);//����ǰ����Ҵ����������
			CGameMgr::getInstance()->getMissionScene()->initMissionWithNpcID(pNpc->getID());//��ͬ��NPC��ʼ��Ϊ��ͬ������
			CGameMgr::getInstance()->setGameScene(E_GAME_MISSIONSCENE);
		}
	}
	

}

void CPlayer::transformData(SRoleDt* pData)
{
	SMapDt* pCurMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getMgr("MapDtMgr")->getDataByID(1001));//�����ݵ�ͼ���õ���ʼ��ͼ����
	CGameMgr::getInstance()->getGameMap()->setCurMapDt(pCurMapDt);//����ʼ��ͼ���ݸ�ֵ����ͼ
	m_nRow = pCurMapDt->nPlayerRow;//�����ʼ��λ��
	m_nCol = pCurMapDt->nPlayerCol;//�����ʼ��λ��
	m_nMoney = 100;//��ҳ�ʼ�����
	m_pPet = new CPet();
	m_nRowBk = 0;
	m_nColBk = 0;

	m_vecMission.clear();
	m_vecBag.clear();
	m_vecSkill.clear();



	//��Ҽ��ܵĳ�ʼ��
	vector<SBaseDt*> vecAllSkill = CDataMgr::getInstance()->getMgr("SkillDtMgr")->getAllDatas();
	for (int i = 0; i < vecAllSkill.size(); i++)
	{
		SSkillDt* pSkillData = static_cast<SSkillDt*>(vecAllSkill[i]);
		if (pSkillData->nPlayerID == pData->nID)
		{
			m_vecSkill.push_back(pSkillData);
		}
	}

	m_pCurEnemyDt = new CEnemy();
	//��Ӧ�����Ը�ֵ 
	m_nID = pData->nID;
	m_strName = pData->strName;
	m_nHp = pData->nHP;
	m_nMp = pData->nMP;
	m_nAtk = pData->nAtk;
	m_nDef = pData->nDef;
	m_strPic = pData->strPic;
	
}

void CPlayer::addItemToBag(SItemDt* pItem)
{
	if (!pItem)
	{
		return;
	}
	for (SItemDt* pData : m_vecBag)
	{
		if (pData->nID == pItem->nID)
		{
			pData->nCount++;
			return;
		}
	}
	pItem->nCount = 1;
	m_vecBag.push_back(pItem);
}

vector<SItemDt*> CPlayer::getBag()
{
	return m_vecBag;
}

void CPlayer::addEquip(SItemDt* pEquip)
{
	if (m_arrWeapons[pEquip->nType])
	{
		//�Ȱ�װ������ȥ���ٴ���װ��
		this->addItemToBag(m_arrWeapons[pEquip->nType]);
		m_arrWeapons[pEquip->nType] = nullptr;
		m_arrWeapons[pEquip->nType] = pEquip;
	}
	m_arrWeapons[pEquip->nType] = pEquip;
}

SItemDt* CPlayer::getEquipByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex > 3)
	{
		return nullptr;
	}
	return m_arrWeapons[nIndex];
}

void CPlayer::removeItemFromBag(int nIndex)
{
	int nCount = m_vecBag.size() - 1;
	if (nIndex < 0 || nIndex > nCount)
	{
		return;
	}
	if (m_vecBag[nIndex]->nCount > 1)
	{
		m_vecBag[nIndex]->nCount--;
	}
	else
	{
		m_vecBag.erase(m_vecBag.begin() + nIndex);
	}
}

int CPlayer::getMoney()
{
	return m_nMoney;
}

void CPlayer::setMoney(int nMoney)
{
	m_nMoney = nMoney;
}

bool CPlayer::isNearANpc()
{
	vector<SBaseDt*> vecNpcs = CDataMgr::getInstance()->getMgr("NpcDtMgr")->getAllDatas();
	for (int i = 0; i < vecNpcs.size(); i++)
	{
		SNpcDt* pData = static_cast<SNpcDt*>(vecNpcs[i]);
		if ((m_nRow == pData->nRow && (m_nCol == pData->nCol + 1 || m_nCol == pData->nCol - 1)) || m_nCol == pData->nCol && (m_nRow == pData->nRow + 1 || m_nRow == pData->nRow - 1))
		{
			return true;
		}
	}
	return false;
}

void CPlayer::petMove()
{
	if (m_arrWeapons[2])
	{
		m_pPet->emitData(m_arrWeapons[2]);
		m_pPet->setPosition(m_nRowBk, m_nColBk);
	}
	if (!m_pPet)
	{
		m_pPet->update();
	}
}

void CPlayer::takeOffItemByIndex(int nIndex)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == nIndex)
		{
			m_arrWeapons[i] = nullptr;
		}
	}
}

void CPlayer::addValue(SItemDt* pData)
{
	m_nHp = m_nHp + pData->nHP;
	m_nMp = m_nMp + pData->nMP;
	m_nAtk = m_nAtk + pData->nAtk;
	m_nDef = m_nDef + pData->nDef;
}

void CPlayer::delValue(SItemDt* pData)
{
	vector<SBaseDt*> vecRole = CDataMgr::getInstance()->getMgr("RoleDtMgr")->getAllDatas();
	for (SBaseDt* pTemp : vecRole)
	{
		SRoleDt* pRole = static_cast<SRoleDt*>(pTemp);
		if (pRole->nID == this->getID())
		{
			if (m_nHp - pData->nHP < pRole->nHP)
			{
				m_nHp = m_nHp;
			}
			else
			{
				m_nHp = m_nHp - pData->nHP;
			}
			if (m_nMp - pData->nMP < pRole->nMP)
			{
				m_nMp = m_nMp;
			}
			else
			{
				m_nMp = m_nMp - pData->nMP;
			}
		}
	}
	m_nAtk = m_nAtk - pData->nAtk;
	m_nDef = m_nDef - pData->nDef;
}

void CPlayer::setRow(int nRow)
{
	m_nRow = nRow;
}

void CPlayer::setCol(int nCol)
{
	m_nCol = nCol;
}

void CPlayer::setPosition(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}

void CPlayer::addMissionToVecMission(SMissionDt* pData)
{
	m_vecMission.push_back(pData);
}

bool CPlayer::judgeMissionIsExist(SMissionDt* pData)
{
	for (SMissionDt* pMission : m_vecMission)
	{
		if (pMission->nID == pData->nID)
		{
			return true;
		}
	}
	return false;
}

void CPlayer::reduceMissionMonsterNumber(int nMonsterNumber)
{
	for (SMissionDt* pData :m_vecMission)
	{
		if (pData->nEnemyID == nMonsterNumber)
		{
			if (pData->nNeedCount > 0)
			{
				pData->nNeedCount--;
			}
			if (pData->nNeedCount == 0)
			{
				pData->bIsFinish = true;
			}
		}
	}
}

void CPlayer::AddMoney(int nMoney)
{
	this->setMoney(this->getMoney() + nMoney);
}

void CPlayer::restorePosition()
{
	m_nRow = m_nRowBk;
	m_nCol = m_nColBk;
}

void CPlayer::delMission(SMissionDt* pData)
{
	for (int i = 0; i < m_vecMission.size();i++)
	{
		if (m_vecMission[i] == pData)
		{
			m_vecMission.erase(m_vecMission.begin() + i);
		}
	}
}




