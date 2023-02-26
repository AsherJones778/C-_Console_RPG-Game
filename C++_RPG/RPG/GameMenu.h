#pragma once
class CGameMenu
{
public:
	CGameMenu();
	~CGameMenu();
	void update();
	void render();
private:
	int m_nMenuState;
};

