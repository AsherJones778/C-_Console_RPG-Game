#pragma once
#include "DataBasic.h"
#include "Player.h"
#include "Enemy.h"
class CBattleScene
{
public:
	CBattleScene();
	~CBattleScene();
	void update();
	void render();
	void setEnemyValues(int nRow, int nCol, CEnemy* pData);
	void setPlayerValues(int nRow, int nCol, CPlayer* pData);
	void playerCommonAttack(int nPlayerAtk,int nEnemyDef);
	void playerSkillAttack(int nPlayerAtk, int nEnemyDef);
	void EnemyCommonAttack(int nEnemyAtk, int nPlayerDef);
	void EnemySkillAttack(int nEnemyAtk, int nPlayerDef);
	void init(CPlayer* pData);
	void useGoodOperate();
	void restorePosition(CPlayer* pTempPlayer);
	CC_SYNTHESIZE(SBattleMapDt*, m_pCurMapDt, CurMapDt);
	CC_SYNTHESIZE_READONLY(CPlayer*, m_pPlayer, Player);
	CC_SYNTHESIZE_READONLY(CEnemy*, m_pEnemy, Enemy);
	CC_SYNTHESIZE(vector<SItemDt*>, m_vecGoods, Goods);
private:
	int m_nCount;
	int m_nSkillCount;
	int m_nBattleState;
	bool m_bPlayerStartCommonAttack;
	bool m_bEnemyStartCommonAttack;
	bool m_bAbleToMove;
	bool m_bSkillState;
	int m_nSkillIndex;
	bool m_bPlayerSkillAttack;
	bool m_bEnemySkillAttack;
	bool m_bUseGoods;
	bool m_bJudgeSkillOrCommon;
	int m_nGoodsIndex;
	bool m_bShowNoMp;
	bool m_bShowGoodLack;
	bool m_bAllowChooseGood;
};

