#pragma once
#include "Enemy.h"
#include <vector>
using namespace std;
class CEnemyMgr
{
public:
	CEnemyMgr();
	~CEnemyMgr();
	void createEnemy();
	CEnemy* isExist(int nRow, int nCol, int nMapID);
private:
	vector<CEnemy*> m_vecEnemys;
};

