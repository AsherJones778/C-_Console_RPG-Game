#pragma once
#include "GameMap.h"
#include "GameMenu.h"
#include "SelectRole.h"
#include "Bag.h"
#include "PlayerState.h"
#include "BattleScene.h"
#include "GameDead.h"
#include "MissionScene.h"
#include "HandInMission.h"
#include "GameWin.h"
class CGameMgr
{
public:
	
	~CGameMgr();
	static CGameMgr* getInstance();

	void update();
	void render();

	CC_SYNTHESIZE(int, m_nGameState, GameScene);
	CC_SYNTHESIZE_READONLY(CGameMap*, m_pGameMap,GameMap);
	CC_SYNTHESIZE_READONLY(CStore*, m_pStore,Store);
	CC_SYNTHESIZE_READONLY(CBag*, m_pBag, Bag);
	CC_SYNTHESIZE_READONLY(CSelectRole*, m_pSelectRole,SelectRole);
	CC_SYNTHESIZE(CBattleScene*, m_pBattleScene, BattleScene);
	CC_SYNTHESIZE(CMissionScene*, m_pMissionScene,MissionScene);
	CC_SYNTHESIZE(CHandInMission*, m_pHandinMission,HandInMission);
private:
	CGameMgr();
	static CGameMgr* m_psInstance;
	CGameMenu* m_pGameMenu;
	CPlayerState* m_pPlayerState;
	CGameDead* m_pDeadScene;
	CGameWin* m_pGameWin;
};

