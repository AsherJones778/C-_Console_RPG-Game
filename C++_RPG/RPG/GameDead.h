#pragma once
class CGameDead
{
public:
	CGameDead();
	~CGameDead();
	void update();
	void render();
	void showPlayerValue();
private:
	int m_nDeadIndex;
	bool m_bShowValue;
};

