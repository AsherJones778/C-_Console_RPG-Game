#include "stdafx.h"
#include "BattleScene.h"
#include "DataMgr.h"
#include "GameMgr.h"
enum 
{
	E_BATTLE_COMMONATTACK,
	E_BATTLE_SKILL,
	E_BATTLE_USEGOOD,
	E_BATTLE_RUNAWAY,
};
CBattleScene::CBattleScene()
{
	m_nBattleState = E_BATTLE_COMMONATTACK;
	m_nCount = 0;
	m_pCurMapDt = static_cast<SBattleMapDt*>(CDataMgr::getInstance()->getMgr("BattleMapDtMgr")->getDataByID(9001));
	m_pPlayer = new CPlayer();
	m_pEnemy = new CEnemy();
	m_bPlayerStartCommonAttack = false;
	m_bEnemyStartCommonAttack = false;
	m_bAbleToMove = true;
	m_bSkillState = false;
	m_nSkillIndex = 0;
	m_bPlayerSkillAttack = false;
	m_bEnemySkillAttack = false;
	m_bUseGoods = false;
	m_nGoodsIndex = 0;
	m_nSkillCount = 1;
	m_bJudgeSkillOrCommon = false;
	m_bShowNoMp = false;
	m_bShowGoodLack = false;
	m_bAllowChooseGood = true;
}
CBattleScene::~CBattleScene()
{
	CC_SAFE_DELETE(m_pCurMapDt);
	CC_SAFE_DELETE(m_pPlayer);
	CC_SAFE_DELETE(m_pEnemy);
	for (SItemDt* pData :m_vecGoods)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecGoods.clear();
}
void CBattleScene::update()
{
	CPlayer* pTempPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	//��ʼ��
	m_pCurMapDt = static_cast<SBattleMapDt*>(CDataMgr::getInstance()->getMgr("BattleMapDtMgr")->getDataByID(pTempPlayer->getEnemy()->getBattleMapID()));
	//�ж��Ƿ��ڼ���ѡ�� ���ܹ���ƶ�
	if (m_bSkillState && !m_bPlayerSkillAttack && !m_bEnemySkillAttack)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nSkillIndex--;
			if (m_nSkillIndex < 0)
			{
				m_nSkillIndex = 3;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nSkillIndex++;
			if (m_nSkillIndex > 3)
			{
				m_nSkillIndex = 0;
			}
		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bSkillState = false;
		}
		if (KEY_DOWN(VK_RETURN))
		{
			if (m_pPlayer->getMp() >= m_pPlayer->getSkillBag()[m_nSkillIndex]->nMP)//���������㹻�˴μ����ͷ�
			{
				m_bPlayerSkillAttack = true;
				m_bJudgeSkillOrCommon = true;
				m_pPlayer->setMp(m_pPlayer->getMp() - m_pPlayer->getSkillBag()[m_nSkillIndex]->nMP);//ʹ�ü��ܼ�������
				m_bShowNoMp = false;
				m_bShowGoodLack = false;
			}
			else
			{
				m_bShowNoMp = true;
				m_bShowGoodLack = false;
			}
		}
	}
	//��Ʒ������ƶ�
	if (m_bUseGoods && m_bAllowChooseGood)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nGoodsIndex--;
			if (m_nGoodsIndex < 0)
			{
				m_nGoodsIndex = 1;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nGoodsIndex++;
			if (m_nGoodsIndex > 1)
			{
				m_nGoodsIndex = 0;
			}
		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bUseGoods = false;
		}
		if (KEY_DOWN(VK_RETURN))
		{
			if (!m_pPlayer->getBag().empty())
			{
				if (m_pPlayer->getBag()[m_nGoodsIndex]->strName == "�󻹵�" && m_pPlayer->getBag()[m_nGoodsIndex]->nCount > 0)
				{
					m_pPlayer->setMp(m_pPlayer->getMp() + m_pPlayer->getBag()[m_nGoodsIndex]->nMP);//�ظ�����
					useGoodOperate();
				}
				else if (m_pPlayer->getBag()[m_nGoodsIndex]->strName == "�󲹵�" && m_pPlayer->getBag()[m_nGoodsIndex]->nCount > 0)
				{
					m_pPlayer->setHp(m_pPlayer->getHp() + m_pPlayer->getBag()[m_nGoodsIndex]->nHP);//�ظ�Ѫ��
					useGoodOperate();
				}
			}
			else
			{
				m_bShowGoodLack = true;//û�е��߻��ߵ�����������
			}
			
		}
	}
	//��Ҽ��ܹ���
	playerSkillAttack(m_pPlayer->getAtk(), m_pEnemy->getDef());
	EnemySkillAttack(m_pEnemy->getAtk(), m_pPlayer->getDef());
	//��ҹ���ǰѡ�������ʽ
	if (!m_bPlayerStartCommonAttack && !m_bEnemyStartCommonAttack && m_bAbleToMove && !m_bSkillState && !m_bUseGoods)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nBattleState--;
			if (m_nBattleState < E_BATTLE_COMMONATTACK)
			{
				m_nBattleState = E_BATTLE_RUNAWAY;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nBattleState++;
			if (m_nBattleState > E_BATTLE_RUNAWAY)
			{
				m_nBattleState = E_BATTLE_COMMONATTACK;
			}
		}
		if (KEY_DOWN(VK_RETURN))
		{
			if (E_BATTLE_COMMONATTACK == m_nBattleState)//��ͨ����
			{
				m_bPlayerStartCommonAttack = true;
				m_nCount++;
				m_bJudgeSkillOrCommon = false;
				m_bShowNoMp = false;
				m_bShowGoodLack = false;
			}
			else if (E_BATTLE_SKILL == m_nBattleState)//���ܹ���
			{
				m_bSkillState = true;
				m_bShowGoodLack = false;
			}
			else if (E_BATTLE_USEGOOD == m_nBattleState)//ʹ�õ���
			{
				m_bUseGoods = true;
			}
			else if (E_BATTLE_RUNAWAY == m_nBattleState)//����
			{
				restorePosition(pTempPlayer);//��ԭ��ͼλ��
				m_pPlayer->setHp(m_pPlayer->getHp() - (m_pEnemy->getAtk() - m_pPlayer->getDef()));//������ҿ۳�Ѫ��
			}
		}
	}
	//������ͨ����
	playerCommonAttack(m_pPlayer->getAtk(), m_pEnemy->getDef());
	EnemyCommonAttack(m_pEnemy->getAtk(), m_pPlayer->getDef());
	//��������
	if (m_pEnemy->getHP() <= 0)
	{
		
		m_nCount = 0;
		m_bSkillState = false;
		//����
		int nReward = m_pEnemy->getMoney();
		m_pPlayer->setMoney(m_pPlayer->getMoney() + nReward);
		//�����ж�
		CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->reduceMissionMonsterNumber(m_pEnemy->getID());
		restorePosition(pTempPlayer);
	}
	//�������
	if (m_pPlayer->getHp() <= 0)
	{
		m_pPlayer->setHp(0);
		CGameMgr::getInstance()->setGameScene(E_GAME_DEAD);
		m_nCount = 0;
		m_bSkillState = false;
	}
}
void CBattleScene::render()
{
	cout << "\t" << "��ǰ����:" << m_pCurMapDt->strName << endl;
	for (int i = 0; i < m_pCurMapDt->nRowCount; i++)
	{
		for (int j = 0; j < m_pCurMapDt->nColCount; j++)
		{

			if (1 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "��";
			}
			else if (m_pPlayer->isExist(i,j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (m_pEnemy->isExist(i,j))
			{
				cout << m_pEnemy->getPic();
			}
			else if (0 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "  ";
			}
		}
		cout << endl;
	}

	if (E_BATTLE_COMMONATTACK == m_nBattleState)
	{
		cout << "������������������������" << endl;
		cout << "��        ����ͨ����  ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "������������������������" << endl;
	}
	else if (E_BATTLE_SKILL == m_nBattleState)
	{
		cout << "������������������������" << endl;
		cout << "��          ��ͨ����  ��" << endl;
		cout << "��        ������      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "������������������������" << endl;
	}
	else if (E_BATTLE_USEGOOD == m_nBattleState)
	{
		cout << "������������������������" << endl;
		cout << "��          ��ͨ����  ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��        ������      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "������������������������" << endl;
	}
	else if (E_BATTLE_RUNAWAY == m_nBattleState)
	{
		cout << "������������������������" << endl;
		cout << "��          ��ͨ����  ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��          ����      ��" << endl;
		cout << "��        ������      ��" << endl;
		cout << "������������������������" << endl;
	}

	cout << endl << endl;
	cout << "---��ǰ���״̬---" << "\t" << "---��ǰ����״̬---" << endl << endl;
	cout << "����ֵ:  " << m_pPlayer->getHp() << "\t" << "\t" << "����ֵ:  " << m_pEnemy->getHP() << endl;
	cout << "������:  " << m_pPlayer->getAtk() << "\t" << "\t" << "������:  " << m_pEnemy->getAtk() << endl;
	cout << "������:  " << m_pPlayer->getDef() << "\t" << "\t" << "������:  " << m_pEnemy->getDef() << endl;
	cout << " MPֵ :  " << m_pPlayer->getMp() << endl;
	
	if (m_bSkillState)
	{
		cout << "---------------������---------------" << endl << endl;
		cout << "    " << "    " << "��������" << "\t" << "\t" << "�ķ�MP��" << "\t"  << "�˺�׷��" << endl;
		vector<SSkillDt*> vecSkill = m_pPlayer->getSkillBag();
		for (int i = 0; i < vecSkill.size(); i++)
		{
			if (i == m_nSkillIndex)
			{
				cout << "��  ";
			}
			else
			{
				cout << "    ";
			}
			cout << "    " 
				<< vecSkill[i]->strName << "\t" << "\t" << vecSkill[i]->nMP << "\t" << "\t" << vecSkill[i]->nAtk << endl;
		}
	}


	if (m_bUseGoods)
	{
		vector<SItemDt*> vecBag = m_pPlayer->getBag();
		cout << "---------------������---------------" << endl;
		cout << "      " << "����" << "\t" << "�ظ�����ֵ" << "\t" << "�ظ�����ֵ" << "\t" << "����" << endl;
		for (int i = 0; i < vecBag.size(); i++)
		{
			if (vecBag[i]->nNpcID == 104)
			{
				if (i == m_nGoodsIndex)
				{
					cout << "  ��";
				}
				else
				{
					cout << "    ";
				}
				cout << "  " << vecBag[i]->strName << "\t" << vecBag[i]->nHP << "\t" << "\t" << vecBag[i]->nMP << "\t" << "\t" << vecBag[i]->nCount << endl;
			}
		}
	}
	if (m_bShowNoMp)
	{
		cout << "û���㹻�������ͷż��ܣ�" << endl;
	}
	if (m_bShowGoodLack)
	{
		cout << "������û��ҩƷ����ҩƷ�������㣡��ս�����¶������ٲ��䣡";
	}
}
void CBattleScene::setEnemyValues(int nRow, int nCol, CEnemy* pData)
{
	m_pEnemy = pData;
	m_pEnemy->setRow(nRow);
	m_pEnemy->setCol(nCol);
	m_pEnemy->setID(pData->getID());
}
void CBattleScene::setPlayerValues(int nRow, int nCol, CPlayer* pData)
{
	m_pPlayer = pData;
	m_pPlayer->setRow(nRow);
	m_pPlayer->setCol(nCol);
}
void CBattleScene::playerCommonAttack(int nPlayerAtk, int nEnemyDef)
{
	if (m_bPlayerStartCommonAttack && m_pPlayer->getCol() != m_pEnemy->getCol())
	{
		m_pPlayer->setCol(m_pPlayer->getCol() + 1);
		if (m_pPlayer->getCol() == m_pEnemy->getCol())
		{
			m_pPlayer->setPosition(m_pCurMapDt->nPlayerRow, m_pCurMapDt->nPlayerCol);
			m_bPlayerStartCommonAttack = false;
			int nManage = 0;
			nManage = nPlayerAtk - nEnemyDef;
			if (nManage >= 0)
			{
				m_pEnemy->setHP(m_pEnemy->getHP() - nManage);
			}
		}
	}
}
void CBattleScene::EnemyCommonAttack(int nEnemyAtk, int nPlayerDef)
{
	if (!m_bPlayerStartCommonAttack && m_nCount > 0 && !m_bJudgeSkillOrCommon)
	{
		m_bEnemyStartCommonAttack = true;
		m_pEnemy->setCol(m_pEnemy->getCol() - 1);
		if (m_pEnemy->getCol() == m_pPlayer->getCol())
		{
			m_bEnemyStartCommonAttack = false;
			m_pEnemy->setRow(m_pCurMapDt->nEnemyRow);
			m_pEnemy->setCol(m_pCurMapDt->nEnemyCol);
			m_nCount--;
			int nManage = 0;
			nManage = nEnemyAtk - nPlayerDef;
			if (nManage > 0)
			{
				m_pPlayer->setHp(m_pPlayer->getHp() - nManage);
			}
			else if (nManage <= 0)
			{
				m_pPlayer->setHp(m_pPlayer->getHp() - 1);
			}
			m_bAllowChooseGood = true;
		}
	}
}
void CBattleScene::playerSkillAttack(int nPlayerAtk, int nEnemyDef)
{
	if (m_bPlayerSkillAttack && m_pPlayer->getCol() != m_pEnemy->getCol() && !m_bEnemySkillAttack && m_bJudgeSkillOrCommon)
	{

		vector<SSkillDt*> vecSkill = m_pPlayer->getSkillBag();
		int nAddAttack = vecSkill[m_nSkillIndex]->nAtk;

		m_pPlayer->setCol(m_pPlayer->getCol() + 1);
		if (m_pPlayer->getCol() == m_pEnemy->getCol())
		{
			m_nCount++;
			m_pPlayer->setPosition(m_pCurMapDt->nPlayerRow, m_pCurMapDt->nPlayerCol);
			m_bPlayerSkillAttack = false;
			int nManage = 0;
			nManage = nPlayerAtk * nAddAttack - nEnemyDef;
			if (nManage >= 0)
			{
				m_pEnemy->setHP(m_pEnemy->getHP() - nManage);
			}
			m_bEnemySkillAttack = true;
		}
	}
}
void CBattleScene::EnemySkillAttack(int nEnemyAtk, int nPlayerDef)
{
	if (!m_bPlayerSkillAttack && m_nCount > 0 && m_bJudgeSkillOrCommon)
	{
		m_bEnemySkillAttack = true;
		m_pEnemy->setCol(m_pEnemy->getCol() - 1);
		if (m_pEnemy->getCol() == m_pPlayer->getCol())
		{
			m_bEnemySkillAttack = false;
			m_pEnemy->setRow(m_pCurMapDt->nEnemyRow);
			m_pEnemy->setCol(m_pCurMapDt->nEnemyCol);
			m_nCount--;
			int nManage = 0;
			nManage = nEnemyAtk - nPlayerDef;
			if (nManage > 0 )
			{
				m_pPlayer->setHp(m_pPlayer->getHp() - nManage);
			}
			else if (nManage <= 0)
			{
				m_pPlayer->setHp(m_pPlayer->getHp() - 1);
			}
		}
	}
}
void CBattleScene::init(CPlayer* pData)
{
	setPlayerValues(m_pCurMapDt->nPlayerRow, m_pCurMapDt->nPlayerCol, pData);
	setEnemyValues(m_pCurMapDt->nEnemyRow, m_pCurMapDt->nEnemyCol, pData->getEnemy());
	m_bPlayerStartCommonAttack = false;
	m_bEnemyStartCommonAttack = false;
	m_bAbleToMove = true;
	m_bSkillState = false;
	m_bPlayerSkillAttack = false;
	m_bEnemySkillAttack = false;
	m_bUseGoods = false;
	m_bJudgeSkillOrCommon = false;
	m_bShowNoMp = false;
	m_bShowGoodLack = false;
	vector<SItemDt*> vecGood = pData->getBag();
	for (int i = 0; i < vecGood.size(); i++)
	{
		SItemDt* pTempData = vecGood[i];
		if (pTempData->nType == 10)
		{
			m_vecGoods.push_back(pTempData);
		}
	}
}
void CBattleScene::useGoodOperate()
{
	m_pPlayer->getBag()[m_nGoodsIndex]->nCount--;
	m_bUseGoods = false;
	m_bShowGoodLack = false;
	m_nCount++;
	EnemyCommonAttack(m_pEnemy->getAtk(), m_pPlayer->getDef());
}
void CBattleScene::restorePosition(CPlayer* pTempPlayer)
{
	CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->setPosition(pTempPlayer->getRowBk(), pTempPlayer->getColBk());
	CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
}

