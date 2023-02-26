#pragma once
#include <vector>
#include "DataBasic.h"
#include "Npc.h"
#include "Player.h"
using namespace std;
class CMissionScene
{
public:
	CMissionScene();
	~CMissionScene();
	void update();
	void render();
	void initMissionWithNpcID(int nNpcID);
	CC_SYNTHESIZE(CNpc*, m_pCurNpc, Npc);
	CC_SYNTHESIZE(CPlayer*, m_pPlayer,Player);
private:
	vector<SMissionDt*> m_vecMissions;
	int m_nIndex;
	bool m_bShowConfirm;
	int m_nConfirmIndex;
	bool m_bConTaskMove;
	bool m_bAlreadyTake;
	bool m_bAvoid;
	int m_nTime;
	bool m_bTalk;
	bool m_bFinishTalk;
};

