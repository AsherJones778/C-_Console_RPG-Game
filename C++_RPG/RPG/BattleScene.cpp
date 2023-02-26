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
	//初始化
	m_pCurMapDt = static_cast<SBattleMapDt*>(CDataMgr::getInstance()->getMgr("BattleMapDtMgr")->getDataByID(pTempPlayer->getEnemy()->getBattleMapID()));
	//判断是否在技能选项 技能光标移动
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
			if (m_pPlayer->getMp() >= m_pPlayer->getSkillBag()[m_nSkillIndex]->nMP)//加入蓝量足够此次技能释放
			{
				m_bPlayerSkillAttack = true;
				m_bJudgeSkillOrCommon = true;
				m_pPlayer->setMp(m_pPlayer->getMp() - m_pPlayer->getSkillBag()[m_nSkillIndex]->nMP);//使用技能减少蓝量
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
	//物品栏光标移动
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
				if (m_pPlayer->getBag()[m_nGoodsIndex]->strName == "大还丹" && m_pPlayer->getBag()[m_nGoodsIndex]->nCount > 0)
				{
					m_pPlayer->setMp(m_pPlayer->getMp() + m_pPlayer->getBag()[m_nGoodsIndex]->nMP);//回复篮量
					useGoodOperate();
				}
				else if (m_pPlayer->getBag()[m_nGoodsIndex]->strName == "大补丹" && m_pPlayer->getBag()[m_nGoodsIndex]->nCount > 0)
				{
					m_pPlayer->setHp(m_pPlayer->getHp() + m_pPlayer->getBag()[m_nGoodsIndex]->nHP);//回复血量
					useGoodOperate();
				}
			}
			else
			{
				m_bShowGoodLack = true;//没有道具或者道具数量不够
			}
			
		}
	}
	//玩家技能攻击
	playerSkillAttack(m_pPlayer->getAtk(), m_pEnemy->getDef());
	EnemySkillAttack(m_pEnemy->getAtk(), m_pPlayer->getDef());
	//玩家攻击前选择出击方式
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
			if (E_BATTLE_COMMONATTACK == m_nBattleState)//普通攻击
			{
				m_bPlayerStartCommonAttack = true;
				m_nCount++;
				m_bJudgeSkillOrCommon = false;
				m_bShowNoMp = false;
				m_bShowGoodLack = false;
			}
			else if (E_BATTLE_SKILL == m_nBattleState)//技能攻击
			{
				m_bSkillState = true;
				m_bShowGoodLack = false;
			}
			else if (E_BATTLE_USEGOOD == m_nBattleState)//使用道具
			{
				m_bUseGoods = true;
			}
			else if (E_BATTLE_RUNAWAY == m_nBattleState)//逃跑
			{
				restorePosition(pTempPlayer);//还原地图位置
				m_pPlayer->setHp(m_pPlayer->getHp() - (m_pEnemy->getAtk() - m_pPlayer->getDef()));//逃跑玩家扣除血量
			}
		}
	}
	//调用普通攻击
	playerCommonAttack(m_pPlayer->getAtk(), m_pEnemy->getDef());
	EnemyCommonAttack(m_pEnemy->getAtk(), m_pPlayer->getDef());
	//敌人死亡
	if (m_pEnemy->getHP() <= 0)
	{
		
		m_nCount = 0;
		m_bSkillState = false;
		//奖励
		int nReward = m_pEnemy->getMoney();
		m_pPlayer->setMoney(m_pPlayer->getMoney() + nReward);
		//任务判断
		CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->reduceMissionMonsterNumber(m_pEnemy->getID());
		restorePosition(pTempPlayer);
	}
	//玩家死亡
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
	cout << "\t" << "当前场景:" << m_pCurMapDt->strName << endl;
	for (int i = 0; i < m_pCurMapDt->nRowCount; i++)
	{
		for (int j = 0; j < m_pCurMapDt->nColCount; j++)
		{

			if (1 == m_pCurMapDt->arrMap[i][j])
			{
				cout << "■";
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
		cout << "■■■■■■■■■■■■" << endl;
		cout << "■        →普通攻击  ■" << endl;
		cout << "■          技能      ■" << endl;
		cout << "■          道具      ■" << endl;
		cout << "■          逃跑      ■" << endl;
		cout << "■■■■■■■■■■■■" << endl;
	}
	else if (E_BATTLE_SKILL == m_nBattleState)
	{
		cout << "■■■■■■■■■■■■" << endl;
		cout << "■          普通攻击  ■" << endl;
		cout << "■        →技能      ■" << endl;
		cout << "■          道具      ■" << endl;
		cout << "■          逃跑      ■" << endl;
		cout << "■■■■■■■■■■■■" << endl;
	}
	else if (E_BATTLE_USEGOOD == m_nBattleState)
	{
		cout << "■■■■■■■■■■■■" << endl;
		cout << "■          普通攻击  ■" << endl;
		cout << "■          技能      ■" << endl;
		cout << "■        →道具      ■" << endl;
		cout << "■          逃跑      ■" << endl;
		cout << "■■■■■■■■■■■■" << endl;
	}
	else if (E_BATTLE_RUNAWAY == m_nBattleState)
	{
		cout << "■■■■■■■■■■■■" << endl;
		cout << "■          普通攻击  ■" << endl;
		cout << "■          技能      ■" << endl;
		cout << "■          道具      ■" << endl;
		cout << "■        →逃跑      ■" << endl;
		cout << "■■■■■■■■■■■■" << endl;
	}

	cout << endl << endl;
	cout << "---当前玩家状态---" << "\t" << "---当前敌人状态---" << endl << endl;
	cout << "生命值:  " << m_pPlayer->getHp() << "\t" << "\t" << "生命值:  " << m_pEnemy->getHP() << endl;
	cout << "攻击力:  " << m_pPlayer->getAtk() << "\t" << "\t" << "攻击力:  " << m_pEnemy->getAtk() << endl;
	cout << "防御力:  " << m_pPlayer->getDef() << "\t" << "\t" << "防御力:  " << m_pEnemy->getDef() << endl;
	cout << " MP值 :  " << m_pPlayer->getMp() << endl;
	
	if (m_bSkillState)
	{
		cout << "---------------技能栏---------------" << endl << endl;
		cout << "    " << "    " << "技能名称" << "\t" << "\t" << "耗费MP量" << "\t"  << "伤害追加" << endl;
		vector<SSkillDt*> vecSkill = m_pPlayer->getSkillBag();
		for (int i = 0; i < vecSkill.size(); i++)
		{
			if (i == m_nSkillIndex)
			{
				cout << "→  ";
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
		cout << "---------------道具栏---------------" << endl;
		cout << "      " << "名称" << "\t" << "回复生命值" << "\t" << "回复法力值" << "\t" << "数量" << endl;
		for (int i = 0; i < vecBag.size(); i++)
		{
			if (vecBag[i]->nNpcID == 104)
			{
				if (i == m_nGoodsIndex)
				{
					cout << "  →";
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
		cout << "没有足够的蓝量释放技能！" << endl;
	}
	if (m_bShowGoodLack)
	{
		cout << "背包中没有药品或者药品数量不足！请战斗完事儿后速速补充！";
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

