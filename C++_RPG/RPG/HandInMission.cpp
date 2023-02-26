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
	cout << "---------------�������---------------" << endl;
	cout << "��������:" << m_pMission->strName << endl;
	cout << "�������:" << m_pMission->strDescribe << endl;
	cout << "������:" << "���" << m_pMission->nReward << "ö" << endl;
	cout << "---------------��ϸ�Ի�---------------" << endl;
	for (int i = 0; i < m_pMission->nFinishTalkLines; i++)
	{
		cout << m_pMission->m_vec_strFinishMission[i] << endl;
	}
	cout << endl << endl;
	cout << "-------���»س�����ȡ�������˳�-------" << endl;
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
