#pragma once
class CGameWin
{
public:
	CGameWin();
	~CGameWin();
	void update();
	void render();
private:
	int m_nIndex;
	bool m_bShowPlayerValue;
};

