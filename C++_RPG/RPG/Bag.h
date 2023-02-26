#pragma once
#include "Player.h"
#include "DataBasic.h"
class CBag
{
public:
	CBag();
	~CBag();
	void update();
	void render();
	void useGood(vector<SItemDt*> vecBag, CPlayer* pPlayer);
	void sellItems(CPlayer* pPlayer);
private:
	int m_nIndex;
	SItemDt* m_pDefItem;
};

