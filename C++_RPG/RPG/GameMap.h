#pragma once
#include "Player.h"
#include "DataBasic.h"
#include "NpcMgr.h"
#include "EnemyMgr.h"
#include "Store.h"
class CGameMap
{
public:
	CGameMap();
	~CGameMap();
	void update();
	void render();
	CC_SYNTHESIZE(SMapDt*, m_pCurMapDt,CurMapDt);
	CC_SYNTHESIZE(CPlayer*, m_pPlayer,CurPlayerDt);
	CC_SYNTHESIZE_READONLY(CNpcMgr*, m_pNpcMgr, CurNpcMgr);
	CC_SYNTHESIZE_READONLY(CEnemyMgr*, m_pEnemyMgr, CurEnemyDt);
};



