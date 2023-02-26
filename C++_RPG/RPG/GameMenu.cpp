#include "stdafx.h"
#include "GameMenu.h"
#include "GameMgr.h"
enum 
{
	E_MENU_START,
	E_MENU_SET,
	E_MENU_EXIT,
};
CGameMenu::CGameMenu()
{
	CGameMenu::m_nMenuState = E_MENU_START;
}
CGameMenu::~CGameMenu()
{
}
void CGameMenu::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nMenuState--;
		if (m_nMenuState < E_MENU_START)
		{
			m_nMenuState = E_MENU_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nMenuState++;
		if (m_nMenuState > E_MENU_EXIT)
		{
			m_nMenuState = E_MENU_START;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_MENU_START == m_nMenuState)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_SELECT);
		}
		else if (E_MENU_EXIT == m_nMenuState)
		{
			exit(0);
		}
	}
}
void CGameMenu::render()
{
	if (m_nMenuState == E_MENU_START)
	{
		cout << "■■■■■■■■■■■■■" << endl;
		cout << "■     游  戏  菜  单   ■" << endl;
		cout << "■     -> 游戏开始      ■" << endl;
		cout << "■        游戏说明      ■" << endl;
		cout << "■        游戏退出      ■" << endl;
		cout << "■■■■■■■■■■■■■" << endl;
	}
	else if (m_nMenuState == E_MENU_SET)
	{
		cout << "■■■■■■■■■■■■■" << endl;
		cout << "■     游  戏  菜  单   ■" << endl;
		cout << "■        游戏开始      ■" << endl;
		cout << "■     -> 游戏说明      ■" << endl;
		cout << "■        游戏退出      ■" << endl;
		cout << "■■■■■■■■■■■■■" << endl;
	}
	else if (m_nMenuState == E_MENU_EXIT)
	{
		cout << "■■■■■■■■■■■■■" << endl;
		cout << "■     游  戏  菜  单   ■" << endl;
		cout << "■        游戏开始      ■" << endl;
		cout << "■        游戏说明      ■" << endl;
		cout << "■     -> 游戏退出      ■" << endl;
		cout << "■■■■■■■■■■■■■" << endl;
	}
}
