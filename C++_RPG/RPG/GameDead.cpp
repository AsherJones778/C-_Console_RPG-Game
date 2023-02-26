#include "stdafx.h"
#include "GameDead.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include "SelectRole.h"
#include "Player.h"
enum 
{
	E_DEAD_RESTART,
	E_DEAD_VALUE,
	E_DEAD_EXIT,
};
CGameDead::CGameDead()
{
	m_nDeadIndex = E_DEAD_RESTART;
	m_bShowValue = false;
}
CGameDead::~CGameDead()
{

}
void CGameDead::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nDeadIndex--;
		if (m_nDeadIndex < E_DEAD_RESTART)
		{
			m_nDeadIndex = E_DEAD_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nDeadIndex++;
		if (m_nDeadIndex > E_DEAD_EXIT)
		{
			m_nDeadIndex = E_DEAD_RESTART;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_DEAD_RESTART == m_nDeadIndex)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
			CGameMgr::getInstance()->getGameMap()->getCurPlayerDt()->transformData(CGameMgr::getInstance()->getSelectRole()->getDefiniteRole());
		}
		else if (E_DEAD_VALUE == m_nDeadIndex)
		{
			m_bShowValue = true;
		}
		else if (E_DEAD_EXIT == m_nDeadIndex)
		{
			exit(0);
		}
	}
}
void CGameDead::render()
{
	if (E_DEAD_RESTART == m_nDeadIndex)
	{
		cout << "■■■■■您已经死亡■■■■■" << endl;
		cout << "■        →重新开始        ■" << endl;
		cout << "■          查看属性        ■" << endl;
		cout << "■          退出游戏        ■" << endl;
		cout << "■■■■■■■■■■■■■■■" << endl;
	}
	else if (E_DEAD_VALUE == m_nDeadIndex)
	{
		cout << "■■■■■您已经死亡■■■■■" << endl;
		cout << "■          重新开始        ■" << endl;
		cout << "■        →查看属性        ■" << endl;
		cout << "■          退出游戏        ■" << endl;
		cout << "■■■■■■■■■■■■■■■" << endl;
	}
	else if (E_DEAD_EXIT == m_nDeadIndex)
	{
		cout << "■■■■■您已经死亡■■■■■" << endl;
		cout << "■          重新开始        ■" << endl;
		cout << "■          查看属性        ■" << endl;
		cout << "■        →退出游戏        ■" << endl;
		cout << "■■■■■■■■■■■■■■■" << endl;
	}
	if (m_bShowValue)
	{
		showPlayerValue();
	}
}
void CGameDead::showPlayerValue()
{
	CPlayer* pData = CGameMgr::getInstance()->getGameMap()->getCurPlayerDt();
	cout << "角色名称" << "\t" << "生命值" << "\t" << "法力值" << "\t" << "攻击力" << "\t" << "防御力" << endl;
	cout << pData->getPic() << "\t" << "\t" << pData->getHp() << "\t" << pData->getMp() << "\t" << pData->getAtk() << "\t" << pData->getDef() << endl;
}
