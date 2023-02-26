#include "stdafx.h"
#include "GameMgr.h"

CGameMgr* CGameMgr::m_psInstance = nullptr;
CGameMgr::CGameMgr()
{
	m_nGameState = E_GAME_MENU;
	m_pGameMap = new CGameMap();
	m_pGameMenu = new CGameMenu();
	m_pSelectRole = new CSelectRole();
	m_pStore = new CStore();
	m_pBag = new CBag();
	m_pPlayerState = new CPlayerState();
	m_pBattleScene = new CBattleScene();
	m_pDeadScene = new CGameDead();
	m_pMissionScene = new CMissionScene();
	m_pHandinMission = new CHandInMission();
	m_pGameWin = new CGameWin();
}


CGameMgr::~CGameMgr()
{
	CC_SAFE_DELETE(m_pGameMenu);
	CC_SAFE_DELETE(m_pGameMap);
	CC_SAFE_DELETE(m_pSelectRole);
	CC_SAFE_DELETE(m_pStore);
	CC_SAFE_DELETE(m_pBag);
	CC_SAFE_DELETE(m_pPlayerState);
	CC_SAFE_DELETE(m_pBattleScene);
	CC_SAFE_DELETE(m_pDeadScene);
	CC_SAFE_DELETE(m_pMissionScene);
	CC_SAFE_DELETE(m_pHandinMission);
	CC_SAFE_DELETE(m_pGameWin);
}

CGameMgr* CGameMgr::getInstance()
{
	if (!m_psInstance)
	{
		m_psInstance = new CGameMgr();
	}
	return m_psInstance;
}

void CGameMgr::update()
{
	if (E_GAME_MENU == m_nGameState)
	{
		m_pGameMenu->update();
	}
	else if (E_GAME_MAP == m_nGameState)
	{
		m_pGameMap->update();
	}
	else if (E_GAME_SELECT == m_nGameState)
	{
		m_pSelectRole->update();
	}
	else if (E_GAME_STORE == m_nGameState)
	{
		m_pStore->update();
	}
	else if (E_GAME_BAG == m_nGameState)
	{
		m_pBag->update();
	}
	else if (E_GAME_PLAYERSTATE == m_nGameState)
	{
		m_pPlayerState->update();
	}
	else if (E_GAME_BATTLE == m_nGameState)
	{
		m_pBattleScene->update();
	}
	else if (E_GAME_DEAD == m_nGameState)
	{
		m_pDeadScene->update();
	}
	else if (E_GAME_MISSIONSCENE == m_nGameState)
	{
		m_pMissionScene->update();
	}
	else if (E_GAME_HANDINMISSION == m_nGameState)
	{
		m_pHandinMission->update();
	}
	else if (E_GAME_WIN == m_nGameState)
	{
		m_pGameWin->update();
	}
}

void CGameMgr::render()
{
	if (E_GAME_MENU == m_nGameState)
	{
		m_pGameMenu->render();
	}
	else if (E_GAME_MAP == m_nGameState)
	{
		m_pGameMap->render();
	}
	else if (E_GAME_SELECT == m_nGameState)
	{
		m_pSelectRole->render();
	}
	else if (E_GAME_STORE == m_nGameState)
	{
		m_pStore->render();
	}
	else if (E_GAME_BAG == m_nGameState)
	{
		m_pBag->render();
	}
	else if (E_GAME_PLAYERSTATE == m_nGameState)
	{
		m_pPlayerState->render();
	}
	else if (E_GAME_BATTLE == m_nGameState)
	{
		m_pBattleScene->render();
	}
	else if (E_GAME_DEAD == m_nGameState)
	{
		m_pDeadScene->render();
	}
	else if (E_GAME_MISSIONSCENE == m_nGameState)
	{
		m_pMissionScene->render();
	}
	else if (E_GAME_HANDINMISSION == m_nGameState)
	{
		m_pHandinMission->render();
	}
	else if (E_GAME_WIN == m_nGameState)
	{
		m_pGameWin->render();
	}
}
