#pragma once
#include <vector>
#include "DataBasic.h"
using namespace std;
class CStore
{
public:
	CStore();
	~CStore();

	void update();
	void render();
	void initItemWithNpcID(int nNpcID);
private:
	vector<SItemDt*> m_vecItems;
	int m_nIndex;
	bool m_bEnoughMoney;
};

