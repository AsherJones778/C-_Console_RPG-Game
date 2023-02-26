#pragma once
#include "Player.h"
#include "Npc.h"
#include "DataBasic.h"
class CHandInMission
{
public:
	CHandInMission();
	~CHandInMission();
	void getMission(SMissionDt* pMission);
	void getReward(int nMoney);
	void finishMissionOperate();
	void update();
	void render();
private:
	SMissionDt* m_pMission;
};