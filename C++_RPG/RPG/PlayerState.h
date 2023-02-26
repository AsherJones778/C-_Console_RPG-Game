#pragma once
#include "DataBasic.h"
class CPlayerState
{
public:
	CPlayerState();
	~CPlayerState();
	void update();
	void render();
private:
	SItemDt* arrWeapon[4];
	int m_nStateIndex;
};

