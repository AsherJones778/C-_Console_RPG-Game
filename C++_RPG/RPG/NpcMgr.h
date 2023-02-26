#pragma once
#include "Npc.h"
#include <vector>
using namespace std;
class CNpcMgr
{
public:
	CNpcMgr();
	~CNpcMgr();
	void createNpc();
	CNpc* getNpcByID(int nID);
	CNpc* isExist(int nRow,int nCol,int nMapID);
private:
	vector<CNpc*> m_vecNpcs;
};