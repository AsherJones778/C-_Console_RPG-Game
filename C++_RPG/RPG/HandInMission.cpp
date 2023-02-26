#include "stdafx.h"
#include "HandInMission.h"
#include "GameMgr.h"
CHandInMission::CHandInMission()
{
}
CHandInMission::~CHandInMission()
{
	CC_SAFE_DELETE(m_pMission);
}
void CHandInMission::update()
{
	if (KEY_DOWN(VK_RETURN))
	{
		if (m_pMission->nID == 5007)
		{
			finishMissionOperate();
			CGameMgr::getInstance()->setGameScene(E_GAME_WIN);
		}
		else
		{
			finishMissionOperate();
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		}
	}
}
void CHandInMission::render()
{
	cout << "---------------完成任务---------------" << endl;
	cout << "任务名称:" << m_pMission->strName << endl;
	cout << "任务概述:" << m_pMission->strDescribe << endl;
	cout << "任务奖励:" << "金币" << m_pMission->nReward << "枚" << endl;
	cout << "---------------详细对话---------------" << endl;
	for (int i = 0; i < m_pMission->nFinishTalkLines; i++)
	{
		cout << m_pMission->m_vec_strFinishMission[i] << endl;
	}
	cout << endl << endl;
	cout << "-------按下回车键领取奖励并退出-------" << endl;
}
void CHandInMission::getMission(SMissionDt* pMission)
{
	m_pMission = pMission;
}
void CHandInMission::getReward(int nMoney)
{
	CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->AddMoney(nMoney);
}

void CHandInMission::finishMissionOperate()
{
	CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->delMission(m_pMission);
	getReward(m_pMission->nReward);
	m_pMission->bIsFinish = true;
}
