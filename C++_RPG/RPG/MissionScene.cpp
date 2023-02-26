#include "stdafx.h"
#include "MissionScene.h"
#include "Player.h"
#include "GameMgr.h"
#include "DataMgr.h"
CMissionScene::CMissionScene()
{
	m_nIndex = 0;//显示当前的任务名称
	m_pCurNpc = nullptr;
	m_bShowConfirm = false;//是否显示确认接受任务菜单
	m_bConTaskMove = false;//确认接受菜单光标是否可移动
	m_nConfirmIndex = 0;//确认任务光标初始化
	m_bAlreadyTake = false;//是否已经接过此任务
	m_bAvoid = false; 
	m_nTime = 0;
	m_bTalk = false;
	m_bFinishTalk = false;
}
CMissionScene::~CMissionScene()
{
	CC_SAFE_DELETE(m_pCurNpc);
	CC_SAFE_DELETE(m_pPlayer);
	for (SMissionDt* pData : m_vecMissions)
	{
		delete pData;
		pData = nullptr;
	}
	m_vecMissions.clear();
}
void CMissionScene::update()
{
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	if (!m_bShowConfirm)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nIndex--;
			if (m_nIndex < 0)
			{
				m_nIndex = m_vecMissions.size() - 1;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nIndex++;
			if (m_nIndex > m_vecMissions.size() - 1)
			{
				m_nIndex = 0;
			}
		}
		if (KEY_DOWN(VK_RETURN))
		{
			//如果这个任务不在玩家的任务列表里面  
			if (!m_pPlayer->judgeMissionIsExist(m_vecMissions[m_nIndex]) && m_vecMissions[m_nIndex]->bIsFinish == false)
			{
				m_bShowConfirm = true;//显示是否接受任务菜单
				m_bAlreadyTake = false;//没接过这个任务  
				m_bConTaskMove = true;//选择是否接受任务菜单 可以移动了
				m_bAvoid = false;
				m_bTalk = true;
			}
			else
			{
				m_bAlreadyTake = true;
				m_bShowConfirm = false;//不显示是否接受任务菜单
				m_bConTaskMove = false;//选择是否接受任务菜单 不可以移动
			}
		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			//重新初始化一下 避免再次进入同一个NPC是上次进入的变量对这次进入的流程的影响
			m_nIndex = 0;//显示当前的任务名称
			m_bShowConfirm = false;//是否显示确认接受任务菜单
			m_bConTaskMove = false;//确认接受菜单光标是否可移动
			m_nConfirmIndex = 0;//确认任务光标初始化
			m_bAlreadyTake = false;//是否已经接过此任务
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		}
	}
	if (m_bConTaskMove && m_bShowConfirm && m_bAvoid)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_nConfirmIndex--;
			if (m_nConfirmIndex < 0)
			{
				m_nConfirmIndex = 1;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nConfirmIndex++;
			if (m_nConfirmIndex > 1)
			{
				m_nConfirmIndex = 0;
			}
		}
		if (KEY_DOWN(VK_RETURN))
		{
			if (0 == m_nConfirmIndex)
			{
				m_pPlayer->addMissionToVecMission(m_vecMissions[m_nIndex]);//把此任务加进玩家任务列表
				m_bShowConfirm = false;
				m_bTalk = false;
			}
			if (1 == m_nConfirmIndex)
			{
				m_bShowConfirm = false;
				m_bTalk = false; 
			}

		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bConTaskMove = false;
			m_bShowConfirm = false;
		}
	}
	m_bAvoid = true;
}

void CMissionScene::render()
{
	cout << "             当前NPC:" << m_pCurNpc->getName() << endl;
	cout << "----------------当前可接收任务-----------------" << endl << endl;
	cout << "    " << "任务名称" << "\t" << "任务简介" << "\t" << "任务类型" << endl;
	for (int i = 0; i < m_vecMissions.size(); i++)
	{
		if (i == m_nIndex)
		{
			cout << "->  ";
		}
		else
		{
			cout << "    ";
		}
		cout << m_vecMissions[i]->strName << "\t" << m_vecMissions[i]->strDescribe << "\t" << m_vecMissions[i]->strType << "线" << endl;
	}
	if (m_bAlreadyTake)
	{
		m_nTime++;
		cout << "此任务已经接受过了，请勿重复接受！"<<endl;
		if (m_nTime > 10)
		{
			m_nTime = 0;
			m_bAlreadyTake = false;
		}
	}
	if (m_bShowConfirm)
	{
		cout << "---------------确定接收此任务？----------------" << endl;
		if (0 == m_nConfirmIndex)
		{
			cout << "  →确认接受      " << endl;
			cout << "    容我再考虑考虑" << endl;
			m_bAlreadyTake = false;
		}
		else if (1 == m_nConfirmIndex)
		{
			cout << "    确认接受      " << endl;
			cout << "  →容我再考虑考虑" << endl;
			m_bAlreadyTake = false;
		}
	}
	if (m_bTalk)
	{
		cout << "---------------对话详情---------------" << endl;
		for (string pData : m_vecMissions[m_nIndex]->m_vec_strGetMission)
		{
			cout << pData << endl;
		}
	}
}
void CMissionScene::initMissionWithNpcID(int nNpcID)
{
	m_vecMissions.clear();
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getMgr("MissionDtMgr")->getAllDatas();
	for (SBaseDt* pData : vecDatas)
	{
		SMissionDt* pMissionDt = static_cast<SMissionDt*>(pData);
		if (pMissionDt->nNpcID == nNpcID)
		{
			m_vecMissions.push_back(pMissionDt);
		}
	}
}